// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef CHECK_CUDA_ERROR_HPP_NQDGL
#define CHECK_CUDA_ERROR_HPP_NQDGL

#include <string>
#include <cuda.h>
#include <cuda_runtime.h>

namespace zisa {

std::string cuda_error_message(cudaError_t error_code);
void check_cuda_error(char const *file, int line);

}

#endif // CHECK_CUDA_ERROR_HPP
