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

// the 'float' version

Fload::Fload(ScrubAverages& sav) : sav_{sav}
{
  cpu_num_ = 2;	 // TBD
  load_fd_ = open(averages_file, O_RDONLY);
  if (load_fd_ < 0) {
    perror("Failed to open load-average system file");
    return;
  }

  update_averages();
}


void Fload::update_averages()
{
  if (load_fd_ < 0) {
    return;
  }

  char buf[64];
  auto ret = pread(load_fd_, buf, sizeof(buf), 0);
  if (ret <= 0) {
    perror("Reading the load-average system file has failed");
    mark_failure();
    return;
  }

  auto [ptr, ec]{std::from_chars(buf, buf + ret, avg_1m)};
  if (ec != std::errc{}) {
    mark_failure();
    return;
  }

  // float avg_5m{3.0f};
  auto [ptr5, ec5]{std::from_chars(ptr + 1, buf + ret, avg_5m)};
  if (ec5 != std::errc{}) {
    mark_failure();
    return;
  }


  // float avg_15m{3.0f};
  auto [ptr15, ec15]{std::from_chars(ptr5 + 1, buf + ret, avg_15m)};
  if (ec15 != std::errc{}) {
    mark_failure();
    return;
  }

  sav_.load_per_cpu_ = avg_1m / cpu_num_;

  // sav_.daily_ = ((daily_samples - 1) * sav_.daily_ + sav_.load_per_cpu_) /
  // daily_samples;
  sav_.daily_ = welf_.nxt(sav_.load_per_cpu_);
  sav_.improving_ = avg_1m < sav_.daily_ && avg_1m < avg_15m;

  // fmt::print("Got {} - {} - {}\n", avg_1m, avg_5m, avg_15m);
}


Fload::~Fload()
{
  if (load_fd_ >= 0) {
    close(load_fd_);
  }
}


void Fload::mark_failure()
{
  close(load_fd_);
  load_fd_ = -1;  // preventing further tries
  std::cout << "\nfailed\n";
}

void Fload::show(std::string_view title)
{
  fmt::print("{}:  {}({}) / .. / {}  ->  {} {}  [N:{}]\n", title, avg_1m,
	     sav_.load_per_cpu_, avg_15m, sav_.daily_,
	     sav_.improving_ ? "imp" : "xxx", welf_.n_);
}

// ---------- the 'double' version

Fload_dbl::Fload_dbl(ScrubAverages& sav) : sav_{sav}
{
  cpu_num_ = 2;	 // TBD
  load_fd_ = open(averages_file, O_RDONLY);
  if (load_fd_ < 0) {
    perror("Failed to open load-average system file");
    return;
  }

  update_averages();
}


void Fload_dbl::update_averages()
{
  if (load_fd_ < 0) {
    return;
  }

  char buf[64];
  auto ret = pread(load_fd_, buf, sizeof(buf), 0);
  if (ret <= 0) {
    perror("Reading the load-average system file has failed");
    mark_failure();
    return;
  }

  auto [ptr, ec]{std::from_chars(buf, buf + ret, avg_1m)};
  if (ec != std::errc{}) {
    mark_failure();
    return;
  }

  // float avg_5m{3.0f};
  auto [ptr5, ec5]{std::from_chars(ptr + 1, buf + ret, avg_5m)};
  if (ec5 != std::errc{}) {
    mark_failure();
    return;
  }


  // float avg_15m{3.0f};
  auto [ptr15, ec15]{std::from_chars(ptr5 + 1, buf + ret, avg_15m)};
  if (ec15 != std::errc{}) {
    mark_failure();
    return;
  }

  sav_.load_per_cpu_ = avg_1m / cpu_num_;

  // sav_.daily_ = ((daily_samples - 1) * sav_.daily_ + sav_.load_per_cpu_) /
  // daily_samples;
  sav_.daily_ = welf_.nxt(sav_.load_per_cpu_);
  sav_.improving_ = avg_1m < sav_.daily_ && avg_1m < avg_15m;

  // fmt::print("Got {} - {} - {}\n", avg_1m, avg_5m, avg_15m);
}


Fload_dbl::~Fload_dbl()
{
  if (load_fd_ >= 0) {
    close(load_fd_);
  }
}


void Fload_dbl::mark_failure()
{
  close(load_fd_);
  load_fd_ = -1;  // preventing further tries
  std::cout << "\nfailed\n";
}

void Fload_dbl::show(std::string_view title)
{
  fmt::print("{}:  {}({}) / .. / {}  ->  {} {}  [N:{}]\n", title, avg_1m,
	     sav_.load_per_cpu_, avg_15m, sav_.daily_,
	     sav_.improving_ ? "imp" : "xxx", welf_.n_);
}
