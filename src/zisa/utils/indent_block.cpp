// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <cassert>
#include <string>

#include <zisa/utils/indent_block.hpp>
#include <zisa/utils/replace_all.hpp>

namespace zisa {

std::string indent_block(int by, const std::string &text) {
  std::string white_space(static_cast<std::size_t>(2 * by), ' ');
  return white_space + replace_all(text, "\n", "\n" + white_space);
}

} // namespace zisa
