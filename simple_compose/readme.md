# Problem 3: simple compose

### Problem statement:
Write a function to calculate function composition. It must take 2 arguments: number of functions and the functions themselves.

`compose` function may be recursive.

If `n = 0`, the function should return some idempotent function. If `n = 1`, it should return its only argument.

`main.cpp` contains some simple tests. It can be used to get the idea on how to instantiate operations (op1) and how to make these operations creators (op2).

It is forbidden to create any auxiliary functions outside of the `compose` function. `compose` should be considered a library function, and the fewer dependencies a library has, the easier it is to read, maintain, and extend it.
