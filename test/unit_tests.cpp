// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#define CATCH_CONFIG_RUNNER
#include "zisa/testing/testing_framework.hpp"

#if ZISA_HAS_MPI
#include <mpi.h>
#endif

#include <zisa/config.hpp>

int main( int argc, char* argv[] ) {
#if ZISA_HAS_MPI
  int requested = MPI_THREAD_MULTIPLE;
  int provided = -1;

  MPI_Init_thread(&argc, &argv, requested, &provided);
  LOG_ERR_IF(requested > provided,
             "MPI does not support the requested level of multi-threading.");
#endif

  int result = Catch::Session().run( argc, argv );

#if ZISA_HAS_MPI
  MPI_Finalize();
#endif

  return result;
}
