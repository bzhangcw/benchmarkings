# test script for COPT solving the LP relaxation
# @author Chuwen Zhang
# @usage: python copt_solve_lp.py <input> <output> <param>
# output schema
#
# {"Status": 2,
#  "Runtime": "2.8141441345214844e+00",
#  "ObjVal": "3",
#  "BoundVio": "0",
#  "ConstrVio": "0",
#  "IterCount": "55297",
#  "BarIterCount": 0
#  }
#

import coptpy
import os
import sys

input_dir, output_dir, param_file = sys.argv[1:]

if os.path.isdir(input_dir):
  in_files = os.listdir(input_dir)

  print(f"running {len(in_files)} models")

  for i in in_files:
    content = {}
    try:
      env = coptpy.Envr()
      m = env.createModel()
      m.read(f"{input_dir}/{i}")
      m.read(param_file)
      m.solveLP()
      name = i.split("/")[-1].replace('.mps', '').replace('.gz', '')
      content['name'] = name
      content['Status'] = m.LpStatus
      content['ObjVal'] = m.objval
      content['IterCount'] = 0
      m.write(f"{output_dir}/{name}.json")
    except Exception as e:
      print(e.message)
      print(f"---- {name} --- failed ")
else:
  i = input_dir
  content = {}
  try:
    m = coptpy.read(f"{i}")
    m.read(param_file)
    m1 = m.relax()
    m1.optimize()
    name = i.split("/")[-1].split(".")[0]
    m1.write(f"{output_dir}/{name}.json")
  except Exception as e:
    print(e.message)
    print(f"---- {name} --- failed ")
