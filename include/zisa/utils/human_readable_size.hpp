// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ZISA_HUMAN_READABLE_SIZE_BVOQUE
#define ZISA_HUMAN_READABLE_SIZE_BVOQUE

#include <string>
#include <zisa/utils/string_format.hpp>

namespace zisa {

/// Returns the size as a human readable string.
/** Examples:
 *      human_readable_size(345) == "345 B"
 *      human_readable_size(3456) == "3.45 KB"
 *      human_readable_size(3456600) == "3.45 MB"
 */
std::string human_readable_size(size_t size_in_bytes,
                                const std::string &float_format = "%.2f");

}
#endif
