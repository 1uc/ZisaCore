// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

//
// Created by lucg on 10/30/20.
//

#ifndef ZISA_TIMER_HPP
#define ZISA_TIMER_HPP

#include <chrono>
#include <zisa/config.hpp>

namespace zisa {

class Timer {
private:
  using clock = std::chrono::steady_clock;

protected:
  auto now() const { return clock::now(); }

public:
  Timer() : t_start(now()) {}

  void reset() { t_start = now(); }

  inline double elapsed_seconds() const {
    return std::chrono::duration<double>(now() - t_start).count();
  }

private:
  clock::time_point t_start;
};

}

#endif // ZISA_TIMER_HPP
