if [ "$#" -ne 4 ]; then
  echo "Script for running Crossover for PDHG via COPT in batch mode..."
  echo "Usage: <dataset directory> <subset name> <time limit for each instance> <precision to use>" 1>&2
  echo "Example: zsh run_all_crs_google_pdhg.sh data/netlib grb_presolved 100 6 &"
  exit -1
fi

# test set
set=$1
prefix=$2
timelimit=$3
precision=$4
result=$set/pdhg_sol_1e-${precision}
cross=$set/crs.pdhg_sol_1e-${precision}

# crossover
crs_script=src/crossover_by_copt.py

mkdir -p $cross

logfile=$set/crs.pdhg_sol_1e-$precision.log
if [ -f $logfile ]; then
  rm $logfile
fi

# no need to run scs at 1e-8
for f in $(/bin/ls $set/$prefix); do

  ff=$(basename -s .mps.gz $f)
  echo $ff >>$logfile
  primal=$result/${ff}_primal.txt
  dual=$result/${ff}_dual.txt
  cmd="timeout $timelimit python $crs_script $set/$prefix/$f $primal $dual $cross &>>$logfile"
  echo $cmd &>>$logfile
  eval $cmd
done
