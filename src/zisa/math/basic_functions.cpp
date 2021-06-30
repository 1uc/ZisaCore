// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <cmath>

#include <zisa/math/basic_functions.hpp>

namespace zisa {

double herons_formula(double a, double b, double c) {
  double s = (a + b + c) / 2;
  return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

ANY_DEVICE double factorial(int k) {
  int n = 1;
  for (int i = 2; i <= k; ++i) {
    n *= i;
  }

  return n;
}

} // namespace zisa
