# test script to summarize all results
# @author Chuwen Zhang
# @usage: python analyze.py conf.json
#
import json
import logging
import os
import time

import pandas as pd

from analyze_google_pdhg import google_pdhg_string_to_result
from analyze_gurobi import gurobi_string_to_result
from analyze_scs import scs_string_to_result
from analyze_abip import abip_string_to_result

DEFAULT_CONF = "./conf.analyze.json"
ANALYZE_METHOD_REGISTRY = {
  "gurobi_simplex": gurobi_string_to_result,
  "gurobi_dual": gurobi_string_to_result,
  "gurobi_barrier": gurobi_string_to_result,
  "google_pdhg_1e-6": google_pdhg_string_to_result,
  "google_pdhg_1e-4": google_pdhg_string_to_result,
  "google_pdhg_1e-8": google_pdhg_string_to_result,
  "scs_indirect_1e-4": scs_string_to_result,
  "scs_indirect_1e-6": scs_string_to_result,
  "scs_direct_1e-4": scs_string_to_result,
  "scs_direct_1e-6": scs_string_to_result,
  "abip_direct_1e-4": abip_string_to_result,
  "abip_indirect_1e-4": abip_string_to_result,
  "abip_direct_1e-6": abip_string_to_result,
  "abip_indirect_1e-6": abip_string_to_result,
  ###########################
  # precision not achievable
  ###########################
  # "scs_indirect_1e-8": scs_string_to_result,
  # "scs_direct_1e-8": scs_string_to_result,
}

FORMAT = '%(asctime)s %(levelname)s %(name)s %(message)s'
logging.basicConfig(format=FORMAT, level=logging.DEBUG)

logger = logging.getLogger("@analyze")
logger.setLevel(logging.DEBUG)


def analyze(fpath=DEFAULT_CONF):
  config = json.load(open(fpath, 'r'))
  instance_path = config['directory']
  dfs = []
  logger.info(f"registered methods {config['methods']}")
  for m in config['methods']:
    name = m['name']
    affix = m['affix']
    func = ANALYZE_METHOD_REGISTRY[name]
    solution_path = os.path.join(instance_path, m['solution_dir'])
    results = []
    logger.debug(f"try {m}")
    if not os.path.exists(solution_path):
      logger.debug(f"method {m} does not exist")
      continue
    logger.debug(f"analyze {m} @ {solution_path}")
    for _fp in os.listdir(solution_path):
      fp = os.path.join(solution_path, _fp)
      if not fp.endswith(affix):
        continue
      try:
        r = func(fp)
        results.append(r)
      except Exception as e:
        logging.exception(e)
        logging.error(f"failed to analyze {name} @ {fp}")
    if len(results) > 0:
      df = pd.DataFrame.from_records(results).assign(
        method=name,
        name=lambda df: df['name'].apply(
          lambda x: x.replace('.mps', '').replace('.gz', '')
        )
      ).drop_duplicates(subset=['name', 'method'])
      dfs.append(df)
    
    logger.info(f"{name} solution finished")
  df_agg = pd.concat(dfs)
  
  instances = df_agg['name'].unique()
  method_names = [n['name'] for n in config['methods']]
  index = pd.MultiIndex.from_tuples(
    list((i, m) for m in method_names for i in instances.tolist()),
    names=('name', 'method')
  )
  df_agg = df_agg.set_index(['name', 'method']).reindex(index, fill_value='-').reset_index(drop=False).sort_values(
    ['name', 'method']
  )
  result_file = f"result_{int(time.time())}.xlsx"
  df_agg.to_excel(result_file, index=False)
  logger.info(f"analyze finished to file {result_file}")


if __name__ == '__main__':
  import argparse
  
  parser = argparse.ArgumentParser()
  parser.add_argument("--conf", type=str)
  args = parser.parse_args()
  analyze(args.conf)
