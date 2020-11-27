#pragma once

#include <bits/stdc++.h>
std::shared_ptr<int> a;

namespace task {

template <typename T>
class UniquePtr {
 public:
  using element_type = T;
  using pointer = T*;
  using reference = T&;

 private:
  pointer ptr;

 public:
  explicit UniquePtr(pointer ptr) noexcept;

  UniquePtr(UniquePtr&& other) noexcept;

  ~UniquePtr();

  pointer get() const noexcept;
  pointer release() noexcept;
  void reset(pointer p = pointer()) noexcept;
  void swap(UniquePtr& other) noexcept;

  UniquePtr& operator=(UniquePtr&& other) noexcept;
  reference operator*() const;
  pointer operator->() const noexcept;
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
 public:
  using element_type = T;
  using pointer = T*;
  using reference = T&;
  using size_type = std::size_t;

 private:
  pointer ptr;
  size_type* shared_cnt;
  size_type* weak_cnt;

 public:
  SharedPtr();

  explicit SharedPtr(T* ptr);

  SharedPtr(const SharedPtr& other) noexcept;

  SharedPtr(SharedPtr&& other) noexcept;

  explicit SharedPtr(const WeakPtr<T>& other);

  ~SharedPtr();

  pointer get() const noexcept;
  size_type use_count() const noexcept;
  void reset() noexcept;

  void reset(pointer ptr);

  void swap(SharedPtr& other) noexcept;

  SharedPtr& operator=(const SharedPtr& other) noexcept;

  SharedPtr& operator=(SharedPtr&& other) noexcept;

  reference operator*() const noexcept;
  pointer operator->() const noexcept;

  friend WeakPtr<element_type>;
};

template <typename T>
class WeakPtr {
 public:
  using element_type = T;
  using pointer = T*;
  using reference = T&;
  using size_type = std::size_t;

 private:
  pointer ptr;
  size_type* shared_cnt;
  size_type* weak_cnt;

 public:
  WeakPtr();

  WeakPtr(const WeakPtr& other) noexcept;

  WeakPtr(WeakPtr&& other) noexcept;

  WeakPtr(const SharedPtr<element_type>& other) noexcept;

  WeakPtr& operator=(const WeakPtr& other) noexcept;

  WeakPtr& operator=(WeakPtr&& other) noexcept;

  WeakPtr& operator=(const SharedPtr<element_type>& other) noexcept;

  ~WeakPtr();

  size_type use_count() const noexcept;
  SharedPtr<element_type> lock() const noexcept;
  bool expired() const noexcept;
  void reset() noexcept;
  void swap(WeakPtr& r) noexcept;

  friend SharedPtr<element_type>;
};

}  // namespace task

#include "smart_pointers.tpp"
