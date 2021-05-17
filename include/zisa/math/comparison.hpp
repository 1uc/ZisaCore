#ifndef COMPARISON_H_3PO4FDB7
#define COMPARISON_H_3PO4FDB7

#include <cmath>

#include <zisa/config.hpp>
#include <zisa/math/isreal.hpp>

namespace zisa {

/// Sign function
/** Thanks to SO:
 *  http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
 */
template <typename T>
ANY_DEVICE_INLINE int sign(T val) {
  return (T(0) < val) - (val < T(0));
}

ANY_DEVICE_INLINE void swap(double &a, double &b) {
  double tmp = a;
  a = b;
  b = tmp;
}

ANY_DEVICE_INLINE bool XOR(bool lhs, bool rhs) { return lhs != rhs; }

// -- absolute value
ANY_DEVICE_INLINE int abs(int i) {
#ifdef __CUDACC__
  return ::abs(i);
#else
  return std::abs(i);
#endif
}

ANY_DEVICE_INLINE double abs(double x) {
#ifdef __CUDACC__
  return ::fabs(x);
#else
  return std::fabs(x);
#endif
}

// -- maximum
template <typename T>
ANY_DEVICE_INLINE constexpr T max(const T &x, const T &y) {
  return x < y ? y : x;
}

template <typename T>
ANY_DEVICE_INLINE constexpr T max(const T &x, const T &y, const T &z) {
  return zisa::max(x, zisa::max(y, z));
}

// -- minimum
template <typename T>
ANY_DEVICE_INLINE constexpr T min(const T &x, const T &y) {
  return x < y ? x : y;
}

template <typename T>
ANY_DEVICE_INLINE constexpr T min(const T &x, const T &y, const T &z) {
  return zisa::min(x, zisa::min(y, z));
}

template <typename T>
ANY_DEVICE_INLINE constexpr T
min(const T &x, const T &y, const T &z, const T &a) {
  return zisa::min(zisa::min(x, y), zisa::min(z, a));
}

// popular slope-limiter comparison
ANY_DEVICE_INLINE double minmod(double a, double b) {
  return 0.5 * (sign(a) + sign(b)) * zisa::min(zisa::abs(a), zisa::abs(b));
}

ANY_DEVICE_INLINE double minabs(double a, double b) {
  // filter out special floating point numbers: -inf, inf, NaN.
  bool should_pick_a = (zisa::abs(a) < zisa::abs(b)) || zisa::isnan(b);
  return should_pick_a ? a : b;
}

ANY_DEVICE_INLINE double maxabs(double a, double b) {
  // filter out special floating point numbers: -inf, inf, NaN.
  bool should_pick_b = (zisa::abs(b) < zisa::abs(a)) || zisa::isnan(a);
  return should_pick_b ? b : a;
}

ANY_DEVICE_INLINE bool almost_equal(double a, double b, double atol) {
  return zisa::abs(b - a) < atol;
}

#ifndef __CUDACC__
inline bool is_inside_interval(double x, const std::tuple<double, double> &I) {

  auto &[i0, i1] = I;

  return i0 <= x && x <= i1;
}
#endif

} // namespace zisa
#endif /* end of include guard: COMPARISON_H_3PO4FDB7 */
