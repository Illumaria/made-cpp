# Problem 5: chunk_allocator

### Problem statement:
We need to implement a custom allocator whose interface is similar to the interface of the `std::allocator`.

The allocator must allocate a large chunk of memory on the first allocation request. All subsequent allocation requests must only return blocks of this chunk. If for some allocation request it is impossible to find a block of sufficient size, we need to try and allocate a new chunk (in case the requested number of bytes does not exceed max chunk size). Chunks must be put in a linked list; thus on allocation request we'll need to iterate over all the chunks in the list to check if we can find and return some already created block. This will greatly reduce memory fragmentation.

On deallocation request no actions are needed. However, we need to deallocate the memory in the destructor.

It is very important to provide for the possibility of copying the allocator, otherwise there's a chance of double memory deletion error occuring. To avoid this we need to have a counter of allocator instance users.

The class must be STL-compatible, i.e. allow for using the allocator for STL containers.
The following methods must be implemented:
- `default constructor`;
- `copy constructor`;
- `destructor`;
- `operator=`;
- `allocate`;
- `deallocate`;
- `construct`;
- `destroy`.

The following member types must be implemented:
- `value_type`;
- `pointer`;
- `const_pointer`;
- `reference`;
- `const_reference`;
- `size_type`;
- `difference_type`;
- `rebind`.

[std::allocator](https://en.cppreference.com/w/cpp/memory/allocator) on Cppreference.
