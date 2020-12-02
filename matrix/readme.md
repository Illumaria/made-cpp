# Problem 4: matrix

### Problem statement:
Implement class `Matrix` of `double` type numbers. The class must support the following methods:
- default constructor of an identity matrix of size `1×1`;
- default constructor of an identity matrix of a given size:
  - a non-square matrix should be initialized with ones on the main diagonal, zeros otherwise;
- copy constructor;
- copy assign operator;
- `get` and `set` methods:
  - should throw `OutOfBoundsException` in case of bad adressing;
- `resize` method:
  - new values should be initialized with zeros;
- `operator[]` for both dimensions, and also for constant matrices;
- `operator+`, `operator-`, `operator*` for scalar and `Matrix` arguments, composite assignment, unary plus and minus operators;
- `operator==` and `operator!=`;
- `det`, `transpose`,`transposed`, `trace` methods;
- `getRow` and `getColumn` methods: return given row/column of type `std::vector`;
- `operator<<`, `operator>>`:
  - `operator>>` takes size as its first argument, values after.

All arithmetic operations, as well as `det` and `trace` methods, must throw `SizeMismatchException` in case of matrix sizes mismatch.

Standard containers are forbidden to use for `Matrix` internal storage.

When comparing real numbers, use the provided `EPS` constant.
