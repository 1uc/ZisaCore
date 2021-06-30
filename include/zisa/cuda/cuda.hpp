// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef CUDA_HPP_FHEUW
#define CUDA_HPP_FHEUW

#include <cuda.h>
#include <cuda_runtime.h>

#include <zisa/cuda/check_cuda_error.hpp>

#define ZISA_CHECK_CUDA zisa::check_cuda_error(__FILE__, __LINE__);

#if ZISA_NO_CHECK_CUDA_DEBUG
#define ZISA_CHECK_CUDA_DEBUG
#else
#define ZISA_CHECK_CUDA_DEBUG zisa::check_cuda_error(__FILE__, __LINE__);
#endif

#endif
