/* Includes and condif for boost::log.
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2014-09-09
 */
#ifndef LOGGING_HPP_B0KMI7N1
#define LOGGING_HPP_B0KMI7N1

#include <assert.h>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef ZISA_SILENT
#define ZISA_LOG_LEVEL -100
#endif

#ifndef ZISA_LOG_LEVEL
#define ZISA_LOG_LEVEL 0
#endif

void log_init(std::string log_file);

/// Simple logging.
/** Log a message to file.
 *
 *  @param file __FILE__
 *  @param line __LINE__
 *  @param severity message severity.
 *  @param msg message to log
 */
void log_msg(char const *const file,
             const int line,
             char const *const severity,
             const std::string &msg);

/// Outright errors.
#define LOG_ERR(msg)                                                           \
  log_msg(__FILE__, __LINE__, "ERROR", (msg));                                 \
  throw std::runtime_error(msg);

#define LOG_ERR_IF(cond, msg)                                                  \
  if (cond) {                                                                  \
    LOG_ERR(msg);                                                              \
  }

/// Critical warnings. Mostly on.
#if ZISA_LOG_LEVEL >= 0
#define LOG_WARN(msg) log_msg(__FILE__, __LINE__, "WARN", (msg))
#else
#define LOG_WARN(msg)
#endif

#define LOG_WARN_IF(cond, msg)                                                 \
  if (cond) {                                                                  \
    LOG_WARN(msg);                                                             \
  }

#if ZISA_LOG_LEVEL >= 1
#define LOG(msg) log_msg(__FILE__, __LINE__, "INFO", (msg))
#else
#define LOG(msg)
#endif

/// VERY verbose, spammy logging
#if ZISA_LOG_LEVEL >= 2
#define LOG_TRACE(msg) log_msg(__FILE__, __LINE__, "TRACE", (msg))
#else
#define LOG_TRACE(msg)
#endif

/// Simple debug logging
#ifdef ZISA_LOG_DEBUG
#define LOG_DEBUG(msg) log_msg(__FILE__, __LINE__, "DEBUG", (msg))
#else
#define LOG_DEBUG(msg)
#endif

#define XISX(X) #X << " = " << X
#define PRINT(X) std::cout << XISX(X) << "\n"

#endif /* end of include guard: LOGGING_HPP_B0KMI7N1 */
