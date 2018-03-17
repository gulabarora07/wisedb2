from sklearn import tree
import numpy as np 

trX = np.load("trX.npy")
trY = np.load("trY.npy")
tstX = np.load("tstX.npy")
tstY = np.load("tstY.npy")

print trX
print trY
print tstX
print tstY

clf = tree.DecisionTreeClassifier()
clf = clf.fit(trX,trY)

n = 100
s = 0
out = clf.predict(tstX)
for i in range(n):
	if tstY[i] == out[i]:
		s+=1

print s," out of ",n
