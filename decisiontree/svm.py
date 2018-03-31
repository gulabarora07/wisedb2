from sklearn.metrics import confusion_matrix
from sklearn.svm import SVC
import numpy as np

trX = np.load("../tests/trX.npy")
trY = np.load("../tests/trY.npy")
tstX = np.load("../tests/tstX.npy")
tstY = np.load("../tests/tstY.npy")
 
svm_model_linear = SVC(kernel = 'linear', C = 1).fit(trX, trY)
svm_predictions = svm_model_linear.predict(tstX)
 
accuracy = svm_model_linear.score(tstX, tstY)
cm = confusion_matrix(y_test, svm_predictions)

print cm
print "Accuracy is ",accuracy