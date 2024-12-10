// #ifndef UNIQUEPTR_H
// #define UNIQUEPTR_H
#pragma once

template <typename T> class UniquePtr {
public:
  UniquePtr(T *data) : data_(data){};
  ~UniquePtr() { delete data_; }
  UniquePtr(const UniquePtr &other) = delete;
  const T *get() { return data_; }

private:
  T *data_;
};

// ##endif // !UNIQUEPTR_H
