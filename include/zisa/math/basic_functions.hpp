// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

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
  return ::pow(x, y);
#else
  return std::pow(x, y);
#endif
}

namespace internal {
template <class T>
struct StaticPowTrait {
  ANY_DEVICE_INLINE constexpr static T one() { return T(1.0); }
};

template <int n, class T>
struct StaticPowImpl {
  ANY_DEVICE_INLINE constexpr static T value(T x) {
    return x * StaticPowImpl<n - 1, T>::value(x);
  }
};

template <class T>
struct StaticPowImpl<1, T> {
  ANY_DEVICE_INLINE constexpr static T value(T x) { return x; }
};

template <class T>
struct StaticPowImpl<0, T> {
  ANY_DEVICE_INLINE constexpr static T value(T) {
    return StaticPowTrait<T>::one();
  }
};
}

template <int n, class T>
ANY_DEVICE_INLINE constexpr T pow(T x) {
  static_assert(n >= 0, "Use `1.0 / pow<n>(x)` instead.");
  return zisa::internal::StaticPowImpl<n, T>::value(x);
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

/// Integer division, but round up.
ANY_DEVICE_INLINE int_t div_up(const int_t i, const int_t n) {
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

namespace detail {

#if __CUDACC__
__device__ __inline__ unsigned int next_pow2_nvcc(unsigned int n) {
  static_assert(sizeof(int) == 4, "Unexpected size of `long long`.");
  return n == 1 ? 1 : ((int)(1)) << (64 - __clzll((int)(n - 1)));
}
#endif

#if __CUDACC__
__device__ __inline__ size_t next_pow2_nvcc(size_t n) {
  static_assert(sizeof(long long) == 8, "Unexpected size of `long long`.");
  return n == 1 ? 1 : ((long long)(1)) << (64 - __clzll((long long)(n - 1)));
}
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_clz)
inline unsigned int next_pow2_gcc_clang(unsigned int n) {
  return n <= 1 ? n : ((unsigned int)(1)) << (32 - __builtin_clz(n - 1));
}
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_clzl)
inline size_t next_pow2_gcc_clang(size_t n) {
  return n <= 1 ? n : ((size_t)(1)) << (64 - __builtin_clzl(n - 1));
}
#endif
}

ANY_DEVICE_INLINE
unsigned int next_pow2(unsigned int n) {
  // See: https://jameshfisher.com/2018/03/30/round-up-power-2/
  //      https://stackoverflow.com/a/63668217

  static_assert(sizeof(unsigned int) == 4,
                "Unexpected size of `unsigned int`.");

#if defined(__CUDACC__) && defined(__CUDA_ARCH__)
  return detail::next_pow2_nvcc(n);
#elif defined(__has_builtin) && __has_builtin(__builtin_clz)
  return detail::next_pow2_gcc_clang(n);
#else
#error "Missing portable implementation."
#endif
}

ANY_DEVICE_INLINE
size_t next_pow2(size_t n) {
  // See: https://jameshfisher.com/2018/03/30/round-up-power-2/
  //      https://stackoverflow.com/a/63668217

  static_assert(sizeof(size_t) == 8, "Unexpected size of `size_t`.");

#if defined(__CUDACC__) && defined(__CUDA_ARCH__)
  return detail::next_pow2_nvcc(n);
#elif defined(__has_builtin) && __has_builtin(__builtin_clzl)
  return detail::next_pow2_gcc_clang(n);
#else
#error "Missing portable implementation."
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
