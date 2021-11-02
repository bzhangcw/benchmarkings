# params
pdhgsrc=/Users/brent/workspace/google-first-order-lp
# test set
set=$1
timelimit=$2
prefix=$3

phdg6=$set/pdhg_sol_1e-6
phdg8=$set/pdhg_sol_1e-8

# clean

# rm -rf $phdg6 && mkdir $phdg6
# rm -rf $phdg8 && mkdir $phdg8

# google-pdhg
# 1e-8
julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \
  --time_sec_limit $timelimit \
  --method pdhg \
  --output_dir $phdg8 \
  --verbosity 4 \
  --redirect_stdio true \
  --instance_path $set/$prefix &>$set/pdhg.1e-8.log &

# 1e-6

julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \
  --time_sec_limit $timelimit \
  --relative_optimality_tol 1e-5 --eps_primal_infeasible 1e-6 --eps_dual_infeasible 1e-6 \
  --method pdhg \
  --output_dir $phdg6 \
  --verbosity 4 \
  --redirect_stdio true \
  --instance_path $set/$prefix &>$set/pdhg.1e-6.log &
