# test script to summarize all results
# @author Chuwen Zhang
# @usage: python analyze.py conf.json
#
import json
import logging
import os
import time

import pandas as pd

from analyze_abip import abip_string_to_result

DEFAULT_CONF = "./conf.analyze.json"

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
        func = abip_string_to_result
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
    df_agg = pd.concat(dfs).fillna(0)

    instances = df_agg['name'].unique()
    method_names = [n['name'] for n in config['methods']]
    index = pd.MultiIndex.from_tuples(
        list((i, m) for m in method_names for i in instances.tolist()),
        names=('name', 'method')
    )
    df_agg = df_agg.set_index(
        ['name', 'method']
    ).reindex(
        index, fill_value='-'
    ).reset_index(drop=False).sort_values(
        ['name', 'method']
    ).assign(
        real_name=lambda df: df['name'].apply(lambda x: x.replace('pre_', ''))
    )

    return df_agg


if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("--conf", type=str)
    # only output the instances with prefix
    parser.add_argument("--prefix", type=str, default='pre')

    args = parser.parse_args()
    df_agg = analyze(args.conf)
    result_stamp = int(time.time())
    df_agg.to_excel(f"result_{result_stamp}.xlsx", index=False)
    idx_df_agg_with_prefix = df_agg['name'].apply(lambda x: x.startswith(args.prefix))
    df_agg_pre = df_agg[idx_df_agg_with_prefix]
    # is successful? todo, may have to add a ground truth
    bool_fail = lambda x: x.lower() in ['unfinished']
    df_agg_pre = df_agg_pre.assign(
        bool_fail=lambda df: df.sol_status.apply(bool_fail)
    )
    df_agg_pre.to_excel(f"result_{result_stamp}.{args.prefix}.xlsx", index=False)
    # do some summary stats
    logger.info(f"analyze finished to with stamp {result_stamp}")

    df_agg_suc = df_agg_pre[~df_agg_pre.bool_fail]
    df_sum = df_agg_suc[(df_agg_suc != '-')].dropna().groupby(
        'method'
    )['name'].count().rename('solved').reset_index()
    df_sum.to_excel(f"result_{result_stamp}.summary.xlsx", index=False)
    print(df_sum.to_latex(multirow=True, multicolumn=True, caption='Number of solved instances'))
