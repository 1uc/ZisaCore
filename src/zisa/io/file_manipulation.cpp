// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#if ZISA_NEEDS_EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#include <zisa/io/file_manipulation.hpp>
#include <zisa/utils/logging.hpp>
#include <zisa/utils/string_format.hpp>


namespace zisa {
void write_string_to_file(const std::string &message,
                          const std::string &filename) {
  std::ofstream fout(filename.c_str());

  if (fout.is_open()) {
    fout << message;
  } else {
    LOG_ERR("Can't write relaunch file.");
  }

  fout.close();
  if (!fout.good()) {
    LOG_ERR("Error writing relaunch file.");
  }
}

bool file_exists(const std::string &filename) {
  std::ifstream file(filename);
  return file.good();
}

void delete_file(const std::string &filename) { fs::remove(filename); }

void create_directory(const std::string &dirname) {
  if (dirname == "") {
    return;
  }

  auto dir = fs::path(dirname);
  fs::create_directories(dir);

  LOG_ERR_IF(
      !fs::is_directory(dir),
      string_format("Failed to create directory. [%s]", dirname.c_str()));
}

std::string stem(const std::string &filename) {
  return fs::path(filename).stem();
}

std::string basename(const std::string &filename) {
  return fs::path(filename).filename();
}

std::string dirname(const std::string &filename) {
  auto p = fs::path(filename);
  return p.remove_filename();
}

void ensure_directory_exists(const std::string &filename) {
  create_directory(dirname(filename));
}

}
