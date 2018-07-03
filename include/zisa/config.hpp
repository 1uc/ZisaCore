/* Global configuration. */

#ifndef CONFIG_H_FYDJO
#define CONFIG_H_FYDJO

#include <cstddef>
#include <iostream>

namespace zisa {

using int_t = std::size_t;

#ifndef USE_CUDA

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
#include <cuda.h>
#include <cuda_runtime.h>
#endif

#define ANY_DEVICE __host__ __device__
#define ANY_DEVICE_INLINE __host__ __device__ __inline__

} // namespace zisa

#include <zisa/utils/string_format.hpp>
#include <zisa/utils/logging.hpp>

#endif /* end of include guard */
