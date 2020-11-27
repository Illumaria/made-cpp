#include <iostream>
#include <functional>


typedef std::function<int (int)> Op;


Op compose (size_t n, Op ops[]) {
  // Idempotent function:
  Op result = [] (int x) -> int { return x; };
  if (n == 0)
    return result;

  // A function to chain ops functions:
  auto func =
    [] (Op prev, size_t i, Op ops[]) -> Op {
      return [prev, i, ops] (int x) -> int {
        return ops[i](prev(x));
      };
    };

  for (ssize_t i = n - 1; i >= 0; --i)
    result = func(result, i, ops);

  return result;
}


int main () {
  /// Simple tests:

  Op op1 =
    [] (int x) -> int {
      return x + 1;
    };

  auto op2 =
    [] (int p) -> Op {
      return [p] (int x) {
        return p * x;
      };
    };

  {
    Op ops[4] = {op1, op2(2), op1, op2(2)};
    if (compose(4, ops)(2) != 11) {
      std::cout << "FAILED AT TEST 1" << std::endl;
      return 0;
    }
  }

  {
    Op ops[8] = {op1, op2(2), op1, op1, op1, op2(2), op2(2), op1};
    if (compose(8, ops)(5) != 55) {
      std::cout << "FAILED AT TEST 2" << std::endl;
      return 0;
    }
  }

  {
    Op ops[1] = {op1};
    if (compose(1, ops)(3) != 4) {
      std::cout << "FAILED AT TEST 3" << std::endl;
      return 0;
    }
  }

  {
    Op ops[0] = {};
    if (compose(0, ops)(4) != 4) {
      std::cout << "FAILED AT TEST 4" << std::endl;
      return 0;
    }
  }

  {
    Op ops[4] = {op2(2), op2(3), op2(4), op2(5)};
    if (compose(4, ops)(1) != 120) {
      std::cout << "FAILED AT TEST 5" << std::endl;
      return 0;
    }
  }
}
