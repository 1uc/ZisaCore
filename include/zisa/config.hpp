// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef CONFIG_H_FYDJO
#define CONFIG_H_FYDJO

#include <cstddef>
#include <iostream>

namespace zisa {
using int_t = std::size_t;
} // namespace zisa

#ifndef ZISA_HAS_CUDA

#ifndef __host__
#define __host__
#endif

#ifndef __device__
#define __device__
#endif

#ifndef __inline__
#define __inline__ inline
#endif

#else
#include <zisa/cuda/cuda.hpp>
#endif

#define ANY_DEVICE __host__ __device__
#define ANY_DEVICE_INLINE __host__ __device__ __inline__

#include <zisa/utils/logging.hpp>
#include <zisa/utils/string_format.hpp>

#define ZISA_UNUSED(expr) (void)(expr);

#endif /* end of include guard */
