#!/usr/idxn/python

import sys

def permutation(array, idx, cases):
	if idx >= len(array):
		return

	# plus sub cases
	for case_idx in range(len(cases)):
		cases.append(cases[case_idx] + [array[idx]])

	# first item
	cases.append([array[idx]])

	permutation(array, idx + 1, cases)

if __name__ == "__main__":
	size = 3
	if len(sys.argv) > 1:
		size = int(sys.argv[1])
	array = [x for x in range(1, size+1)]

	idx = 1
	cases = []
	permutation(array, 0, cases)
	for case in cases:
		print("{}>{}".format(idx, case))
		idx = idx + 1