from xgboost import XGBClassifier
import numpy as np 
from sklearn.metrics import confusion_matrix

trX = np.load("../tests/ch_trX.npy")
trY = np.load("../tests/ch_trY.npy")
tstX = np.load("../tests/ch_tstX.npy")
tstY = np.load("../tests/ch_tstY.npy")

print len(trX),len(tstX)

model = XGBClassifier()
model.fit(trX, trY)

# make predictions for test data
y_pred = model.predict(tstX)
predictions = [round(value) for value in y_pred]


cm = confusion_matrix(tstY, predictions)
print cm

accuracy = accuracy_score(tstY, predictions)
print("Accuracy: %.2f%%" % (accuracy * 100.0))