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
precision=8
eps=1e-$precision
uniform="nohup julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_qp.jl \
  --time_sec_limit $timelimit \
  --relative_optimality_tol $eps --eps_primal_infeasible $eps --eps_dual_infeasible $eps \
  --method pdhg \
  --verbosity 4 \
  --redirect_stdio true \
  --instance_path $set/$prefix"


###############################
# test different features
###############################

# baseline
attr=baseline
name=pdhg_$attr
phdg=$set/$name
log=$set/$name.log

mkdir -p $phdg
extraargs="--output_dir $phdg \
  --step_size_policy constant \
  --l_inf_ruiz_iterations 0 \
  --pock_chambolle_rescaling false \
  --l2_norm_rescaling false \
  --restart_scheme no_restart \
  --primal_weight_update_smoothing 0.0 \
  --scale_invariant_initial_primal_weight false"

cmd="$uniform \
   $extraargs &>> $log &"

echo $cmd
echo $cmd > $log
eval $cmd

# + restart
attr=restart
name=pdhg_$attr
phdg=$set/$name
log=$set/$name.log

mkdir -p $phdg
extraargs="--output_dir $phdg \
  --restart_to_current_metric gap_over_distance \
  --step_size_policy constant \
  --l_inf_ruiz_iterations 0 \
  --pock_chambolle_rescaling false \
  --l2_norm_rescaling false \
  --primal_weight_update_smoothing 0.0 \
  --scale_invariant_initial_primal_weight false"

cmd="$uniform \
   $extraargs &>> $log &"

echo $cmd
echo $cmd > $log
eval $cmd

 + scaling
attr=scaling
name=pdhg_$attr
phdg=$set/$name
log=$set/$name.log

mkdir -p $phdg
extraargs="--output_dir $phdg \
  --restart_to_current_metric gap_over_distance \
  --step_size_policy constant \
  --restart_scheme no_restart"

cmd="$uniform \
   $extraargs &>> $log &"

echo $cmd
echo $cmd > $log
eval $cmd

# + scaling + restart
attr=restart_scaling
name=pdhg_$attr
phdg=$set/$name
log=$set/$name.log

mkdir -p $phdg
extraargs="--output_dir $phdg \
  --restart_to_current_metric gap_over_distance \
  --step_size_policy constant \
  --primal_weight_update_smoothing 0.0 \
  --scale_invariant_initial_primal_weight false"

cmd="$uniform \
   $extraargs &>> $log &"

echo $cmd
echo $cmd > $log
eval $cmd


# + adaptive stepsize + primal weight + scaling + restart
attr=all
name=pdhg_$attr
phdg=$set/$name
log=$set/$name.log

mkdir -p $phdg
extraargs="--output_dir $phdg \
  --restart_to_current_metric gap_over_distance"

cmd="$uniform \
   $extraargs &>> $log &"

echo $cmd
echo $cmd > $log
eval $cmd

