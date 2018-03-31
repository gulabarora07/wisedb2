import numpy as np
import pandas
from keras.models import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from keras.utils import np_utils
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import KFold
from sklearn.pipeline import Pipeline

trX = np.load("../tests/ch_trX.npy")
trY = np.load("../tests/ch_trY.npy")
tstX = np.load("../tests/ch_tstX.npy")
tstY = np.load("../tests/ch_tstY.npy")

# trX = np.concatenate(trX,tstX)
# trY = np.concatenate(trY,tstY)

seed = 7
np.random.seed(seed)

encoder = LabelEncoder()
encoder.fit(trY)
encoded_Y = encoder.transform(trY)
dummy_y = np_utils.to_categorical(encoded_Y)

def baseline_model():
	model = Sequential()
	model.add(Dense(8, input_dim=41, init='normal', activation='relu'))
	model.add(Dense(11, init='normal', activation='sigmoid'))
	model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
	return model


estimator = KerasClassifier(build_fn=baseline_model, nb_epoch=200, batch_size=5, verbose=0)
kfold = KFold(n_splits=10, shuffle=True, random_state=seed)
results = cross_val_score(estimator, trX, dummy_y, cv=kfold)
print("Baseline: %.2f%% (%.2f%%)" % (results.mean()*100, results.std()*100))