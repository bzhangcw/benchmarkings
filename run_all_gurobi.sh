# test set
set=$1
simplex=$set/grb_sol_simplex
dual=$set/grb_sol_dual
barrier=$set/grb_sol_barrier

# clean
mkdir -p $simplex
mkdir -p $dual
mkdir -p $barrier

# gurobi
# python gurobi_solve_lp.py $set/grb_presolved $simplex ./gurobi.simplex.prm &>$set/grb.simplex.log &
# python gurobi_solve_lp.py $set/grb_presolved $dual ./gurobi.dual.prm &>$set/grb.dual.log &
python gurobi_solve_lp.py $set/grb_presolved $barrier ./gurobi.barrier.prm &>$set/grb.barrier.log &
