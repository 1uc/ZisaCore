#ifndef REPLACE_ALL_H_M4F3M
#define REPLACE_ALL_H_M4F3M

#include <string>

namespace zisa {

/// Copy of `source` with all occurrences of `from` replaced by `to`.
std::string replace_all(const std::string &source,
                        const std::string &from,
                        const std::string &to);

} // namespace zisa
#endif /* end of include guard */
