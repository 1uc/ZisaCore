// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <zisa/cuda/check_cuda_error.hpp>

#include <zisa/utils/string_format.hpp>
#include <zisa/utils/logging.hpp>

namespace zisa {

std::string cuda_error_message(cudaError_t error_code) {
  auto error_desc = cudaGetErrorName(error_code);
  return string_format("CUDA error detected: %s", error_desc);
}

void check_cuda_error(char const * file, int line) {
  auto error_code = cudaPeekAtLastError();
  if (error_code != cudaSuccess) {
    auto msg = cuda_error_message(error_code);
    log_msg(file, line, "ERROR", msg);
  }
}

}


