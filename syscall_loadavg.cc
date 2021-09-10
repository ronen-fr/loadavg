// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include <fcntl.h>
#include <fmt/core.h>
#include <unistd.h>

#include <charconv>
#include <cstdio>
#include <iostream>

#include "loadavg.h"

static constexpr const char* averages_file{"/proc/loadavg"};

Getloadsys::Getloadsys(ScrubAverages& sav) : sav_{sav}
{
  cpu_num_ = 2;	 // TBD

  update_averages();
}


void Getloadsys::update_averages()
{
  if (failed_)
    return;


  if (getloadavg(vs_, 3) != 3) {
    perror(" couldn't read loadavgs");
    mark_failure();
    return;
  }

  sav_.load_per_cpu_ = vs_[0] / cpu_num_;

  sav_.daily_ = welf_.nxt(sav_.load_per_cpu_);
  sav_.improving_ = vs_[0] < sav_.daily_ && vs_[0] < vs_[2];
}


Getloadsys::~Getloadsys()
{
}


void Getloadsys::mark_failure()
{
  failed_ = true;
  std::cout << "\nfailed\n";
}

void Getloadsys::show(std::string_view title)
{
  fmt::print("{}:  {}({}) / .. / {}  ->  {} {}  [N:{}]\n", title, vs_[0],
	     sav_.load_per_cpu_, vs_[2], sav_.daily_,
	     sav_.improving_ ? "imp" : "xxx", welf_.n_);
}
