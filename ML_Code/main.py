#!/usr/bin/python3
# Aviral Upadhyay
# Vandit Maheshwari
# Version 1.0
# Date May 7th, 2020


import os

import merger
import pandas as pd

# 类似于MySQL中的join函数和Excel中的vlookup函数。它的作用是可以根据一个或多个键将不同的DatFrame链接起来
# if not os.path.isfile("Transformed Data/Transformed_Co"):
# 	merger.mergerCo()
# 	print("Controlled group file created")
# else:
# 	print("Controlled group file already exist, using that")
# if not os.path.isfile("Transformed Data/Transformed_Pt"):
# 	merger.mergerPt()
# 	print("Patient file created")
# else:
# 	print("Patient file already exist, using that")


df_co = pd.read_csv('Transformed Data/Transformed_Co', index_col=0)
df_pt = pd.read_csv('Transformed Data/Transformed_Pt', index_col=0)

# print("\n\n\nRandom Forest\n\n")
# import Random_Forest
#
# Random_Forest.randomForest(df_co, df_pt)
# print("\n\n\nKNN\n\n")
# import KNN
#
# KNN.kNN(df_co, df_pt)
# print("\n\n\nLinear SVM\n\n")
# import SVM_Linear
#
# SVM_Linear.svmLinear(df_co, df_pt)
# print("\n\n\nPolynomial SVM\n\n")
# import SVM_Poly
#
# SVM_Poly.svmPoly(df_co, df_pt)
# print("\n\n\nSigmoid SVM\n\n")
# import SVM_Sigmoid
#
# SVM_Sigmoid.svmSigmoid(df_co, df_pt)
import plot1

plot1.plot()
