#include <zisa/utils/join.hpp>

#include <numeric>

namespace zisa {

std::string join(const std::vector<std::string> &parts,
                 const std::string &separator) {
  if (parts.empty()) {
    return "";
  }

  auto length_parts
      = std::accumulate(parts.begin(),
                        parts.end(),
                        size_t(0),
                        [](size_t count, const std::string &part) {
                          return count + part.size();
                        });
  auto length_separators = (parts.size() - 1) * separator.size();

  auto joined = std::string();
  joined.reserve(length_parts + length_separators);

  joined.append(parts[0]);
  for (auto p = parts.begin() + 1; p < parts.end(); ++p) {
    joined.append(separator);
    joined.append(*p);
  }

  return joined;
}
}
