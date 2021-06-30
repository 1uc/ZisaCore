// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ALL_TRUE_H_DD6Y1
#define ALL_TRUE_H_DD6Y1

#include <type_traits>

namespace zisa {

namespace detail {

template <bool...>
struct bool_pack;

} // namespace detail

template <bool... bools>
struct all_true {
  static constexpr bool value
      = std::is_same<detail::bool_pack<true, bools...>,
                     detail::bool_pack<bools..., true>>::value;
};

} // namespace zisa

#endif /* end of include guard */
