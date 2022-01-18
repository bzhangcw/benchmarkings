# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 3 ]; then
  echo "Script for running Google PDLP in batch mode..."
  echo "Usage: <dataset directory> <subset name> <time limit for each instance>" 1>&2
  exit -1
fi

# params
pdhgsrc=google-pdlp

if [ ! -d $pdhgsrc ]; then
  echo "pdhg not set up here!"
  echo "link your pdgh directory to './google-pdlp' "
fi

# test set
set=$1
prefix=$2
timelimit=$3

phdg6=$set/pdhg_sol_1e-6
phdg8=$set/pdhg_sol_1e-8

mkdir -p $phdg6
mkdir -p $phdg8

# google-pdhg
# 1e-8
nohup julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \
  --time_sec_limit $timelimit \
  --relative_optimality_tol 1e-8 --eps_primal_infeasible 1e-8 --eps_dual_infeasible 1e-8 \
  --method pdhg \
  --output_dir $phdg8 \
  --verbosity 4 \
  --redirect_stdio true \
  --instance_path $set/$prefix &>$set/pdhg.1e-8.log &

# 1e-6
julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \

nohup julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \
  --time_sec_limit $timelimit \
  --relative_optimality_tol 1e-6 --eps_primal_infeasible 1e-6 --eps_dual_infeasible 1e-6 \
  --method pdhg \
  --output_dir $phdg6 \
  --verbosity 4 \
  --redirect_stdio true \
  --instance_path $set/$prefix &>$set/pdhg.1e-6.log &
