# test script for gurobi solving the LP relaxation
# @author Chuwen Zhang
# @usage: python gurobi_solve_lp.py <input> <output> <param>
#
import gurobipy
import os
import sys

input_dir, output_dir, param_file = sys.argv[1:]

if os.path.isdir(input_dir):
  in_files = os.listdir(input_dir)

  print(f"running {len(in_files)} models")

  for i in in_files:
    try:
      m = gurobipy.read(f"{input_dir}/{i}")
      m.read(param_file)
      m1 = m.relax()
      m1.optimize()
      name = i.split("/")[-1].split(".")[0]
      m1.write(f"{output_dir}/{name}.json")
    except Exception as e:
      print(e.message)
      print(f"---- {name} --- failed ")
else:
  i = input_dir
  try:
    m = gurobipy.read(f"{i}")
    m.read(param_file)
    m1 = m.relax()
    m1.optimize()
    name = i.split("/")[-1].split(".")[0]
    m1.write(f"{output_dir}/{name}.json")
  except Exception as e:
    print(e.message)
    print(f"---- {name} --- failed ")
