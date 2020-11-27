namespace task {

template <typename T>
UniquePtr<T>::UniquePtr(pointer ptr) noexcept : ptr(ptr) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : ptr(other.release()) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
  ptr = pointer();
}

template <typename T>
typename UniquePtr<T>::pointer UniquePtr<T>::get() const noexcept {
  return ptr;
}

template <typename T>
typename UniquePtr<T>::pointer UniquePtr<T>::release() noexcept {
  pointer tmp = get();
  ptr = pointer();
  return tmp;
}

template <typename T>
void UniquePtr<T>::reset(pointer p) noexcept {
  ptr = p;
}

template <typename T>
void UniquePtr<T>::swap(UniquePtr& other) noexcept {
  std::swap(ptr, other.ptr);
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
  reset(other.release());
  return *this;
}

template <typename T>
typename UniquePtr<T>::reference UniquePtr<T>::operator*() const {
  return *get();
}

template <typename T>
typename UniquePtr<T>::pointer UniquePtr<T>::operator->() const noexcept {
  return get();
}

template <typename T>
SharedPtr<T>::SharedPtr()
    : ptr(pointer()),
      shared_cnt(new size_type(0)),
      weak_cnt(new size_type(0)) {}

template <typename T>
SharedPtr<T>::SharedPtr(pointer ptr)
    : ptr(ptr), shared_cnt(new size_type(1)), weak_cnt(new size_type(0)) {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept
    : ptr(other.ptr), shared_cnt(other.shared_cnt), weak_cnt(other.weak_cnt) {
  ++(*shared_cnt);
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept
    : ptr(other.ptr), shared_cnt(other.shared_cnt), weak_cnt(other.weak_cnt) {
  other.ptr = nullptr;
  other.shared_cnt = new size_type(0);
  other.weak_cnt = new size_type(0);
}

template <typename T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& other)
    : ptr(other.ptr), shared_cnt(other.shared_cnt), weak_cnt(other.weak_cnt) {
  ++(*shared_cnt);
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (*shared_cnt > 0) --(*shared_cnt);
  if (*shared_cnt == 0) {
    delete ptr;
    if (weak_cnt == 0) {
      delete shared_cnt;
      delete weak_cnt;
    }
  }
}

template <typename T>
typename SharedPtr<T>::pointer SharedPtr<T>::get() const noexcept {
  return ptr;
}

template <typename T>
typename SharedPtr<T>::size_type SharedPtr<T>::use_count() const noexcept {
  return ptr != nullptr ? *shared_cnt : 0;
}

template <typename T>
void SharedPtr<T>::reset() noexcept {
  SharedPtr().swap(*this);
}

template <typename T>
void SharedPtr<T>::reset(pointer ptr) {
  SharedPtr<T>(ptr).swap(*this);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& other) noexcept {
  std::swap(ptr, other.ptr);
  std::swap(shared_cnt, other.shared_cnt);
  std::swap(weak_cnt, other.weak_cnt);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) noexcept {
  SharedPtr<T>(other).swap(*this);
  return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
  SharedPtr<T>(std::move(other)).swap(*this);
  return *this;
}

template <typename T>
typename SharedPtr<T>::reference SharedPtr<T>::operator*() const noexcept {
  return *get();
}

template <typename T>
typename SharedPtr<T>::pointer SharedPtr<T>::operator->() const noexcept {
  return get();
}

template <typename T>
WeakPtr<T>::WeakPtr() = default;

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other) noexcept
    : ptr(other.ptr),
      shared_cnt(new size_type(0)),
      weak_cnt(new size_type(1)) {}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept
    : ptr(other.ptr), shared_cnt(other.shared_cnt), weak_cnt(other.weak_cnt) {
  other.ptr = nullptr;
  other.weak_cnt = new size_type(0);
  other.shared_cnt = new size_type(0);
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& other) noexcept
    : ptr(other.ptr), shared_cnt(other.shared_cnt), weak_cnt(other.weak_cnt) {
  ++(*weak_cnt);
}

template <typename T>
WeakPtr<T>::~WeakPtr() {
  if (weak_cnt != nullptr && *weak_cnt > 0) {
    --(*weak_cnt);
  }
  if (ptr == nullptr && weak_cnt != nullptr && *weak_cnt == 0 &&
      *shared_cnt == 0) {
    delete weak_cnt;
    delete shared_cnt;
  }
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) noexcept {
  if (*weak_cnt > 0) --(*weak_cnt);
  other.swap(*this);
  return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
  if (weak_cnt != nullptr && *weak_cnt > 0) --(*weak_cnt);
  WeakPtr<T>(other).swap(*this);
  return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other) noexcept {
  WeakPtr<T>(std::move(other)).swap(*this);
  return *this;
}

template <typename T>
typename WeakPtr<T>::size_type WeakPtr<T>::use_count() const noexcept {
  return ptr != nullptr ? *shared_cnt : 0;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept {
  return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
}

template <typename T>
bool WeakPtr<T>::expired() const noexcept {
  return use_count() == 0;
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
  WeakPtr().swap(*this);
}

template <typename T>
void WeakPtr<T>::swap(WeakPtr& other) noexcept {
  std::swap(ptr, other.ptr);
  std::swap(weak_cnt, other.weak_cnt);
  std::swap(shared_cnt, other.shared_cnt);
}

}  // namespace task
