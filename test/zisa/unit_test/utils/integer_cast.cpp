// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <zisa/testing/testing_framework.hpp>

#include <zisa/utils/integer_cast.hpp>

template <class To, class From>
constexpr bool check_integer_cast(From i) {
  return zisa::integer_cast<To>(i) == To(i);
}

TEST_CASE("integer_cast; API", "[utils]") {
  int i_int = 32;
  unsigned long i_ul = 32ul;
  std::size_t i_size_t = 32;
  zisa::int_t i_int_t = 32;

  SECTION("int -> *") {
    REQUIRE(check_integer_cast<int>(i_int));
    REQUIRE(check_integer_cast<std::size_t>(i_int));
    REQUIRE(check_integer_cast<zisa::int_t>(i_int));
    REQUIRE(check_integer_cast<unsigned long>(i_int));
  }

  SECTION("unsigned long -> *") {
    REQUIRE(check_integer_cast<int>(i_ul));
    REQUIRE(check_integer_cast<std::size_t>(i_ul));
    REQUIRE(check_integer_cast<zisa::int_t>(i_ul));
    REQUIRE(check_integer_cast<unsigned long>(i_ul));
  }

  SECTION("zisa::size_t -> *") {
    REQUIRE(check_integer_cast<int>(i_size_t));
    REQUIRE(check_integer_cast<std::size_t>(i_size_t));
    REQUIRE(check_integer_cast<zisa::int_t>(i_size_t));
    REQUIRE(check_integer_cast<unsigned long>(i_size_t));
  }

  SECTION("unsigned long -> *") {
    REQUIRE(check_integer_cast<int>(i_int_t));
    REQUIRE(check_integer_cast<std::size_t>(i_int_t));
    REQUIRE(check_integer_cast<zisa::int_t>(i_int_t));
    REQUIRE(check_integer_cast<unsigned long>(i_int_t));
  }

  SECTION("short -> *") {
    // Doesn't and shouldn't compile until `short` it's implemented for short.
    //  zisa::integer_cast<short>(i_int_t);
  }
}

TEST_CASE("integer_cast; overflow", "[utils]") {
  auto i_int = std::numeric_limits<int>::max();
  auto i_ul = std::numeric_limits<unsigned long>::max();
  auto i_size_t = std::numeric_limits<std::size_t>::max();
  auto i_int_t = std::numeric_limits<zisa::int_t>::max();

#if !NDEBUG
  // TODO These tests require restructuring of how we assert.
  SECTION("* -> int") {
    // REQUIRE_THROWS(check_integer_cast<int>(i_ul));
    // REQUIRE_THROWS(check_integer_cast<int>(i_size_t));
    // REQUIRE_THROWS(check_integer_cast<int>(i_int_t));
  }
#endif
}
