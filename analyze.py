# test script to summarize all results
# @author Chuwen Zhang
# @usage: python analyze.py conf.json
#
import json
import logging
import os
import time

import pandas as pd

from google_pdhg_analyze import google_pdhg_string_to_result
from gurobi_analyze import gurobi_string_to_result

DEFAULT_CONF = "./conf.analyze.json"
ANALYZE_METHOD_REGISTRY = {
  "gurobi_simplex": gurobi_string_to_result,
  "gurobi_dual": gurobi_string_to_result,
  "gurobi_barrier": gurobi_string_to_result,
  "google_pdhg_1e-6": google_pdhg_string_to_result,
  "google_pdhg_1e-8": google_pdhg_string_to_result
}

logger = logging.getLogger("@analyze")
logger.setLevel(logging.INFO)


def analyze(fpath=DEFAULT_CONF):
  config = json.load(open(fpath, 'r'))
  instance_path = config['directory']
  dfs = []
  for m in config['methods']:
    name = m['name']
    affix = m['affix']
    func = ANALYZE_METHOD_REGISTRY[name]
    solution_path = os.path.join(instance_path, m['solution_dir'])
    results = []
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
    df = pd.DataFrame.from_records(results).assign(method=name)
    dfs.append(df)
    logging.info(f"{name} solution finished")
  df_agg = pd.concat(dfs)

  result_file = f"result_{int(time.time())}.xlsx"
  df_agg.to_excel(result_file)
  logging.info("analyze finished to file {result_file}")


if __name__ == '__main__':
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("--conf", type=str)
  args = parser.parse_args()
  analyze(args.conf)
