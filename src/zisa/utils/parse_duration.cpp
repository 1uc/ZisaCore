// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#include <regex>

#include <zisa/utils/logging.hpp>
#include <zisa/utils/parse_duration.hpp>
#include <zisa/utils/string_format.hpp>

namespace zisa {

std::chrono::milliseconds parse_duration_ms(const std::string &duration) {
  std::regex re("([[:digit:]]+)(s|ms)");

  std::smatch sm;
  bool status = std::regex_match(duration, sm, re);

  LOG_ERR_IF(!status,
             string_format("Failed to parse duration. [%s]", duration.c_str()));

  int n = std::stoi(sm[1]);
  std::string units = sm[2];

  if (sm[2] == "s") {
    return std::chrono::seconds(n);
  } else if (sm[2] == "ms") {
    return std::chrono::milliseconds(n);
  }

  LOG_ERR("Broken logic of some sort.");
}

} // namespace zisa
