#include <iostream>
#include <vector>

#include "allocator.h"

const size_t max_chunk_size = 1024;

class A {
 public:
  A(int x, int y) {}
};

int main() {
  // Default constructor:
  Allocator<int, max_chunk_size> alloc_1;
  if (alloc_1.countInstances() != 1) {
    std::cerr << "Incorrect number of Allocator<int> instances!\n";
    return 1;
  }

  Allocator<int>::value_type x = 123;

  // Copy constructor:
  Allocator<int, max_chunk_size> alloc_2(alloc_1);
  if (alloc_2.countInstances() != 2) {
    std::cerr << "Incorrect number of Allocator<int> instances!\n";
    return 1;
  }

  // Operator==:
  if (!(alloc_1 == alloc_2)) {
    std::cerr << "Error: operaror==\n";
    return 1;
  }

  // Operator!=:
  if (alloc_1 != alloc_2) {
    std::cerr << "Error: operaror!=\n";
    return 1;
  }

  // Allocate:
  int* arr_1 = alloc_2.allocate(max_chunk_size - 100);
  if (arr_1 == nullptr) {
    std::cerr << "Incorrect allocation via alloc_2!\n";
    return 1;
  }

  // Deallocate:
  alloc_2.deallocate(arr_1, 10);

  try {
    int* arr_2 = alloc_2.allocate(max_chunk_size + 100);
  } catch (std::bad_alloc e) {
  }

  int* p_1;
  alloc_2.construct(p_1, 3);
  alloc_2.construct(p_1 + 1, 4);
  alloc_2.destroy(p_1);

  // Operator=:
  Allocator<int, max_chunk_size> alloc_3 = alloc_2;
  if (alloc_2.countInstances() != 3) {
    std::cerr << "Incorrect number of Allocator<int> instances!\n";
    return 1;
  }

  Allocator<A, max_chunk_size> alloc_4;
  if (alloc_4.countInstances() != 1) {
    std::cerr << "Incorrect number of Allocator<A> instances!\n";
    return 1;
  }

  auto p_2 = alloc_4.allocate(1);
  alloc_4.construct(p_2, 1, 2);
  alloc_4.destroy(p_2);
  alloc_4.deallocate(p_2, 1);

  std::vector<A, Allocator<A, max_chunk_size>> vec;
  if (alloc_4.countInstances() != 1) {
    std::cerr << "Incorrect number of Allocator<A> instances!\n";
    return 1;
  }

  vec.push_back(A(1, 2));

  std::cout << "All tests passed!\n";

  return 0;
}
