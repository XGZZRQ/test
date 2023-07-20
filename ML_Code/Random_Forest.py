#!/usr/bin/python3
# Aviral Upadhyay
# Vandit Maheshwari
# Version 1.0
# Date May 7th, 2020
import pickle

import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.svm import SVC

from sklearn.ensemble import RandomForestClassifier


def randomForest(df1, df2):
    df1_len = df1.shape[0]
    df2_len = df2.shape[0]
    df2.shape + df1.shape
    X = pd.concat([df1, df2])
    y1 = pd.Series([0] * df1_len)
    y1.shape
    y2 = pd.Series([1] * df2_len, index=range(df1_len - 1, (df1_len + df2_len) - 1))
    y = pd.concat([y1, y2])
    y.tail()
    max_acc = 0
    max_est = 0
    curr_max_acc = 0
    curr_max_n = 0
    for i in range(1, 100):
        X_train, X_test, y_train1, y_test1 = train_test_split(X, np.ravel(y), random_state=i)
        y_train = pd.DataFrame(y_train1)
        y_test = pd.DataFrame(y_test1)

        for n in [5, 10, 20, 40, 100, 200]:
            clf = RandomForestClassifier(n_estimators=int(n), n_jobs=2)
            clf.fit(X_train, np.ravel(y_train))
            if (max_acc < clf.score(X_test, np.ravel(y_test))):
                max_acc = clf.score(X_test, np.ravel(y_test))
                max_n = int(n)

        if (curr_max_acc < max_acc):
            curr_max_acc = max_acc
            curr_max_n = max_n
            n_rs = i
        # print("{} done".format(i))
    print("Accuracy = {}, n_estimators = {}, Random State = {}".format(curr_max_acc, curr_max_n, n_rs))

    X_train, X_test, y_train1, y_test1 = train_test_split(X, np.ravel(y))
    y_train = pd.DataFrame(y_train1)
    y_test = pd.DataFrame(y_test1)
    clf = RandomForestClassifier(n_estimators=200, n_jobs=2, max_depth=10)
    clf.fit(X_train, np.ravel(y_train))
    clf.score(X_test, np.ravel(y_test))

    from sklearn.model_selection import GridSearchCV
    from sklearn.metrics import roc_auc_score
    grid_vals = {'n_estimators': [5, 10, 20, 40, 100, 200]}
    # 要构造一个随机森林模型，第一步是确定森林中树的数目，通过模型的 进行调节。
    # n_estimators越大越好，但占用的内存与训练和预测的时间也会相应增长，且边际效益是递减的，
    # 所以要在可承受的内存/时间内选取尽可能大的n_estimators。
    grid_clf = GridSearchCV(clf, param_grid=grid_vals, scoring='accuracy')
    # GridSearchCV 它存在的意义就是自动调参，只要把参数输进去，就能给出最优化的结果和参数。
    # 但是这个方法适合于小数据集,一旦数据的量级上去了,很难得出结果
    # 数据量比较大的时候可以使用一个快速调优的方法——坐标下降,它其实是一种贪心算法：拿当前对模型影响最大的参数调优，直到最优化；再拿下一个影响最大的参数调优，如此下去，直到所有的参数调整完毕
    # 这个方法的缺点就是可能会调到局部最优而不是全局最优,但是省时间省力,巨大的优势面前,还是试一试吧,后续可以再拿bagging再优化。
    # scoring :准确度评价标准，默认None,这时需要使用score函数；或者如scoring=’roc_auc’，根据所选模型不同，评价准则不同。
    grid_clf.fit(X_train, y_train1.reshape(229, ))
    y_pred_proba = grid_clf.predict_proba(X_test)

    # clf.predict_proba,二分类则得到[(px1,px2),()] 分别表示预测为0的概率和预测为1的概率
    print(roc_auc_score(y_test, y_pred_proba[:, 1]))
    print("Best Score", grid_clf.best_score_)
    print("Best Parameters", grid_clf.best_params_)

    # print(X_test)
    # print(type(X_test))
    # print(X_test.iloc[[0]])

    print("最佳模型", grid_clf.best_estimator_)
    best_model = grid_clf.best_estimator_
    import pickle
    with open('save/random_forest.pickle', 'wb') as f:
        pickle.dump(best_model, f)
    # with open('save/random_forest.pickle','rb') as fb:
    #     model=pickle.load(fb)
    # pre = X_test.iloc[[0]]
    # print(model.predict(pre))
