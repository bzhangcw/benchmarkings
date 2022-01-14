# create presolved mps using GUROBI
# @author CHUWEN ZHANG
import gurobipy
import os
import sys

input_dir, output_dir = sys.argv[1:]

if os.path.isdir(input_dir):
  in_files = os.listdir(input_dir)

  print(f"running {len(in_files)} models")

  for i in in_files:
    try:
      m = gurobipy.read(f"{input_dir}/{i}")
      m1 = m.relax().presolve()
      m1.write(f"{output_dir}/pre_{i}")
    except:
      print(f"failed at {i}")
else:
  i = input_dir
  m = gurobipy.read(i)
  m1 = m.relax().presolve()
  name = i.split("/")[-1]
  m1.write(f"{output_dir}/pre_{name}")
