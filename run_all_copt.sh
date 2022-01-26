# test set
set=$1
simplex=$set/copt_sol_simplex
dual=$set/copt_sol_dual
barrier=$set/copt_sol_barrier

# clean
mkdir -pv $simplex && mkdir $simplex
mkdir -pv $dual && mkdir $dual
mkdir -pv $barrier && mkdir $barrier

# gurobi
# python copt_solve_lp.py $set/copt_presolved $simplex ./copt.simplex.prm &>$set/copt.simplex.log &
# python copt_solve_lp.py $set/copt_presolved $dual ./copt.dual.prm &>$set/copt.dual.log &
python copt_solve_lp.py $set/copt_presolved $barrier ./copt.barrier.prm &>$set/copt.barrier.log &
