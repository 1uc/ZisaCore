#ifndef ZISA_INTEGER_CAST_HPP_ICHUW
#define ZISA_INTEGER_CAST_HPP_ICHUW

#include <zisa/config.hpp>

#include <limits>

namespace zisa {
namespace detail {
template <class To, class From>
class IntegerCast;

template <>
class IntegerCast<int, size_t> {
public:
  static ANY_DEVICE_INLINE int cast(size_t i) {
    assert(i <= size_t(std::numeric_limits<int>::max()));

    return int(i);
  }
};

template <>
class IntegerCast<size_t, int> {
public:
  static ANY_DEVICE_INLINE size_t cast(int i) {
    assert(i >= 0);
    return size_t(i);
  }
};

template <>
class IntegerCast<unsigned, size_t> {
public:
  static ANY_DEVICE_INLINE unsigned cast(size_t i) {
    assert(i <= size_t(std::numeric_limits<unsigned>::max()));
    return unsigned(i);
  }
};

template <>
class IntegerCast<size_t, unsigned> {
public:
  static ANY_DEVICE_INLINE size_t cast(unsigned i) {
    return size_t(i);
  }
};

template <>
class IntegerCast<unsigned long long int, long unsigned int> {
private:
  using To = unsigned long long int;
  using From = long unsigned int;

public:
  static ANY_DEVICE_INLINE To cast(From i) { return To(i); }
};

template <>
class IntegerCast<long unsigned int, unsigned long long int> {
private:
  using To = long unsigned int;
  using From = unsigned long long int;

public:
  static ANY_DEVICE_INLINE To cast(From i) {
    assert(i <= From(std::numeric_limits<To>::max()));
    return To(i);
  }
};

template <>
class IntegerCast<unsigned long, long> {
public:
  static ANY_DEVICE_INLINE unsigned long cast(long i) {
    assert(i >= 0);
    return (unsigned long)(i);
  }
};

template <>
class IntegerCast<long, unsigned long> {
public:
  static ANY_DEVICE_INLINE long cast(unsigned long i) {
    assert(i <= (unsigned long)(std::numeric_limits<long>::max()));
    return long(i);
  }
};

template <class Int>
class IntegerCast<Int, Int> {
public:
  static ANY_DEVICE_INLINE Int cast(Int i) { return i; }
};
}

template <class To, class From>
ANY_DEVICE_INLINE typename std::decay<To>::type integer_cast(From from) {
  return detail::IntegerCast<typename std::decay<To>::type,
                             typename std::decay<From>::type>::cast(from);
}

}

#endif // ZISA_INTEGER_CAST_HPP
