import numpy as np 
import random

trX = []
trY = []
tstX = []
tstY = []

n = 1000
t = 100

for i in range(n):
	a = random.uniform(1.0,100.0)
	b = random.uniform(1.0,25.0)
	c = random.uniform(1.0,10.0)
	d = random.uniform(1.0,40.0)
	l = [a,b,c,d]
	trX.append(l)
	trY.append(random.randrange(0,2))

for i in range(t):
	a = random.uniform(1.0,100.0)
	b = random.uniform(1.0,25.0)
	c = random.uniform(1.0,10.0)
	d = random.uniform(1.0,40.0)
	l = [a,b,c,d]
	tstX.append(l)
	tstY.append(random.randrange(0,2))

trX = np.array(trX)
trY = np.array(trY)
tstX = np.array(tstX)
tstY = np.array(tstY)

np.save("trX.npy",trX)
np.save("trY.npy",trY)
np.save("tstX.npy",tstX)
np.save("tstY.npy",tstY)