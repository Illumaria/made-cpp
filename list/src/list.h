#pragma once
#include <iterator>

namespace task {

template <typename T, typename Alloc = std::allocator<T>>
class list {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using allocator_type = Alloc;

  class iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;

  class const_iterator;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 private:
  struct Node {
    pointer data;
    Node* prev;
    Node* next;
  };

  using _Node_alloc_type =
      typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
  using _Node_alloc_traits = std::allocator_traits<_Node_alloc_type>;

  Node* new_();

  template <typename... Args>
  Node* new_(Args&&... args);

  void delete_(Node* node);

 private:
  Node* head;
  size_type _size;
  allocator_type _allocator;
  _Node_alloc_type _node_allocator;

 public:
  list();
  explicit list(const Alloc& alloc);
  list(std::size_t count, const T& value, const Alloc& alloc = Alloc());
  explicit list(std::size_t count, const Alloc& alloc = Alloc());
  list(const list<T, Alloc>& other);
  list(list<T, Alloc>&& other);

  list<T, Alloc>& operator=(const list<T, Alloc>& other);
  list<T, Alloc>& operator=(list<T, Alloc>&& other);

  ~list();

  size_type size() const;
  bool empty() const;

  void push_front(T&& value);
  void push_back(T&& value);
  void push_front(const T& value);
  void push_back(const T& value);
  void pop_front();
  void pop_back();

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  reverse_iterator rbegin();
  reverse_iterator rend();

  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  iterator insert(const_iterator pos, const T& value);
  iterator insert(const_iterator pos, T&& value);
  iterator insert(const_iterator pos, std::size_t count, const T& value);

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  allocator_type get_allocator() const;

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const;

  size_type max_size() const;
  void clear();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);

  template <typename... Args>
  void emplace_back(Args&&... args);

  template <typename... Args>
  void emplace_front(Args&&... args);

  void resize(std::size_t count);
  void swap(list<T, Alloc>& other);

  void merge(list<T, Alloc>& other);
  void merge(list<T, Alloc>&& other);
  void splice(const_iterator pos, list& other);
  void splice(const_iterator pos, list&& other);
  void remove(const T& value);
  void reverse();
  void unique();
  void sort();

  class iterator {
   private:
    friend class list<T, Alloc>;

   public:
    using value_type = list<T, Alloc>::value_type;
    using pointer = list<T, Alloc>::pointer;
    using reference = list<T, Alloc>::reference;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

   private:
    explicit iterator(Node* current);
    Node* ptr;

   public:
    iterator() = delete;
    iterator(const iterator&);
    iterator& operator=(const iterator&);

    iterator& operator++();
    iterator operator++(int);
    reference operator*() const;
    pointer operator->() const;
    iterator& operator--();
    iterator operator--(int);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
  };

  class const_iterator {
   private:
    friend class list<T, Alloc>;

   public:
    using value_type = list<T, Alloc>::value_type;
    using pointer = list<T, Alloc>::pointer;
    using reference = list<T, Alloc>::reference;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

   private:
    explicit const_iterator(Node* current);
    Node* ptr;

   public:
    const_iterator() = delete;
    const_iterator(const iterator&);
    const_iterator(const const_iterator&);
    const_iterator& operator=(const const_iterator&);

    const_iterator& operator++();
    const_iterator operator++(int);
    reference operator*() const;
    pointer operator->() const;
    const_iterator& operator--();
    const_iterator operator--(int);

    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
  };

  static_assert(std::is_same<typename Alloc::value_type, value_type>::value,
                "Alloc::value_type must be the same type as value_type");
};

}  // namespace task

#include "list.cpp"
