/* Initialization for boost::log
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2014-09-09
 */
#include <zisa/utils/logging.hpp>

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

#if ZISA_HAS_MPI != 0
#include <mpi.h>
#endif

#include <zisa/utils/string_format.hpp>
#include <zisa/datetime.hpp>

void log_msg(char const *const file,
             const int line,
             char const *const severity,
             const std::string &msg) {
  auto &os = std::cerr;
  std::stringstream ss;

  ss << file << ":" << line << " [" << severity << "]: ";

   #if ZISA_HAS_MPI != 0
     int rank = -1;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     ss << string_format("[PE %3d] ", rank);
   #endif

   auto current_time = zisa::time_format(zisa::current_time());

  ss << current_time << "  " << msg << "\n";

  os << ss.str();
  os.flush();
}
