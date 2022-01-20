# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 3 ]; then
  echo "Script for generating different page rank instances in batch mode..."
  echo "sparsity defined as |E| / |V|"
  echo "Usage: <output_directory> <sparsity> <instance_number>" 1>&2
  exit -1
fi
pdhgsrc=google-pdlp
# params
for V in 10 50 100 500 1000 5000; do
  julia --project=$pdhgsrc/benchmarking $pdhgsrc/benchmarking/generate_pagerank_lp_batch.jl \
    --num_nodes $V \
    --random_seed 1 \
    --output_dir $1 \
    --sparsity $2 \
    --instance_number $3 &
done
