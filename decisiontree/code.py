from sklearn import tree
import numpy as np 

trX = np.load("../tests/trX.npy")
trY = np.load("../tests/trY.npy")
tstX = np.load("../tests/tstX.npy")
tstY = np.load("../tests/tstY.npy")

clf = tree.DecisionTreeClassifier(max_depth = 20)
clf = clf.fit(trX,trY)

n = len(tstX)
s = 0
out = clf.predict(tstX)
for i in range(n):
	if tstY[i] == out[i]:
		s+=1

cm = confusion_matrix(tstY, out)
print cm

acc = float(s)/float(n)
acc *= 100.0
print "Accuracy is ",acc