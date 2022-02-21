# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 6 ]; then
  echo "Script for running SCS via Julia in batch mode..."
  echo "SCS is invoked via JuMP by the scripts provided in PDLP (google/FirstOrderLP"
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <iterlimit> <precision> <method>" 1>&2
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
precision=$5
method=$6

scs6=$set/scs_${method}_sol_1e-$precision

mkdir -p $scs6

# google-pdhg
# 1e-8
# todo, scs how to set timelimit?
# it is unable to do so, then you can only controll time limits outside.
logfile=$set/scs_${method}_sol_1e-$precision.log
if [ -f $logfile ]; then
  rm $logfile
fi

# no need to run scs at 1e-8
for f in $(/bin/ls $set/$prefix); do
  nohup timeout $timelimit julia --project=$pdhgsrc/scripts $pdhgsrc/scripts/solve_lp_external.jl \
    --solver scs-$method \
    --verbose true \
    --print_stdout true \
    --iteration_limit $iterlimit \
    --output_dir $scs6 \
    --tolerance 1e-$precision \
    --instance_path $set/$prefix/$f &>>$logfile
done
