from keras.models import Sequential
from keras.layers import *
from sklearn.preprocessing import LabelEncoder
from keras.utils import np_utils
from keras.optimizers import Adam
import keras

trX = np.load("../tests/ch_trX.npy")
trY = np.load("../tests/ch_trY.npy")
tstX = np.load("../tests/ch_tstX.npy")
tstY = np.load("../tests/ch_tstY.npy")

# trX = trX[:1000]
# trY = trY[:1000]
# tstX = tstX[:100]
# tstY = tstY[:100]
trY = keras.utils.to_categorical(trY, 11)

tstY = keras.utils.to_categorical(tstY, 11)
print trX.shape,trY.shape
model = Sequential()

model.add(Dense( 25,activation='relu',input_shape=(41,)))
model.add(Dense(16, activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(11,activation='softmax'))

adam=Adam(lr=0.00001)

model.compile(loss='categorical_crossentropy', optimizer=adam, metrics=['accuracy'])



print(model.summary())
model.fit(trX, trY, epochs=10, batch_size=64,verbose=1)
# Final evaluation of the model
scores = model.evaluate(tstX, tstY, verbose=0)
print "Scores: ",scores