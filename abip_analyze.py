"""typical abip schema
{
  "status": "Solved",
  "ipm_iter": 39,
  "admm_iter": 2270,
  "mu": [],
  "pobj": 0,
  "dobj": -1.4003453115950552e-08,
  "resPri": 2.0406043610616293e-06,
  "resDual": 9.999104596259573e-05,
  "relGap": 1.4003452919853857e-08,
  "resInfeas": null,
  "resUnbdd": null,
  "setupTime": 0.025511,
  "solveTime": 44.7790708,
  "name": "pre_pagerank.100000.100000.0-1.mps"
}
"""
import json
import pandas as pd


def abip_string_to_result(fpath):
  with open(fpath, 'r') as f:
    content = json.load(f)
    res_primal = content['resPri']
    res_dual = content['resDual']
    sol_time = content['solveTime']
    sol_status = content['status']
    val_primal = content['pobj']
    val_dual = content['dobj']
    name = content['name']
    return dict(iteration_num=content['admm_iter'],
                ipm_num=content['ipm_iter'],
                res_primal=res_primal.__round__(8),
                res_dual=res_dual.__round__(8),
                sol_time=sol_time.__round__(4),
                val_primal=val_primal.__round__(4),
                val_dual=val_dual.__round__(4),
                sol_status=sol_status,
                name=name)
