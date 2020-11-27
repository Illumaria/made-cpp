#include <iostream>

template <typename T, const size_t max_chunk_size = 8192>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  template <typename U>
  struct rebind {
    using other = Allocator<U>;
  };

 private:
  struct Chunk {
    pointer start;
    difference_type offset;
    Chunk* prev;
    size_type free_size;

    Chunk()
        : start(reinterpret_cast<pointer>(
              new uint8_t[max_chunk_size * sizeof(T)])),
          offset(0),
          prev(nullptr),
          free_size(max_chunk_size) {}

    ~Chunk() { delete[] start; }
  };
  Chunk* head;
  size_type* copies_cnt;

 public:
  Allocator() noexcept : head(nullptr), copies_cnt(new size_type(1)) {}

  Allocator(const Allocator& other) noexcept
      : head(other.head), copies_cnt(other.copies_cnt) {
    ++(*copies_cnt);
  }

  ~Allocator() {
    if (*copies_cnt > 1) {
      --(*copies_cnt);
      return;
    }

    while (head != nullptr) {
      head->~Chunk();
      head = head->prev;
    }
    delete copies_cnt;
  }

  Allocator<T>& operator=(const Allocator<T>& other) {
    if (this != &other) {
      head = other.head;
      --(*copies_cnt);
      copies_cnt = other.copies_cnt;
      ++(*copies_cnt);
    }
  }

  pointer allocate(const size_type n) {
    if (n > max_chunk_size) throw std::bad_alloc();

    // There are no chunks at all:
    if (head == nullptr) {
      Chunk* newChunk = new Chunk();
      head = newChunk;
    }

    // Check for free space in chunks:
    Chunk* prev = head;
    while (prev != nullptr) {
      if (prev->free_size >= n) {
        prev->free_size -= n;
        pointer temp = prev->start + prev->offset;
        prev->offset += static_cast<difference_type>(n);
        return temp;
      }
      prev = prev->prev;
    }

    // Create new chunk if there's no free space:
    Chunk* newChunk = new Chunk();
    newChunk->prev = head;
    newChunk->free_size -= n;
    newChunk->offset += static_cast<difference_type>(n);
    head = newChunk;
    return head->start;
  }

  void deallocate(pointer p, const size_type n) {}

  template <typename... Args>
  void construct(pointer p, Args&&... args) {
    new (reinterpret_cast<void*>(p)) T(std::forward<Args>(args)...);
  }

  void destroy(pointer p) { p->~T(); }

  size_type countInstances() const noexcept { return *copies_cnt; }

  size_type max_size() const noexcept { return max_chunk_size; }

  template <typename T1, typename T2, const size_t N>
  friend bool operator==(const Allocator<T1, N>&,
                         const Allocator<T2, N>&) noexcept;

  template <typename T1, typename T2, const size_t N>
  friend bool operator!=(const Allocator<T1, N>&,
                         const Allocator<T2, N>&) noexcept;
};

template <typename T1, typename T2, const size_t N>
bool operator==(const Allocator<T1, N>& lhs,
                const Allocator<T2, N>& rhs) noexcept {
  return lhs.head == rhs.head;
}

template <typename T1, typename T2, const size_t N>
bool operator!=(const Allocator<T1, N>& lhs,
                const Allocator<T2, N>& rhs) noexcept {
  return !(lhs.head == rhs.head);
}
