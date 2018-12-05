#ifndef PARSE_DURATION_H_6H1LW
#define PARSE_DURATION_H_6H1LW

#include <chrono>
#include <string>

namespace zisa {

/// Convert "1s", "1ms", etc. to `std::chrono::duration
std::chrono::milliseconds parse_duration_ms(const std::string &duration);

} // namespace zisa

#endif
