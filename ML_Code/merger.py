#!/usr/bin/python3
# Aviral Upadhyay
# Vandit Maheshwari
# Version 1.0
# Date May 7th, 2020


import pandas as pd
import numpy as np
from sklearn import decomposition
import os
import scipy.stats as sc
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.svm import SVC


# 正常人文件：92个
# 患者文件：214个
# 每个文件里有16列左右脚脚底坐标的压力数据，还2列左脚右脚那八个压力数据总和的数据
# merger文件就是把所有正常人的数据和患者数据分别整合到一个文件里，文件中的每一条数据代表一个人
# 每条数据含有左脚、右脚每个压力传感器采集数据的 "Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis"
# 还有采集时间、左脚总和、右脚总和这两列的"Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis"
#                            最小值、最大值、标准差、中值、平均值、    峰度     、   偏态
# 其中每列共有133个数据

def mergerCo():
    count = 0

    for name in os.listdir('CSV'):
        if 'Co' in name:
            count += 1

    files = []

    for name in os.listdir('CSV'):
        if 'Co' in name:
            files.append('CSV/' + name)

    pathco = 'Transformed Data/Transformed_Co'

    # df2 = pd.DataFrame(columns = [col + string for col in df.columns for string in ["Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis", "Moment"]])
    i = 0
    df2 = pd.DataFrame()
    for fname in files:

        df = pd.read_csv(fname)
        for col in df.columns:
            for x in ["Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis"]:
                colname = col + x
                if x == 'Min':
                    df2.loc[i, colname] = df[col].min(axis=0)

                if x == 'Max':
                    df2.loc[i, colname] = df[col].max(axis=0)

                if x == 'Std':
                    df2.loc[i, colname] = df[col].std(axis=0)

                if x == 'Med':
                    df2.loc[i, colname] = df[col].median(axis=0)

                if x == 'Avg':
                    df2.loc[i, colname] = df[col].mean(axis=0)
                if x == 'Skewness':
                    df2.loc[i, colname] = df[col].skew(axis=0)

                if x == 'Kurtosis':
                    df2.loc[i, colname] = df[col].kurtosis(axis=0)

        i += 1
        print("{} files completed out of {}".format(i, count))

    df2 = df2.dropna(thresh=50)
    df2.to_csv(pathco)


def mergerPt():
    count = 0

    for name in os.listdir('CSV'):
        if 'Pt' in name:
            count += 1

    files = []

    for name in os.listdir('CSV'):
        if 'Pt' in name:
            files.append('CSV/' + name)

    pathpt = 'Transformed Data/Transformed_Pt'

    # df2 = pd.DataFrame(columns = [col + string for col in df.columns for string in ["Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis", "Moment"]])
    i = 0

    df4 = pd.DataFrame()
    for fname in files:

        df3 = pd.read_csv(fname)
        for col in df3.columns:
            for x in ["Min", "Max", "Std", "Med", "Avg", "Skewness", "Kurtosis"]:
                colname = col + x
                if x == 'Min':
                    df4.loc[i, colname] = df3[col].min(axis=0)

                if x == 'Max':
                    df4.loc[i, colname] = df3[col].max(axis=0)

                if x == 'Std':
                    df4.loc[i, colname] = df3[col].std(axis=0)

                if x == 'Med':
                    df4.loc[i, colname] = df3[col].median(axis=0)

                if x == 'Avg':
                    df4.loc[i, colname] = df3[col].mean(axis=0)
                if x == 'Skewness':
                    df4.loc[i, colname] = df3[col].skew(axis=0)

                if x == 'Kurtosis':
                    df4.loc[i, colname] = df3[col].kurtosis(axis=0)

        i += 1
        print("{} files completed out of {}".format(i, count))

    df4 = df4.dropna(thresh=50)

    df4

    df4.to_csv(pathpt)

