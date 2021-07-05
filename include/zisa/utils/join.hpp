// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ZISA_JOIN_HPP_MZXNB
#define ZISA_JOIN_HPP_MZXNB

#include <string>
#include <vector>

namespace zisa {

std::string join(const std::vector<std::string> &parts,
                 const std::string &separator);
}

#endif // ZISA_JOIN_HPP
