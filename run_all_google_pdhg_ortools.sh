# /*
#  * Created Date: Monday, October 18th 2021, 11:29:23 am
#  * Author: C. Zhang
#  *
#  * Copyright (c) 2022
#  */

if [ "$#" -ne 4 ]; then
  echo "Script for running Google PDLP in batch mode..."
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <eps>" 1>&2
  exit -1
fi

# params
if [ -z $pdhgsrc ]; then
  echo "'pdhgsrc' unset!"
  echo "set your google-ortools directory first 'pdhgsrc' "
  exit
fi

if [ ! -d $pdhgsrc ]; then
  echo "pdhg not set up here!"
  echo "link your pdgh directory to './google-pdlp' "
fi
wdir=$(pwd)
# test set
set=$1
prefix=$2
timelimit=$3
precision=$4
eps=1e-$precision

name=pdhg_cpp_1e-${precision}
phdg=$set/$name
logfile=$set/$name.log

mkdir -p $phdg

cd $wdir/$pdhgsrc
echo "running $pdhgsrc with $precision" > $logfile
for f in $(/bin/ls $set/$prefix/*.mps); do

  ff=$(basename -s .mps $f)
  cmd="cmake-build-release/bin/solve --solver=pdlp \
    --dump_response ${phdg}/$ff.rep \
    --dump_request ${phdg}/$ff.req \
    --input $f \
    --dump_format json &>> $logfile"

  echo $cmd
  eval $cmd

done
