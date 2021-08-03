// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ZISA_INTEGER_CAST_HPP_ICHUW
#define ZISA_INTEGER_CAST_HPP_ICHUW

#include <zisa/config.hpp>

#include <limits>

namespace zisa {
namespace detail {
template <class To, class From>
class IntegerCast {
  static_assert(
      !std::is_same<To, To>::value,
      "zisa::detail::IntegerCast is not specialized for the given input types");
};

template <>
class IntegerCast<int, size_t> {
public:
  static constexpr ANY_DEVICE_INLINE int cast(size_t i) {
    return assert(i <= size_t(std::numeric_limits<int>::max())), int(i);
  }
};

template <>
class IntegerCast<size_t, int> {
public:
  static constexpr ANY_DEVICE_INLINE size_t cast(int i) {
    return assert(i >= 0), size_t(i);
  }
};

template <>
class IntegerCast<unsigned, size_t> {
public:
  static constexpr ANY_DEVICE_INLINE unsigned cast(size_t i) {
    return assert(i <= size_t(std::numeric_limits<unsigned>::max())),
           unsigned(i);
  }
};

template <>
class IntegerCast<size_t, unsigned> {
public:
  static constexpr ANY_DEVICE_INLINE size_t cast(unsigned i) {
    return size_t(i);
  }
};

template <>
class IntegerCast<unsigned long long int, unsigned long int> {
private:
  using To = unsigned long long int;
  using From = unsigned long int;

public:
  static constexpr ANY_DEVICE_INLINE To cast(From i) { return To(i); }
};

template <>
class IntegerCast<unsigned long int, unsigned long long int> {
private:
  using To = unsigned long int;
  using From = unsigned long long int;

public:
  static constexpr ANY_DEVICE_INLINE To cast(From i) {
    return assert(i <= From(std::numeric_limits<To>::max())), To(i);
  }
};

template <>
class IntegerCast<unsigned long, long> {
public:
  static constexpr ANY_DEVICE_INLINE unsigned long cast(long i) {
    return assert(i >= 0), (unsigned long)(i);
  }
};

template <>
class IntegerCast<long, unsigned long> {
public:
  static constexpr ANY_DEVICE_INLINE long cast(unsigned long i) {
    return assert(i <= (unsigned long)(std::numeric_limits<long>::max())),
           long(i);
  }
};

template <class Int>
class IntegerCast<Int, Int> {
public:
  static constexpr ANY_DEVICE_INLINE Int cast(Int i) { return i; }
};
}

template <class To, class From>
constexpr ANY_DEVICE_INLINE typename std::decay<To>::type
integer_cast(From from) {
  return detail::IntegerCast<typename std::decay<To>::type,
                             typename std::decay<From>::type>::cast(from);
}

}

#endif // ZISA_INTEGER_CAST_HPP
