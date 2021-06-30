// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef ZISA_RETURN_T_HPP
#define ZISA_RETURN_T_HPP

#include <type_traits>

namespace zisa {

template <class Transform, class Arg1, class Arg2>
using return_t = std::result_of_t<Transform(const Arg1 &, const Arg2 &)>;

}

#endif // ZISA_RETURN_T_HPP
