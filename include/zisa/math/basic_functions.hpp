/* Basic functions.
 */

#ifndef BASIC_FUNCTIONS_H_FTM4W
#define BASIC_FUNCTIONS_H_FTM4W

#include <zisa/config.hpp>
#include <zisa/math/comparison.hpp>
#include <zisa/math/mathematical_constants.hpp>

namespace zisa {

double herons_formula(double a, double b, double c);

ANY_DEVICE_INLINE double log(double x) {
#ifdef __CUDACC__
  return ::log(x);
#else
  return std::log(x);
#endif
}

ANY_DEVICE_INLINE double log10(double x) {
#ifdef __CUDACC__
  return ::log10(x);
#else
  return std::log10(x);
#endif
}

ANY_DEVICE_INLINE double exp(double x) {
#ifdef __CUDACC__
  return ::exp(x);
#else
  return std::exp(x);
#endif
}

ANY_DEVICE_INLINE double pow(double x, double y) {
#ifdef __CUDACC__
  return ::pow(x, y);
#else
  return std::pow(x, y);
#endif
}

ANY_DEVICE_INLINE float pow(float x, float y) {
#ifdef __CUDACC__
  LOG_ERR("CHECK exact name.");
#else
  return std::pow(x, y);
#endif
}

template <int n, class T>
ANY_DEVICE_INLINE constexpr T pow(T x) {
  return x * pow<n - 1>(x);
}

template <>
ANY_DEVICE_INLINE constexpr double pow<0>(double) {
  return double(1);
}

template <>
ANY_DEVICE_INLINE constexpr int pow<0>(int) {
  return int(1);
}

template <>
ANY_DEVICE_INLINE constexpr double pow<1>(double x) {
  return x;
}

template <>
ANY_DEVICE_INLINE constexpr int pow<1>(int x) {
  return x;
}

ANY_DEVICE_INLINE double sqrt(double x) { return ::sqrt(x); }

ANY_DEVICE_INLINE double sin(double x) {
#ifdef __CUDACC__
  return ::sin(x);
#else
  return std::sin(x);
#endif
}

ANY_DEVICE_INLINE double sin2pi(double x) {
#ifdef __CUDACC__
  return ::sin(2 * zisa::pi * x);
#else
  return std::sin(2 * zisa::pi * x);
#endif
}

ANY_DEVICE_INLINE double cos(double x) {
#ifdef __CUDACC__
  return ::cos(x);
#else
  return std::cos(x);
#endif
}

ANY_DEVICE_INLINE double cos2pi(double x) {
#ifdef __CUDACC__
  return ::cos(2 * zisa::pi * x);
#else
  return std::cos(2 * zisa::pi * x);
#endif
}

ANY_DEVICE_INLINE double atan2(double y, double x) {
#ifdef __CUDACC__
  return ::atan2(y, x);
#else
  return std::atan2(y, x);
#endif
}

template <class T>
ANY_DEVICE_INLINE T avg(const T &a, const T &b) {
  return 0.5 * (a + b);
}

/// Integer division, but round up.
ANY_DEVICE_INLINE int div_up(const int i, const int n) {
  return (i + n - 1) / n;
}

/// compute a gaussian
ANY_DEVICE_INLINE double gaussian(double x, double x_mid, double sigma) {
  return zisa::exp(-zisa::pow((x - x_mid) / sigma, 2.0));
}

ANY_DEVICE_INLINE double ceil(double x) {
#ifdef __CUDACC__
  return ::ceil(x);
#else
  return std::ceil(x);
#endif
}

ANY_DEVICE_INLINE double floor(double x) {
#ifdef __CUDACC__
  return ::floor(x);
#else
  return std::floor(x);
#endif
}

template <typename T>
ANY_DEVICE_INLINE T sech(T a) {
  return 1 / cosh(a);
}

ANY_DEVICE double factorial(int k);
ANY_DEVICE_INLINE double Gamma(int k) { return factorial(k - 1); }

} // namespace zisa

#endif /* end of include guard */
