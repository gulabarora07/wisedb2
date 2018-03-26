import random

num_temp = 12
num_qr = 20
num = 0
each = 300
ans = ""

f = open("../tests/"+"test-"+str(num_temp)+"-"+str(num_qr)+".txt",'wb')

def get_perm(q,i,sumt,last):
	global num
	global num_qr
	global num_temp
	global f
	if i == num_temp:
		if sumt != 0:
			return
		q.sort()
		q = q[::-1]
		cnt_temp = num_temp
		while q[cnt_temp-1] == 0:
			cnt_temp -= 1
		for j in range(each):
			num += 1
			vmpen = random.uniform(100,500)
			startup = random.uniform(0,50)
			# print num_temp,vmpen,startup
			f.write(str(cnt_temp)+" "+str(vmpen)+" "+str(startup)+"\n")
			for t in range(1,cnt_temp+1):
				qcost = random.uniform(0,80)
				f.write(str(t)+" "+str(qcost)+" "+str(q[t-1])+"\n")
				# print t,qcost,q[t-1]

		return 

	for j in range(last,sumt+1):
		q[i] = j
		get_perm(q,i+1,sumt-j,j)


def main():
	global num
	global num_qr
	global num_temp
	
	q = [0]*num_temp
	get_perm(q,0,num_qr,0)
	print "count is ",num
	
main()