
#!/usr/bin/env python

import random
import sys

def insert_sort(array):
	for i in range(1, len(array)):
		j = i - 1
		while j > -1 and array[j] > array[i]:
			tmp = array[i]
			array[i] = array[j]
			array[j] = tmp
			i = i - 1
			j = j - 1

array = []
if len(sys.argv) > 1:
	digits = sys.argv[1].split(",")
	for digit in digits:
		array.append(int(digit))
else:
	length = 20
	for i in range(length):
		array.append(random.randint(0, length))

print "input\t{}".format(array)
insert_sort(array)
print "result\t{}".format(array)