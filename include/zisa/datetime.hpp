/* Collection of routines to manipulate dates and times.
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2016-12-11
 */
#ifndef DATETIME_H_TZXNLSQO
#define DATETIME_H_TZXNLSQO

#include <ctime>
#include <string>

namespace zisa {
#if ZISA_HAS_MPI == 1
using time_stamp_t = double;
#else
using time_stamp_t = std::time_t;
#endif

/// Format the date as 'YYYY-MM-DD HH:MM:SS UTC%z'.
std::string date_format(const std::time_t &time);

/// Format the date as 'HH:MM:SS'.
std::string time_format(const std::time_t &time);

/// Format the duration as 'd-HH:MM:SS'.
/** Fractional seconds are truncated. */
std::string duration_format(double seconds);

/// Get a time-stamp of the current time.
zisa::time_stamp_t current_time_stamp();

/// Get the current date.
std::time_t current_date();

/// Get the current time.
std::time_t current_time();

double elapsed_seconds(const zisa::time_stamp_t &newer,
                       const zisa::time_stamp_t &older);

double elapsed_seconds_since(const zisa::time_stamp_t &reference);

/// Convert the string "d-HH:MM:SS" to seconds.
double string_to_seconds(const std::string &duration);

}
#endif /* end of include guard: DATETIME_H_TZXNLSQO */
