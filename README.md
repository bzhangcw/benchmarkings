# Benchmarking Commercial and Open-Source Solvers for Linear Programming


## Dataset
Each dataset is managed seperately. We are interested in:

### LP relaxation of MIPLIB2017
  - cf. https://miplib.zib.de/
  - benchmark
  - collection: `a larger collection`

### Mittelmann's LP datasets. 
It is a mixture of datasets.
- Benchmark of Simplex LP solvers: http://plato.asu.edu/ftp/lpsimp.html
- Benchmark of Barrier LP solvers: http://plato.asu.edu/ftp/lpbar.html
- Large Network-LP Benchmark (commercial vs. free): http://plato.asu.edu/ftp/network.html

These datasets can be downloaded separately. Here we provide a [script](collect_lp_benchmark.sh)


### Recommended Organization

A recommended organization of datasets and solvers:

First, create a data directory, then follow links to separate datasets. 

An ideal organization may look like...

```
# @ the root directory of this repo

# data directory
data
├── miplib2017
├── miplib2017-collection
├── mittelmann
├── ofinterest
├── qplib
... 
# the solver libraries
google-pdlp   # link to FirstOrderLp.jl
abip-lp       # link to abip-lp
...
```

In each subdirectory (dataset), create `subset folders`, `target folders` for each tested solver, e.g.,
```
data/miplib2017-collection
...
# subset of datasets
#  in case you are only interested in a few...
├── subset1
├── subset2
...
# result folders
├── grb_sol_barrier
├── grb_sol_dual
├── grb_sol_simplex
├── pdhg_sol_1e-6
└── pdhg_sol_1e-8
```

## Setting up solvers

A `method` is defined by `solver + parameters`.

### Google PDLP

Use a slightly modified version of the original PDLP at branch chuwen@[brentian](https://github.com/brentian/FirstOrderLp.jl.git).

Make sure you are using the right branch.
```
git checkout chuwen
```

Initialize environment:

```
julia --project=scripts -e 'import Pkg; Pkg.instantiate()'
julia --project=benchmarking -e 'import Pkg; Pkg.instantiate()'
```

After setting up PDLP, you can create a link at the top of the benchmark repo here named after `google-pdlp`.

You may also use your own names.

```
ln -s <the path to FirstOrderLp.jl> google-pdlp
```

See [`run_all_google_pdhg.sh`](./run_all_google_pdhg.sh) to run batch tests. An example invocation,

```
zsh run_all_google_pdhg.sh -h
```

By default, it will run PDLP at precisions of `1e-6` and eps `1e-8`

### SCS

Using same repo, see [`run_all_scs.sh`](./run_all_scs.sh)

```
zsh run_all_scs.sh -h
```