// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
#if 0

#include <string>
#include <iostream>
#include <sstream>
#include <new>
#include <memory>
#include <cstring>
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>

using namespace std;

static int glvl = 30;

ostream& dout(int lev)
{
  return cout;
}

#define dendl "\n"


struct Slogger {
  template<int LVL, typename... Args>
  static void log_if_level(const char* fmt, Args&&... a)
  {
    fmt::memory_buffer out;
    fmt::format_to(out, fmt, a...);
    //dout(LVL) << to_string(out) << dendl;
    if (LVL <= glvl)
      dout(LVL) << to_string(out) << dendl;
  }

  template<typename... Args>
  static inline void debug(const char* fmt, Args&&... a)
  {
    Slogger::log_if_level<20>(fmt, std::forward<Args>(a) ...);
  }

};

namespace {
static inline Slogger slogger{};

Slogger& logger() { return slogger; }
}



void test_log(int k)
{
  cout << "------------\n";

  dout(1) << "the dout " << k << dendl;

  logger().debug("A logger debug {} {} {}", __func__, k, (k > 10) ? " >>> " : " <<< ");
}

int main()
{
  test_log(100);
  test_log(1);


}



#endif
