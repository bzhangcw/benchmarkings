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

df[['iteration_num', 'sol_time']] = df[['iteration_num', 'sol_time']].apply(
  pd.to_numeric, errors='coerce'
)
df['success'] = df['sol_status'].apply(lambda x: x.lower()).apply(lambda x: 'solved' in x or 'optimal' in x)
df['more_iter'] = pd.to_numeric(df.apply(lambda row: cal_dev(row, 'iteration_num'), axis=1), errors='coerce')
df['more_time'] = pd.to_numeric(df.apply(lambda row: cal_dev(row, 'sol_time'), axis=1), errors='coerce')
df['std_time'] = df.apply(lambda row: df_std['sol_time'].get(row.name[0]), axis=1)
df['std_iter'] = df.apply(lambda row: df_std['iteration_num'].get(row.name[0]), axis=1)
df['more_iter_perc'] = pd.to_numeric(df['more_iter'].divide(df['std_iter']), errors='coerce')
df['more_time_perc'] = pd.to_numeric(df['more_time'].divide(df['std_time']), errors='coerce')
dfa = df.groupby(level=1).aggregate(
    {
        "more_iter": 'mean',
        "more_iter_perc": 'mean',
        "more_time": 'mean',
        "more_time_perc": 'mean',
				"iteration_num": 'mean',
				"sol_time": 'mean',
				"success": 'sum'
    }
)

print(df.to_latex(longtable=True, multirow=True, multicolumn=True))
print(dfa.to_latex(longtable=True, multirow=True, multicolumn=True))
df.to_excel("1.xlsx")
dfa.to_excel("2.xlsx")
