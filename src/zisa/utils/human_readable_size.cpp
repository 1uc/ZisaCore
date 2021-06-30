// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <zisa/utils/human_readable_size.hpp>

#include <array>
#include <cmath>

#include <iostream>

namespace zisa {
std::string human_readable_size(size_t size_in_bytes,
                                const std::string &number_format) {
  if (size_in_bytes == 0) {
    return "0 B";
  }

  char prefixes[] = {'K', 'M', 'G', 'T', 'P'};
  double logb = log10(double(size_in_bytes));

  auto atol = double(2ul << 20);
  auto k = int(round((logb / 3.0) * atol) / atol);

  if (k == 0) {
    return string_format("%d B", size_in_bytes);
  } else {
    double b = round(double(size_in_bytes) / pow(10.0, 3.0 * k) * atol) / atol;
    return string_format(number_format, b)
           + string_format(" %cB", prefixes[k - 1]);
  }
}

}