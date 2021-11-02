# @author: chuwen
# python _.py "./data/miplib2017-collection/grb_presolved/pre_datt256.mps.gz" \
#   "./data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_primal.txt" \
#   "./data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_dual.txt"
import coptpy as cp
import sys

mps, primal, dual = sys.argv[1:]

print(mps, primal, dual)

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