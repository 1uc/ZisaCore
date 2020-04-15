#ifndef ZISA_INTEGER_CAST_HPP_ICHUW
#define ZISA_INTEGER_CAST_HPP_ICHUW

#include <zisa/config.hpp>

namespace zisa {
namespace detail {
template <class To, class From>
class IntegerCast;

template <>
class IntegerCast<int, size_t> {
public:
  static int cast(size_t i) {
    assert(i <= size_t(std::numeric_limits<int>::max()));

    return int(i);
  }
};

template <>
class IntegerCast<size_t, int> {
public:
  static size_t cast(int i) {
    assert(i >= 0);
    return size_t(i);
  }
};

template <>
class IntegerCast<unsigned long long int, long unsigned int> {
private:
  using To = unsigned long long int;
  using From = long unsigned int;

public:
  static To cast(From i) { return To(i); }
};

template <>
class IntegerCast<long unsigned int, unsigned long long int> {
private:
  using To = long unsigned int;
  using From = unsigned long long int;

public:
  static To cast(From i) {
    assert(i <= From(std::numeric_limits<To>::max()));
    return To(i);
  }
};

template <>
class IntegerCast<unsigned long, long> {
public:
  static unsigned long cast(long i) {
    assert(i >= 0);
    return (unsigned long)(i);
  }
};

template <>
class IntegerCast<long, unsigned long> {
public:
  static long cast(unsigned long i) {
    assert(i <= (unsigned long)(std::numeric_limits<long>::max()));
    return long(i);
  }
};

template <class Int>
class IntegerCast<Int, Int> {
public:
  static Int cast(Int i) { return i; }
};
}

template <class To, class From>
std::decay_t<To> integer_cast(From from) {
  return detail::IntegerCast<std::decay_t<To>, std::decay_t<From>>::cast(from);
}

}

#endif // ZISA_INTEGER_CAST_HPP
