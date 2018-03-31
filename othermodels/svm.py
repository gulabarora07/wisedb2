from sklearn.metrics import confusion_matrix
from sklearn.svm import SVC
import numpy as np

trX = np.load("../tests/ch_trX.npy")
trY = np.load("../tests/ch_trY.npy")
tstX = np.load("../tests/ch_tstX.npy")
tstY = np.load("../tests/ch_tstY.npy")

print len(trX)

trX = trX[:10000]
trY = trY[:10000]
tstX = tstX[:1000]
tstY = tstY[:1000]

svm_model_linear = SVC(kernel = 'linear', C = 1).fit(trX, trY)
svm_predictions = svm_model_linear.predict(tstX)
 
accuracy = svm_model_linear.score(tstX, tstY)
cm = confusion_matrix(y_test, svm_predictions)

print cm
print "Accuracy is ",accuracy