/* Collection of routines to manipulate dates and times.
 */

#if ZISA_HAS_MPI == 1
#include <mpi.h>
#endif

#include <zisa/datetime.hpp>
#include <zisa/utils/string_format.hpp>

namespace zisa {
struct tm localtime_safe(const std::time_t &time) {
  struct tm timeinfo;

#ifdef _MSC_VER // Windows
  localtime_s(&timeinfo, &time);
#else // POSIX
  localtime_r(&time, &timeinfo);
#endif

  return timeinfo;
}

std::string date_format(const std::time_t &time) {
  auto timeinfo = localtime_safe(time);

  const int date_len = 50;
  char date_str[date_len];
  std::strftime(date_str, date_len, "%F %T UTC%z", &timeinfo);

  return std::string(date_str);
}

std::string time_format(const std::time_t &time) {
  auto timeinfo = localtime_safe(time);

  const int date_len = 50;
  char date_str[date_len];
  std::strftime(date_str, date_len, "%T", &timeinfo);

  return std::string(date_str);
}

std::string duration_format(double elapsed_seconds) {
  int elapsed = int(elapsed_seconds); // chop off fractions of a second

  int days = elapsed / (24 * 3600);
  int hours = (elapsed % (24 * 3600)) / 3600;
  int minutes = (elapsed % 3600) / 60;
  int seconds = elapsed % 60;

  return string_format("%d-%02d:%02d:%02d", days, hours, minutes, seconds);
}

double elapsed_seconds(const zisa::time_stamp_t &newer,
                       const zisa::time_stamp_t &older) {
#if ZISA_HAS_MPI != 0
  return newer - older;
#else
  return std::difftime(newer, older);
#endif
}

double elapsed_seconds_since(const zisa::time_stamp_t &reference) {
  return elapsed_seconds(current_time_stamp(), reference);
}

/// Get a time-stamp of the current time.
zisa::time_stamp_t current_time_stamp() {
#if ZISA_HAS_MPI == 1
  return MPI_Wtime();
#else
  return time(0);
#endif
}

std::time_t current_date() { return time(0); }
std::time_t current_time() { return time(0); }

class DurationParser {
public:
  static double parse(const std::string &duration) {
    return parse_dhhmmss(duration);
  }

  static double parse_hhmmss(const std::string &duration) {
    auto first_colon = duration.find(':');

    int hours = stoi(duration.substr(0, first_colon));
    int minutes = stoi(duration.substr(first_colon + 1, 2));
    int seconds = stoi(duration.substr(first_colon + 4, 2));

    return hours * 3600 + minutes * 60 + seconds;
  }

  static double parse_dhhmmss(const std::string &duration) {
    auto pos_dash = duration.find('-');

    if (pos_dash != duration.npos) {
      int days = stoi(duration.substr(0, pos_dash));
      return days * 24 * 3600 + parse_hhmmss(duration.substr(pos_dash + 1));
    } else {
      return parse_hhmmss(duration);
    }
  }
};

double string_to_seconds(const std::string &duration) {
  return DurationParser::parse(duration);
}

} // namespace zisa
