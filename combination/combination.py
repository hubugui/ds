#!/usr/bin/python

import sys

case_idx = 1

def combination(array, bi, ei):
	global case_idx

	if bi > ei:
		return
	if bi == ei:
		print("{}>{}".format(case_idx, array[bi]))
		case_idx = case_idx + 1
		return

	# [1,2,3,4] = [1] + [1] & [2,3,4] + [2,3,4]

	# first
	combination(array, bi, bi)

	for i in range(bi+1, ei+1):
		for j in range(i, ei+1):
			print("{}>{}".format(case_idx, array[bi])),
			case_idx = case_idx + 1

			for k in range(i, j+1):
				print(array[k]),
			print("")

	# exclusion first element
	combination(array, bi + 1, ei)	

if __name__ == "__main__":
	size = 4
	if len(sys.argv) > 1:
		size = int(sys.argv[1])

	array = [x for x in range(1, size+1)]
	combination(array, 0, size - 1)