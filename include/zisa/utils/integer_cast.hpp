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
    assert(i < size_t(std::numeric_limits<int>::max()));

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
