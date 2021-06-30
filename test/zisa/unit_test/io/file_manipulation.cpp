#include <zisa/testing/testing_framework.hpp>

#include <fstream>
#include <zisa/io/file_manipulation.hpp>

TEST_CASE("file_manipulation; API", "[io]") {

  std::string filename = "__file.txt";

  {
    auto os = std::ofstream(filename);
    os << "hi\n";
  }

  REQUIRE(zisa::file_exists(filename));

  zisa::delete_file(filename);

  REQUIRE(!zisa::file_exists(filename));
}
