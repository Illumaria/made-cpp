# Problem 6: smart pointers

### Problem statement:
Implement simplified analogues of C++11 smart pointers: [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr), [`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr), [`std::weak_ptr`](https://en.cppreference.com/w/cpp/memory/weak_ptr).

- `UniquePtr`:
  - common pointer constructor;
  - move constructor;
  - move assignment operator;
  - destructor;
  - `operator*`;
  - `operator->`;
  - `get` method;
  - `release` method;
  - `reset` method;
  - `swap` method.

- `SharedPtr`:
  - common pointer constructor;
  - copy constructor;
  - move constructor;
  - copy assignment operator;
  - move assignment operator;
  - destructor;
  - `WeakPtr` constructor;
  - `operator*`;
  - `operator->`;
  - `get` method;
  - `use_count` method (returns the number of `SharedPtr`'s pointing to the same object);
  - `reset` method;
  - `swap` method.

- `WeakPtr`:
  - `SharedPtr` constructor;
  - copy constructor;
  - move constructor;
  - copy assignment operator;
  - move assignment operator;
  - `SharedPtr` assignment operator;
  - destructor;
  - `expired` method;
  - `use_count` method (returns the number of `SharedPtr`'s pointing to the same object);
  - `lock` method (returns `SharedPtr`);
  - `reset` method;
  - `swap` method.
