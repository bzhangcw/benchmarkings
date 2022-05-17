# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */
if [ "$#" -ne 5 ]; then
  echo "Script for running ABIP via matlab in batch mode...";
  echo "  will run abip by environment variable 'abipsrc'";
  echo "Usage: export abipsrc=abiplp; export abipfunc=abip_indirect; export testfunc=test_one_abip_from_mat; export abipaffix=.mat"
  echo "Usage:  <dataset directory> <subset name> <time limit for each instance> <abip_func.mat> <eps>" 1>&2
  exit -1
fi

# params
wdir=$(pwd)

echo "working directory ${wdir}"

if [ -z $abipsrc ]; then
  echo "'abipsrc' unset!"
  echo "set your abip directory first 'abiplp' "
  exit
fi

if [ ! -d $abipsrc ]; then
  echo "abip not set up here!"
  echo "link your abip directory here, maybe './abiplp' "
  exit
fi

# test set
set=$1
prefix=$2
timelimit=$3
abip_func_params=$4
precision=$5

abipname=$set/${abipfunc}_${abip_func_params}_1e-$precision
logfile=${abipname}.$prefix.1e-$precision.log

mkdir -p $abipname

if [ -f $logfile ]; then
  rm $logfile
fi

##########
# dbg
##########
echo $abipname
echo $logfile

cd $wdir/$abipsrc

for f in $(/bin/ls $set/$prefix/*${abipaffix}); do
  ff=$(basename -s .mps.gz $f)
  echo "---------------------------------------------------------------------------------------------\n"
  echo $ff >>$logfile
  echo "running $ff" &>>$logfile;
  mat_cmd="load('$abip_func_params.mat'); params.func='${abipfunc}'; params.timelimit=${timelimit}; ${testfunc}('$f', '$abipname', params, 1e-$precision); exit;"
  echo $mat_cmd &>>$logfile
  full_cmd="nohup timeout $timelimit $MATLAB_HOME/bin/matlab -nodesktop -nodisplay -nosplash -noFigureWindows -r  \"${mat_cmd}\""
  echo $full_cmd
  eval ${full_cmd} &>>$logfile
done