#include <cmath>

#include <zisa/math/basic_functions.hpp>

namespace zisa {

double herons_formula(double a, double b, double c) {
  double s = (a + b + c) / 2;
  return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

} // namespace zisa
