/*
 * Copyright 2020 Mornie
 */


#pragma once
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>


namespace task {
  const double _EPS = 1e-7;


  template <typename T>
  std::istream& operator>>(std::istream& is, std::vector<T> &a) {
    size_t size;
    is >> size;
    if (size < 0)
      return is;
    a.resize(size);

    T value;
    for (size_t i = 0; i < size; ++i)
      is >> a[i];

    return is;
  }


  template <typename T>
  std::ostream& operator<<(std::ostream& os, const std::vector<T>& a) {
    for (auto& value : a)
      os << value << " ";
    os << '\n';

    return os;
  }


  template <typename T>
  std::vector<T> operator+(const std::vector<T>& a) {
    std::vector<T> result(a);

    return result;
  }


  template <typename T>
  std::vector<T> operator-(const std::vector<T>& a) {
    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
      result[i] = -a[i];

    return result;
  }


  template <typename T>
  std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
      result[i] = a[i] + b[i];

    return result;
  }


  template <typename T>
  std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
      result[i] = a[i] - b[i];

    return result;
  }


  template <typename T>
  double operator*(const std::vector<T>& a, const std::vector<T>& b) {
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
      result += a[i] * b[i];

    return result;
  }


  template <typename T>
  std::vector<T> operator%(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result(a.size());

    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];

    return result;
  }


  template <typename T>
  bool _is_zero_vector(const std::vector<T>& a) {
    for (const auto& value : a)
      if (value != 0)
        return false;

    return true;
  }


  template <typename T>
  bool operator||(const std::vector<T>& a, const std::vector<T>& b) {
    if (_is_zero_vector(b))
      return true;

    double lambda = a[0] / b[0];

    for (size_t i = 1; i < a.size(); ++i)
      if (fabs(a[i] - lambda * b[i]) > _EPS)
        return false;

    return true;
  }


  template <typename T>
  bool operator&&(const std::vector<T>& a, const std::vector<T>& b) {
    if (_is_zero_vector(b))
      return true;

    double lambda = a[0] / b[0];
    if (lambda < 0)
      return false;

    for (size_t i = 1; i < a.size(); ++i)
      if (fabs(a[i] - lambda * b[i]) > _EPS)
        return false;

    return true;
  }


  template <typename T>
  void reverse(std::vector<T>& v) {
    std::reverse(v.begin(), v.end());
  }


  template <typename T>
  std::vector<T> operator&(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
      result[i] = a[i] & b[i];

    return result;
  }

  template <typename T>
  std::vector<T> operator|(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
      result[i] = a[i] | b[i];

    return result;
  }


}  // namespace task
