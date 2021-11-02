offinterest=ofinterest.txt

for l in $(cat ${ofinterest}); do
  python gurobi_presolve.py data/miplib2017-collection/original/$l*.mps.gz data/miplib2017-collection/grb_presolved
done
