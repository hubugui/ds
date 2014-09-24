#!/usr/bin/python

import sys

def permutation(array, bi, cases):
	if bi >= len(array):
		return

	# sub array
	permutation(array, bi+1, cases)

	# plus sub cases
	size = len(cases)
	for i in range(0, size):
		cases.append([array[bi]] + cases[i])

	# first item
	cases.append([array[bi]])

def go(array, cases):
	permutation(array, 0, cases)

if __name__ == "__main__":
	size = 4
	if len(sys.argv) > 1:
		size = int(sys.argv[1])
	array = [x for x in range(1, size+1)]

	idx = 1
	cases = []
	go(array, cases)
	for case in cases:
		print("{}>{}".format(idx, case))
		idx = idx + 1