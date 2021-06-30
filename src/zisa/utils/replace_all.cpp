// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <zisa/utils/replace_all.hpp>

namespace zisa {

std::string replace_all(const std::string &source,
                        const std::string &from,
                        const std::string &to) {

  // credit: https://stackoverflow.com/a/29752943

  std::string new_string;
  new_string.reserve(source.length());

  std::string::size_type lastPos = 0;
  std::string::size_type findPos;

  while (std::string::npos != (findPos = source.find(from, lastPos))) {
    new_string.append(source, lastPos, findPos - lastPos);
    new_string += to;
    lastPos = findPos + from.length();
  }

  new_string += source.substr(lastPos);

  return new_string;
}

} // namespace zisa
