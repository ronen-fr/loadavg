// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab


#include <benchmark/benchmark.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <unistd.h>

#include "loadavg.h"


static void bench_Fload(benchmark::State& state) {
  // Code before the loop is not measured
  ScrubAverages sav;
  Fload a(sav);

  for (auto _ : state) {
    a.update_averages();
  }

  a.show(" - ");
}
BENCHMARK(bench_Fload);


static void bench_Getloadsys(benchmark::State& state) {
  // Code before the loop is not measured
  ScrubAverages sav;
  Getloadsys a(sav);

  for (auto _ : state) {
    a.update_averages();
  }

  a.show(" - ");
}
BENCHMARK(bench_Getloadsys);

BENCHMARK_MAIN();


