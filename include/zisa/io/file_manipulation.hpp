#ifndef WRITE_STRING_TO_FILE_H_PAMZW0U5
#define WRITE_STRING_TO_FILE_H_PAMZW0U5
#include <fstream>
#include <string>

namespace zisa {
void write_string_to_file(const std::string &message,
                          const std::string &filename);

bool file_exists(const std::string &filename);
void delete_file(const std::string &filename);
void create_directory(const std::string &dirname);
void ensure_directory_exists(const std::string &filename);

std::string stem(const std::string &filename);
std::string basename(const std::string &filename);
std::string dirname(const std::string &filename);

}
#endif /* end of include guard: WRITE_STRING_TO_FILE_H_PAMZW0U5 */
