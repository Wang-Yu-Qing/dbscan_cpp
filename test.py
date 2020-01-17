from sklearn.cluster import DBSCAN
import pandas as pd
import math


df = pd.read_csv('data/gaode_merge.csv')
df = df.iloc[:, [3, 4]]
result = DBSCAN(eps=0.01, min_samples=100, metric='euclidean').fit(df)
print(len(set(result.labels_)))


def dis(p1, p2):
    print(math.sqrt((p1[0]-p2[0])**2+(p1[1]-p2[1])**2))
