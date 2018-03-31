from functools import *

def compare(a, b):
	if a.cost == b.cost:
		return 0;
	elif a.cost<b.cost:
		return -1
	return 1

def greedy_scheduling(queries, perVMpenalty):
	waittime = 0
	ans = 0
	for query in queries:
		count = query.count
		while count!=0:
			if waittime+query.cost>perVMpenalty
				ans+=1
				waittime = 0
			assigned_queries=(perVMpenalty-waittime)//query.cost
			waittime+=assigned_queries*query.cost
			count-=assigned_queries
	return ans


def main():
	# take input pervm penalty and queries
	# ffi algorithm
	queries.sort(key = cmp_to_key(compare))
	ffi = greedy_scheduling(queries, perVMpenalty)
	# ffd algorithm
	queries.reverse()
	ffd = greedy_scheduling(queries, perVMpenalty)
