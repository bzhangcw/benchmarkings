# test set
set=$1
subset=$2
simplex=$set/copt_sol_simplex
dual=$set/copt_sol_dual
barrier=$set/copt_sol_barrier

# clean
#mkdir -pv $simplex && mkdir $simplex
#mkdir -pv $dual && mkdir $dual
mkdir -pv $barrier

# gurobi
# python copt_solve_lp.py $set/copt_presolved $simplex ./copt.simplex.par &>$set/copt.simplex.log &
# python copt_solve_lp.py $set/copt_presolved $dual ./copt.dual.par &>$set/copt.dual.log &
python copt_solve_lp.py $set/$subset $barrier copt.barrier.par &>$set/copt.barrier.log &
