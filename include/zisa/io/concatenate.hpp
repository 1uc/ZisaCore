// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef CONCATENATE_H_L3KZSHB0
#define CONCATENATE_H_L3KZSHB0

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

namespace zisa {

template <class Iterator>
std::string
concatenate(Iterator begin, const Iterator &end, const std::string &separator) {
  if (begin == end) {
    return std::string("");
  }

  std::stringstream ss;
  ss << *(begin++);
  auto interleave
      = [&ss, &separator](const std::string &s) { ss << separator << s; };
  std::for_each(begin, end, interleave);
  return ss.str();
}

template <class T>
std::string concatenate(const std::vector<T> &c, const std::string &separator) {
  std::ostringstream ss;

  std::copy(
      c.begin(), c.end() - 1, std::ostream_iterator<T>(ss, separator.c_str()));
  ss << c.back();

  return ss.str();
}

} // namespace zisa
#endif /* end of include guard: CONCATENATE_H_L3KZSHB0 */
