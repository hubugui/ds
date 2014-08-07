avl
==================

# compile

`
make
`

# test

* general case, fixed test data. detail refer to `remove.py` and `test.c`

`./remove.py`

* dynamic test data, depended array's permutations and combinations, from "0 0 0 0 0" to "5 5 5 5 5"

`./avl 6`

# kuan_array.c

array's permutations and combinations

# QA

* Q1. Why save substree height's difference instead of height in node?
* A1. per node's height need to refresh when rotate, but difference forever equal -1, 0, 1.