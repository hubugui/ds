#!/usr/bin/python

import random
import sys

from subprocess import call

array = "30 15 60 7 20 40 80 4 10 17 25 50 1 6 8 22"

def execute(cmd):
    rc = call(cmd, shell=True)
    if rc != 0:
        sys.exit(rc)

def random_array(array):
    new_array = ""
    elements = array.split(" ")
    count = len(elements)

    for i in range(0, count):
        idx = random.randint(0, len(elements) - 1)
        if i < count - 1:
            new_array += elements.pop(idx) + " "
        else:
            new_array += elements.pop(idx)
    return new_array

def remove(array, element):
    cmd = "./avl %s %s" % (array, element)
    print("#remove %s, cmd=\"%s\"" % (element, cmd))
    execute(cmd)
    print("")

def remove_foreach(array):
    elements = array.split(" ")
    for element in elements:
        remove(array, element)

# make
execute("make")
print("")

print("#array={%s}" % (array))
remove_foreach(array)

# random array
array = random_array(array)
remove_foreach(array)
# print("#random array={%s}" % (array))