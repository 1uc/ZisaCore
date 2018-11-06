/*
 *
 */

#ifndef FORMAT_AS_LIST_H_H0M8C
#define FORMAT_AS_LIST_H_H0M8C

#include <sstream>
#include <string>
#include <zisa/config.hpp>

namespace zisa {

template <class Array, class SFINAE = decltype(std::declval<Array>()[0])>
std::string format_as_list(const Array &array, int_t n) {
  std::stringstream ss;

  ss << "[ ";
  for (int_t i = 0; i < n; ++i) {
    ss << array[i] << (i < n - 1 ? ", " : " ]");
  }

  return ss.str();
}

template <class Array, class SFINAE = decltype(std::declval<Array>().size())>
std::string format_as_list(const Array &array) {
  return format_as_list(array, array.size());
}

} // namespace zisa

#endif /* end of include guard */
