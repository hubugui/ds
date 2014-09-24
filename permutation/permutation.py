#!/usr/bin/python

import sys


def permutation(array, bi, ei):
	results = []

	if bi > ei:
		return []

	# first
	results.append([array[bi]])

	sub_results = permutation(array, bi+1, ei)
	results += sub_results
	size = len(sub_results)
	for i in range(0, size):
		results.append([array[bi]] + sub_results[i])
	return results

if __name__ == "__main__":
	size = 4
	if len(sys.argv) > 1:
		size = int(sys.argv[1])

	idx = 1
	array = [x for x in range(1, size+1)]	
	results = permutation(array, 0, size - 1)
	for item in results:
		print("{}>{}".format(idx, item))
		idx = idx + 1