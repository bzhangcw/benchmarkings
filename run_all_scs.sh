# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 4 ]; then
  echo "Script for running SCS via Julia in batch mode..."
  echo "SCS is invoked via JuMP by the scripts provided in PDLP (google/FirstOrderLP"
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <iterlimit>" 1>&2
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
iterlimit=$4

scs6=$set/scs_sol_1e-6
scs8=$set/scs_sol_1e-8

mkdir -p $scs6
mkdir -p $scs8

# google-pdhg
# 1e-8
# todo, scs how to set timelimit?
# it is unable to do so, then you can only controll time limits outside.
rm $set/scs.1e-8.log
for f in $(/bin/ls $set/$prefix); do
  nohup timeout $timelimit julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_lp_external.jl \
    --solver scs-indirect \
    --verbose true \
    --print_stdout true \
    --iteration_limit $iterlimit \
    --output_dir $scs8 \
    --tolerance 1e-8 \
    --instance_path $set/$prefix/$f &>>$set/scs.1e-8.log &
done
# 1e-6
rm $set/scs.1e-6.log
for f in $(/bin/ls $set/$prefix); do
  nohup timeout $timelimit julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_lp_external.jl \
    --solver scs-indirect \
    --verbose true \
    --print_stdout true \
    --iteration_limit $iterlimit \
    --output_dir $scs6 \
    --tolerance 1e-6 \
    --instance_path $set/$prefix/$f &>>$set/scs.1e-6.log &
done
