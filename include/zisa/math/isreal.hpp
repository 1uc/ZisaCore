/* Check that a floating point number is a real number.
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2016-01-12
 */
#ifndef ISREAL_H_M87B3AXT
#define ISREAL_H_M87B3AXT

#include <cmath>
#include <zisa/config.hpp>

namespace zisa {
// TODO fix naming, should be is_nan.
ANY_DEVICE_INLINE bool isnan(double x) {
#ifdef __CUDACC__
  return ::isnan(x);
#else
  return std::isnan(x);
#endif
}

ANY_DEVICE_INLINE bool isinf(double x) {
#ifdef __CUDACC__
  return ::isinf(x);
#else
  return std::isinf(x);
#endif
}

ANY_DEVICE_INLINE bool isreal(double x) {
  return !zisa::isnan(x) && !zisa::isinf(x);
}

ANY_DEVICE_INLINE bool ispositive(double x) {
  return x > 0.0 && zisa::isreal(x);
}

ANY_DEVICE_INLINE bool notreal(double x) {
  return zisa::isnan(x) || zisa::isinf(x);
}

ANY_DEVICE_INLINE bool isplausible(double x) { return zisa::isreal(x); }

} // namespace zisa
#endif /* end of include guard: ISREAL_H_M87B3AXT */
