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

template <class UInt>
std::tuple<std::vector<UInt>, std::vector<UInt>>
testcase_next_pow2_powers_of_two(int bits) {
  std::vector<UInt> input;
  input.reserve(bits);

  std::vector<UInt> output;
  output.reserve(bits);

  input.push_back(0);
  output.push_back(0);

  for (int k = 0; k < bits; ++k) {
    input.push_back(UInt(1) << k);
    output.push_back(UInt(1) << k);
  }

  return {std::move(input), std::move(output)};
}

template <class UInt>
std::tuple<std::vector<UInt>, std::vector<UInt>>
testcase_next_pow2_powers_of_two_minus_one(int bits) {
  std::vector<UInt> input;
  input.reserve(bits);

  std::vector<UInt> output;
  output.reserve(bits);

  for (int k = 2; k < bits; ++k) {
    input.push_back((UInt(1) << k) - 1);
    output.push_back(UInt(1) << k);
  }

  return {std::move(input), std::move(output)};
}

template <class UInt>
std::tuple<std::vector<UInt>, std::vector<UInt>>
testcase_next_pow2_powers_of_two_plus_one(int bits) {
  std::vector<UInt> input;
  input.reserve(bits);

  std::vector<UInt> output;
  output.reserve(bits);

  for (int k = 2; k < bits - 1; ++k) {
    input.push_back((UInt(1) << k) + 1);
    output.push_back(UInt(1) << (k + 1));
  }

  return {std::move(input), std::move(output)};
}

template <class UInt>
static void check_next_pow2(const std::vector<UInt> &input,
                            const std::vector<UInt> &exact) {

  for (size_t k = 0; k < input.size(); ++k) {
    auto approx = zisa::next_pow2(input[k]);
    INFO(string_format("next_pow2(%d) = %d != %d", input[k], approx, exact[k]));
    REQUIRE(approx == exact[k]);
  }
}

template <class UInt>
void testsuite_next_pow2(int bits) {
  SECTION("2**k") {
    auto [input, exact] = testcase_next_pow2_powers_of_two<UInt>(bits);
    check_next_pow2(input, exact);
  }

  SECTION("2**k - 1") {
    auto [input, exact]
        = testcase_next_pow2_powers_of_two_minus_one<UInt>(bits);
    check_next_pow2(input, exact);
  }

  SECTION("2**k + 1") {
    auto [input, exact] = testcase_next_pow2_powers_of_two_plus_one<UInt>(bits);
    check_next_pow2(input, exact);
  }
}

TEST_CASE("next_pow2(32bit)", "[runme][math]") {
  testsuite_next_pow2<unsigned int>(32);
}

TEST_CASE("next_pow2(64bit)", "[runme][math]") {
  testsuite_next_pow2<size_t>(64);
}