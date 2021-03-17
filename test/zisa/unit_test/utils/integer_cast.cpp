#include <zisa/testing/testing_framework.hpp>

#include <zisa/utils/integer_cast.hpp>

TEST_CASE("integer_cast; API", "[utils]") {
  int i_int = 32;
  unsigned long i_ul = 32ul;
  std::size_t i_size_t = 32;
  std::size_t i_int_t = 32;

  SECTION("int -> *") {
    zisa::integer_cast<int>(i_int);
    zisa::integer_cast<std::size_t>(i_int);
    zisa::integer_cast<zisa::int_t>(i_int);
    zisa::integer_cast<unsigned long>(i_int);
  }

  SECTION("unsigned long -> *") {
    zisa::integer_cast<int>(i_ul);
    zisa::integer_cast<std::size_t>(i_ul);
    zisa::integer_cast<zisa::int_t>(i_ul);
    zisa::integer_cast<unsigned long>(i_ul);
  }

  SECTION("zisa::size_t -> *") {
    zisa::integer_cast<int>(i_size_t);
    zisa::integer_cast<std::size_t>(i_size_t);
    zisa::integer_cast<zisa::int_t>(i_size_t);
    zisa::integer_cast<unsigned long>(i_size_t);
  }

  SECTION("unsigned long -> *") {
    zisa::integer_cast<int>(i_int_t);
    zisa::integer_cast<std::size_t>(i_int_t);
    zisa::integer_cast<zisa::int_t>(i_int_t);
    zisa::integer_cast<unsigned long>(i_int_t);
  }

  SECTION("unsigned long -> *") {
    // Doesn't and shouldn't compile until `short` it's implemented for short.
    //  zisa::integer_cast<short>(i_int_t);
  }
}
