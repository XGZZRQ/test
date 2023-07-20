import pickle
import pandas as pd
import random

# 随机森林判断
with open('random_forest.pickle', 'rb') as fb:
    model = pickle.load(fb)
df_co = pd.read_csv('../Transformed Data/Transformed_Co', index_col=0)
df_pt = pd.read_csv('../Transformed Data/Transformed_Pt', index_col=0)

i = random.randint(0, 90)
pre_co = df_co.iloc[[i]]
pre_pt = df_pt.iloc[[i]]
if model.predict(pre_co)[0] == 0:
    print("正常")
else:
    print("患病")
if model.predict(pre_pt)[0] == 0:
    print("正常")
else:
    print("患病")

# # KNN判断
# with open('knn.pickle', 'rb') as fb:
#     model = pickle.load(fb)
# df_co = pd.read_csv('../Transformed Data/Transformed_Co', index_col=0)
# df_pt = pd.read_csv('../Transformed Data/Transformed_Pt', index_col=0)
#
# i = random.randint(0, 90)
# pre_co = df_co.iloc[[i]]
# pre_pt = df_pt.iloc[[i]]
# if model.predict(pre_co)[0] == 0:
#     print("正常")
# else:
#     print("患病")
# if model.predict(pre_pt)[0] == 0:
#     print("正常")
# else:
#     print("患病")

# # svm_linear判断
# with open('svm_linear.pickle', 'rb') as fb:
#     model = pickle.load(fb)
# df_co = pd.read_csv('../Transformed Data/Transformed_Co', index_col=0)
# df_pt = pd.read_csv('../Transformed Data/Transformed_Pt', index_col=0)
#
# i = random.randint(0, 90)
# pre_co = df_co.iloc[[i]]
# pre_pt = df_pt.iloc[[i]]
# if model.predict(pre_co)[0] == 0:
#     print("正常")
# else:
#     print("患病")
# if model.predict(pre_pt)[0] == 0:
#     print("正常")
# else:
#     print("患病")

# # svm_poly判断
# with open('svm_poly.pickle', 'rb') as fb:
#     model = pickle.load(fb)
# df_co = pd.read_csv('../Transformed Data/Transformed_Co', index_col=0)
# df_pt = pd.read_csv('../Transformed Data/Transformed_Pt', index_col=0)
#
# i = random.randint(0, 90)
# pre_co = df_co.iloc[[i]]
# pre_pt = df_pt.iloc[[i]]
# if model.predict(pre_co)[0] == 0:
#     print("正常")
# else:
#     print("患病")
# if model.predict(pre_pt)[0] == 0:
#     print(model.predict(pre_pt))
#     print("正常")
# else:
#     print("患病")

# # svm_sigmoid判断
# with open('svm_sigmoid.pickle', 'rb') as fb:
#     model = pickle.load(fb)
# df_co = pd.read_csv('../Transformed Data/Transformed_Co', index_col=0)
# df_pt = pd.read_csv('../Transformed Data/Transformed_Pt', index_col=0)
#
# i = random.randint(0, 90)
# pre_co = df_co.iloc[[i]]
# pre_pt = df_pt.iloc[[i]]
# if model.predict(pre_co)[0] == 0:
#     print("正常")
# else:
#     print("患病")
# if model.predict(pre_pt)[0] == 0:
#     print("正常")
# else:
#     print("患病")
