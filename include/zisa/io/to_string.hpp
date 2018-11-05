/* If an object can write to a stream, `zisa::to_string` will return what would
 * have been written to the stream as a string.
 *
 */

#ifndef TO_STRING_H_1341G
#define TO_STRING_H_1341G

#include <string>
#include <sstream>

namespace zisa {

template <class T>
std::string to_string(const T &t) {

  std::stringstream ss;
  ss << t;
  return ss.str();
}

} // namespace zisa

#endif /* end of include guard */
