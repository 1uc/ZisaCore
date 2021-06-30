// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef IF_T_H_DBUU1
#define IF_T_H_DBUU1
namespace zisa {
namespace detail {

template <bool cond, class IfTrue, class IfFalse>
struct if_struct {};

template <class IfTrue, class IfFalse>
struct if_struct<true, IfTrue, IfFalse> {
  using type = IfTrue;
};

template <class IfTrue, class IfFalse>
struct if_struct<false, IfTrue, IfFalse> {
  using type = IfFalse;
};

} // namespace detail

template <bool cond, class IfTrue, class IfFalse>
using if_t = typename detail::if_struct<cond, IfTrue, IfFalse>::type;

} // namespace zisa
#endif /* end of include guard */
