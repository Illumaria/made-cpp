#include "list.h"

/****************************************
 * ITERATOR
 ****************************************/

template <typename T, typename Alloc>
task::list<T, Alloc>::iterator::iterator(Node* current) : ptr(current) {}

template <typename T, typename Alloc>
task::list<T, Alloc>::iterator::iterator(const iterator& other)
    : ptr(other.ptr) {}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator&
task::list<T, Alloc>::iterator::operator=(const iterator& other) {
  ptr = other.ptr;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator&
task::list<T, Alloc>::iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator
task::list<T, Alloc>::iterator::operator++(int) {
  auto temp = *this;
  ++*this;
  return temp;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator::reference
task::list<T, Alloc>::iterator::operator*() const {
  return *(ptr->data);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator::pointer
task::list<T, Alloc>::iterator::operator->() const {
  return ptr->data;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator&
task::list<T, Alloc>::iterator::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator
task::list<T, Alloc>::iterator::operator--(int) {
  auto temp = *this;
  --*this;
  return temp;
}

template <typename T, typename Alloc>
bool task::list<T, Alloc>::iterator::operator==(const iterator& other) const {
  return ptr == other.ptr;
}

template <typename T, typename Alloc>
bool task::list<T, Alloc>::iterator::operator!=(const iterator& other) const {
  return ptr != other.ptr;
}

/****************************************
 * CONST_ITERATOR
 ****************************************/

template <typename T, typename Alloc>
task::list<T, Alloc>::const_iterator::const_iterator(Node* current)
    : ptr(current) {}

template <typename T, typename Alloc>
task::list<T, Alloc>::const_iterator::const_iterator(const iterator& other)
    : ptr(other.ptr) {}

template <typename T, typename Alloc>
task::list<T, Alloc>::const_iterator::const_iterator(
    const const_iterator& other)
    : ptr(other.ptr) {}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator&
task::list<T, Alloc>::const_iterator::operator=(const const_iterator& other) {
  ptr = other.ptr;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator&
task::list<T, Alloc>::const_iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator
task::list<T, Alloc>::const_iterator::operator++(int) {
  auto temp = *this;
  ++*this;
  return temp;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator::reference
task::list<T, Alloc>::const_iterator::operator*() const {
  return *(ptr->data);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator::pointer
task::list<T, Alloc>::const_iterator::operator->() const {
  return ptr->data;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator&
task::list<T, Alloc>::const_iterator::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator
task::list<T, Alloc>::const_iterator::operator--(int) {
  auto temp = *this;
  --*this;
  return temp;
}

template <typename T, typename Alloc>
bool task::list<T, Alloc>::const_iterator::operator==(
    const const_iterator& other) const {
  return ptr == other.ptr;
}

template <typename T, typename Alloc>
bool task::list<T, Alloc>::const_iterator::operator!=(
    const const_iterator& other) const {
  return ptr != other.ptr;
}

/****************************************
 * LIST CONSTRUCTORS & DESTRUCTORS
 ****************************************/

template <typename T, typename Alloc>
task::list<T, Alloc>::list() : list(Alloc()) {}

template <typename T, typename Alloc>
task::list<T, Alloc>::list(const Alloc& alloc) : _size(0), _allocator(alloc) {
  head = _node_allocator.allocate(1);
  _node_allocator.construct(head);
  head->next = head;
  head->prev = head;
}

template <typename T, typename Alloc>
task::list<T, Alloc>::list(std::size_t count, const Alloc& alloc)
    : list(alloc) {
  for (std::size_t i = 0; i < count; ++i) emplace_back();
}

template <typename T, typename Alloc>
task::list<T, Alloc>::list(std::size_t count, const T& value,
                           const Alloc& alloc)
    : list(alloc) {
  for (std::size_t i = 0; i < count; ++i) push_back(value);
}

template <typename T, typename Alloc>
task::list<T, Alloc>::list(const list<T, Alloc>& other)
    : list(std::allocator_traits<allocator_type>::
               select_on_container_copy_construction(other.get_allocator())) {
  _node_allocator = other._node_allocator;
  for (auto i = other.cbegin(); i != other.cend(); ++i) push_back(*i);
}

template <typename T, typename Alloc>
task::list<T, Alloc>::list(list<T, Alloc>&& other)
    : head(other.head),
      _size(other._size),
      _allocator(std::move(other._allocator)),
      _node_allocator(std::move(other._node_allocator)) {
  other.head = _node_allocator.allocate(1);
  _node_allocator.construct(other.head);
  other.head->next = other.head;
  other.head->prev = other.head;
  other._size = 0;
}

template <typename T, typename Alloc>
task::list<T, Alloc>::~list() {
  clear();
  _node_allocator.destroy(head);
  _node_allocator.deallocate(head, 1);
}

/****************************************
 * LIST OPERATORS
 ****************************************/

template <typename T, typename Alloc>
task::list<T, Alloc>& task::list<T, Alloc>::operator=(
    const list<T, Alloc>& other) {
  if (this == &other) return *this;

  clear();

  _allocator = other._allocator;
  _node_allocator = other._node_allocator;

  for (auto i = other.cbegin(); i != other.cend(); ++i) push_back(*i);

  return *this;
}

template <typename T, typename Alloc>
task::list<T, Alloc>& task::list<T, Alloc>::operator=(list<T, Alloc>&& other) {
  if (this == &other) return *this;

  clear();

  head = other.head;
  _size = other._size;
  _allocator = other._allocator;
  _node_allocator = other._node_allocator;

  other.head = _node_allocator.allocate(1);
  _node_allocator.construct(other.head);
  other.head->next = other.head;
  other.head->prev = other.head;
  other._size = 0;

  return *this;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::begin() {
  return iterator(head->next);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::end() {
  return iterator(head);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::reverse_iterator task::list<T, Alloc>::rbegin() {
  return reverse_iterator(end());
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::reverse_iterator task::list<T, Alloc>::rend() {
  return reverse_iterator(begin());
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator task::list<T, Alloc>::cbegin()
    const {
  return const_iterator(head->next);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_iterator task::list<T, Alloc>::cend()
    const {
  return const_iterator(head);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_reverse_iterator
task::list<T, Alloc>::crbegin() const {
  return const_reverse_iterator(cend());
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_reverse_iterator
task::list<T, Alloc>::crend() const {
  return const_reverse_iterator(cbegin());
}

/****************************************
 * LIST METHODS
 ****************************************/

template <typename T, typename Alloc>
typename task::list<T, Alloc>::reference task::list<T, Alloc>::back() {
  return *(--end());
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_reference task::list<T, Alloc>::back()
    const {
  return *(--cend());
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::clear() {
  while (!empty()) pop_back();
}

template <typename T, typename Alloc>
template <typename... Args>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::emplace(
    const_iterator pos, Args&&... args) {
  Node* tmp = new_(std::forward<Args>(args)...);
  tmp->next = pos.ptr;
  tmp->prev = pos.ptr->prev;
  pos.ptr->prev->next = tmp;
  pos.ptr->prev = tmp;

  return iterator(tmp);
}

template <typename T, typename Alloc>
template <typename... Args>
void task::list<T, Alloc>::emplace_back(Args&&... args) {
  emplace(cend(), std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
template <typename... Args>
void task::list<T, Alloc>::emplace_front(Args&&... args) {
  emplace(cbegin(), std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
bool task::list<T, Alloc>::empty() const {
  return _size == 0;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::erase(
    const_iterator pos) {
  Node* tmp = pos.ptr->next;
  if (pos.ptr != nullptr) {
    pos.ptr->next->prev = pos.ptr->prev;
    pos.ptr->prev->next = pos.ptr->next;
    delete_(pos.ptr);
  }
  return iterator(tmp);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::erase(
    const_iterator first, const_iterator last) {
  while (first != last) first = erase(first);
  return iterator(last.ptr);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::reference task::list<T, Alloc>::front() {
  return *begin();
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::const_reference task::list<T, Alloc>::front()
    const {
  return *cbegin();
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::allocator_type
task::list<T, Alloc>::get_allocator() const {
  return _allocator;
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::insert(
    const_iterator pos, const T& value) {
  Node* tmp = new_(value);
  tmp->prev = pos.ptr->prev;
  tmp->next = pos.ptr;
  pos.ptr->prev->next = tmp;
  pos.ptr->prev = tmp;

  return iterator(tmp);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::insert(
    const_iterator pos, T&& value) {
  return emplace(pos, std::move(value));
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::iterator task::list<T, Alloc>::insert(
    const_iterator pos, std::size_t count, const T& value) {
  if (count > 0) {
    list tmp(count, value, _allocator);
    iterator it = tmp.begin();
    splice(pos, std::move(tmp));
    return it;
  }

  return iterator(pos.ptr);
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::size_type task::list<T, Alloc>::max_size()
    const {
  return _Node_alloc_traits::max_size(_node_allocator);
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::merge(list<T, Alloc>& other) {
  merge(std::move(other));
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::merge(list<T, Alloc>&& other) {
  if (this != &other) {
    iterator first_1 = begin();
    iterator last_1 = end();
    iterator first_2 = other.begin();
    iterator last_2 = other.end();
    const size_type orig_size = other.size();

    while (first_1 != last_1 && first_2 != last_2)
      if (*first_2 < *first_1) {
        iterator next(first_2.ptr->next);
        first_2.ptr->prev = first_1.ptr->prev;
        first_2.ptr->next = first_1.ptr;
        first_1.ptr->prev->next = first_2.ptr;
        first_1.ptr->prev = first_2.ptr;
        first_2 = next;
      } else {
        ++first_1;
      }

    if (first_2 != last_2) {
      first_2.ptr->prev = last_1.ptr->prev;
      last_1.ptr->prev->next = first_2.ptr;
      last_1.ptr->prev = last_2.ptr->prev;
      last_2.ptr->prev->next = last_1.ptr;
    }

    _size += other._size;

    other.head = other._node_allocator.allocate(1);
    other._node_allocator.construct(other.head);
    other.head->next = other.head;
    other.head->prev = other.head;
    other._size = 0;
  }
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::pop_back() {
  erase(--end());
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::pop_front() {
  erase(begin());
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::push_back(const T& value) {
  insert(end(), value);
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::push_back(T&& value) {
  insert(end(), std::move(value));
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::push_front(const T& value) {
  insert(begin(), value);
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::push_front(T&& value) {
  insert(begin(), std::move(value));
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::remove(const T& value) {
  for (iterator x = begin(); x != end();) {
    if (*x == value)
      x = erase(x);
    else
      ++x;
  }
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::resize(std::size_t count) {
  while (_size != count) {
    if (_size > count)
      pop_back();
    else
      emplace_back();
  }
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::reverse() {
  Node* cur_head = head;
  Node* node = cur_head;

  while (true) {
    Node* next = node->next;
    node->next = node->prev;
    node->prev = next;

    if (next == cur_head) {
      break;
    }

    node = next;
  }
}

template <typename T, typename Alloc>
typename task::list<T, Alloc>::size_type task::list<T, Alloc>::size() const {
  return _size;
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::sort() {
  for (iterator i = begin(); i != end(); ++i)
    for (iterator j = i; j != end(); ++j)
      if (*i > *j) std::swap(i.ptr->data, j.ptr->data);
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::splice(const_iterator pos, list& other) {
  splice(pos, std::move(other));
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::splice(const_iterator pos, list&& other) {
  if (!other.empty() && get_allocator() == other.get_allocator()) {
    other.head->prev->next = pos.ptr;
    other.head->next->prev = pos.ptr->prev;

    pos.ptr->prev->next = other.head->next;
    pos.ptr->prev = other.head->prev;

    _size += other._size;
  }

  other.head = _node_allocator.allocate(1);
  _node_allocator.construct(other.head);
  other.head->next = other.head;
  other.head->prev = other.head;
  other._size = 0;
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::swap(list<T, Alloc>& other) {
  std::swap(head, other.head);
  std::swap(_size, other._size);
  std::swap(_allocator, other._allocator);
  std::swap(_node_allocator, other._node_allocator);
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::unique() {
  iterator first = begin();
  iterator last = end();

  if (first == last) return;

  iterator next = first;
  while (++next != last) {
    if (*first == *next)
      erase(next);
    else
      first = next;
    next = first;
  }
}

/****************************************
 * NODE METHODS
 ****************************************/

template <typename T, typename Alloc>
typename task::list<T, Alloc>::Node* task::list<T, Alloc>::new_() {
  Node* node = _node_allocator.allocate(1);
  _node_allocator.construct(node);

  node->data = _allocator.allocate(1);
  _allocator.construct(node->data);

  ++_size;

  return node;
}

template <typename T, typename Alloc>
template <typename... Args>
typename task::list<T, Alloc>::Node* task::list<T, Alloc>::new_(
    Args&&... args) {
  Node* node = _node_allocator.allocate(1);
  _node_allocator.construct(node);

  node->data = _allocator.allocate(1);
  _allocator.construct(node->data, std::forward<Args>(args)...);

  ++_size;

  return node;
}

template <typename T, typename Alloc>
void task::list<T, Alloc>::delete_(Node* node) {
  if (node->prev != nullptr) node->prev->next = node->next;

  if (node->next != nullptr) node->next->prev = node->prev;

  node->prev = nullptr;
  node->next = nullptr;

  _allocator.destroy(node->data);
  _node_allocator.deallocate(node, 1);

  node = nullptr;

  --_size;
}
