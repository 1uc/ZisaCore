// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ADD_CONST_IF_H_PKUZS
#define ADD_CONST_IF_H_PKUZS

#include "zisa/meta/if_t.hpp"

namespace zisa {

template <bool cond, class T>
struct add_const_if {
  using type = if_t<cond, typename std::add_const<T>::type, T>;
};

template <bool cond, class T>
using add_const_if_t = typename add_const_if<cond, T>::type;

} // namespace zisa
#endif /* end of include guard */
