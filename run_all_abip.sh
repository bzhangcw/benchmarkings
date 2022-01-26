# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 5 ]; then
  echo "Script for running ABIP via matlab in batch mode..."
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <iterlimit> <precision>" 1>&2
  exit -1
fi

# params
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

abipname=$set/abip_1e-$precision
logfile=$abipname.log

mkdir -p $abipname

if [ -f $logfile ]; then
  rm $logfile
fi
# test_batch_func(fdir, fodir, max_iter, eps)
for f in $(/bin/ls $set/$prefix); do
  ff=$set/$prefix/$f
  echo "running $ff" &>>$logfile
  mat_cmd="cd $abipsrc; addpath test; test_batch_func('$ff', '$abipname', $iterlimit, 1e-$precision)"
  echo $mat_cmd &>>$logfile
  nohup timeout $timelimit \
    $MATLAB_HOME/matlab -nodesktop -nosplash -noFigureWindows -r \
    "${mat_cmd}" &>>$logfile
done
