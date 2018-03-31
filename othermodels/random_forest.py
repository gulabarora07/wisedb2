from sklearn.ensemble import RandomForestClassifier
import numpy as np 
from sklearn.metrics import confusion_matrix

trX = np.load("../tests/ch_trX.npy")
trY = np.load("../tests/ch_trY.npy")
tstX = np.load("../tests/ch_tstX.npy")
tstY = np.load("../tests/ch_tstY.npy")

print len(trX),len(tstX)

clf = RandomForestClassifier()
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