/* Initialization for boost::log
 *
 * Authors: Luc Grosheintz <forbugrep@zoho.com>
 *    Date: 2014-09-09
 */

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sstream>

#include <zisa/utils/logging.hpp>
#include <zisa/utils/string_format.hpp>

void log_msg(char const *const file, const int line, char const *const severity,
             const std::string &msg) {
  auto &os = std::cerr;
  std::stringstream ss;

  ss << file << ":" << line << " [" << severity << "]: ";

  // #if TYR_HAS_MPI != 0
  //   int mpi_rank = -1;
  //   MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  //   ss << string_format("[PE %3d] ", mpi_rank);
  // #endif

  ss << msg << "\n";

  os << ss.str();
  os.flush();
}
