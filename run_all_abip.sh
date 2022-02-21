# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 7 ]; then
  echo "Script for running ABIP via matlab in batch mode..."
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <iterlimit> <precision> <method> <presolve>" 1>&2
  exit -1
fi

# params
wdir=$(pwd)
abipsrc=abip-lp

if [ ! -d $abipsrc ]; then
  echo "abip not set up here!"
  echo "link your abip directory to './abip-lp' "
  exit
fi

# test set
set=$1
prefix=$2
timelimit=$3
iterlimit=$4
precision=$5
method=$6
presolve=$7

abipname=$set/abip_${method}_1e-$precision
logfile=$abipname.$prefix.${presolve}.1e-$precision.log

mkdir -p $abipname

if [ -f $logfile ]; then
  rm $logfile
fi
# test_batch_func(fdir, fodir, max_iter, eps)
cd $wdir/$abipsrc
for f in $(/bin/ls $set/$prefix/*.mps); do
  ff=$f
  echo "running $ff" &>>$logfile
  mat_cmd="addpath test; test_batch_func('$ff', '$abipname', $iterlimit, 1e-$precision, $method, $presolve); exit;"
  echo $mat_cmd &>>$logfile
  nohup timeout $timelimit \
    $MATLAB_HOME/matlab -nodesktop -nosplash -noFigureWindows -r \
    "${mat_cmd}" &>>$logfile
done