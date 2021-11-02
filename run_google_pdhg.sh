julia --project=scripts scripts/solve_qp.jl \
    --method pdhg \
    --output_dir ../miplib2017-bench/pdhg_sol \
    --instance_path ../miplib2017-bench/grb_presolved \
    --time_sec_limit 1000 &>../miplib2017-bench/pdhg.log &
