/* Solid printf for std::string, thanks [1].
 *
 * Requires C++11.
 *
 * [1]: http://stackoverflow.com/a/26221725
 */

#ifndef STRING_FORMAT_H_NESVBYMK
#define STRING_FORMAT_H_NESVBYMK

#include <cassert>
#include <cstdio>
#include <memory>
#include <string>

template <typename... Args>
std::string string_format(const char *format, Args... args) {
  // Extra space for '\0'
  auto size_ = snprintf(nullptr, 0, format, args...) + 1;
  assert(size_ > 0);

  size_t size = size_t(size_);

  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format, args...);

  // Strip the '\0'.
  return std::string(buf.get(), buf.get() + size - 1);
}

template <typename... Args>
std::string string_format(const std::string &format, Args... args) {
  return string_format(format.c_str(), args...);
}

#endif /* end of include guard: STRING_FORMAT_H_NESVBYMK */
