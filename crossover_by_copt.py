# @author: chuwen
# input the ipm/1-st order solutions to query basis by crossover.
# python _.py "./data/miplib2017-collection/grb_presolved/pre_datt256.mps.gz" \
#   "./data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_primal.txt" \
#   "./data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_dual.txt"
from black import main
import coptpy as cp
import sys
import json

mps, primal, dual, output_dir = sys.argv[1:]

if __name__ == '__main__':
    print(mps, primal, dual)
    try:
        envr = cp.Envr()
        model = envr.createModel()
        model.read(mps)
        mvars = model.getVars()
        mconstr = model.getConstrs()
        primal = [float(i) for i in open(primal, 'r')]
        dual = [float(i) for i in open(dual, 'r')]
        sl = [0] * len(dual)
        rc = [0] * len(primal)
        model.setLpSolution(primal, sl, dual, rc)
        model.setParam("LpMethod", 3)
        model.solveLP()
        # dump results
        name = mps.split("/")[-1].replace('.mps', '').replace('.gz', '')
        content = {}
        content['name'] = name
        content['Status'] = model.LpStatus
        content['ObjVal'] = model.ObjVal
        content['IterCount'] = model.SimplexIter
        content['SolvingTime'] = model.SolvingTime
        print(content)
        json.dump(content, open(f"{output_dir}/{name}.crs.json", "w"))
    except Exception as e:
        print(mps, e.message)
