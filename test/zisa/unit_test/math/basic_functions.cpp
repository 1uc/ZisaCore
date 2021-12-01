// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <zisa/testing/testing_framework.hpp>

#include <zisa/math/basic_functions.hpp>

struct X {
  // Anything not convertible from `1.0`.
  constexpr X(double, double b) : x(b) {}

  X operator*(X y) const { return X(0.0, x * y.x); }

  double x;
};

namespace zisa {
namespace internal {

template <>
struct StaticPowTrait<X> {
  constexpr static X one() { return X(0.0, 1.0); }
};

}
}

TEST_CASE("pow<n>(x); API", "[math]") {
  SECTION("double") {
    double a3 = zisa::pow<3>(2.0);
    REQUIRE(a3 == 8.0);
  }

  SECTION("int") {
    int a3 = zisa::pow<3>(3);
    REQUIRE(a3 == 27);
  }

  SECTION("int_t") {
    zisa::int_t a3 = zisa::pow<3>(3);
    REQUIRE(a3 == zisa::int_t(27));
  }

  SECTION("long") {
    long a3 = zisa::pow<3>(long(3));
    REQUIRE(a3 == long(27));
  }

  SECTION("Custom type; X") {
    X b(0.0, 2.0);
    X b3 = zisa::pow<3>(b);

    REQUIRE(b3.x == 8.0);
  }
}
