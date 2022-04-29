fname = "datt.grb.sol"
fpdhg = "data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_primal.txt"

varnames = [i.split(" ")[0] for i in open(fname, 'r') if not '#' in i]

with open("data/miplib2017-collection/pdhg_sol_1e-6/pre_datt256_primal.txt.sol", 'w') as fout:
    lines = open(fpdhg, 'r')
    for idx, l in enumerate(lines):
        fout.write(f"{varnames[idx]}\t{l}")



