import numpy as np
import pandas as pd
import sys

key ='google_pdhg'
fname = sys.argv[1]

df = pd.read_excel(fname)
df.set_index(['name', 'method'], inplace=True)
df_std = df.query(f"method == \'{key}\'")
df_std = df_std.droplevel(1)


def cal_dev_perc(row, k):
    try:
        return (row[k] - df_std[k].get(row.name[0])) / df_std[k].get(row.name[0])
    except:
        return np.nan


def cal_dev(row, k):
    try:
        return (row[k] - df_std[k].get(row.name[0]))
    except:
        return np.nan


df['more_iter'] = pd.to_numeric(df.apply(lambda row: cal_dev(row, 'iteration_num'), axis=1), errors='coerce')
df['more_time'] = pd.to_numeric(df.apply(lambda row: cal_dev(row, 'sol_time'), axis=1), errors='coerce')
df['std_time'] = df.apply(lambda row: df_std['sol_time'].get(row.name[0]), axis=1)
df['std_iter'] = df.apply(lambda row: df_std['iteration_num'].get(row.name[0]), axis=1)
df['more_iter_perc'] = pd.to_numeric(df['more_iter']/df['iteration_num'], errors='coerce')
df['more_time_perc'] = pd.to_numeric(df['more_time']/df['sol_time'], errors='coerce')
dfa = df.groupby(level=1).aggregate(
    {
        "more_iter": 'mean',
        "more_iter_perc": 'mean',
        "more_time": 'mean',
        "more_time_perc": 'mean'
    }
)

print(df.to_latex(longtable=True, multirow=True, multicolumn=True))
print(dfa.to_latex(longtable=True, multirow=True, multicolumn=True))
df.to_excel("1.xlsx")
dfa.to_excel("2.xlsx")