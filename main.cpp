#include <benchmark/benchmark.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <unistd.h>

#include "loadavg.h"


int main()
{
  ScrubAverages sav;
  Fload a(sav);

  //a.update_averages();
  //a.show("first");
  //a.update_averages();
  //a.show("2nd");

  for (int k = 0; k < 600; ++k) {
    usleep(50'000);
    a.update_averages();
    if (!(k % 20)) {
      a.show(" - ");
    }
  }
}



#if 0


static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
//BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
//BENCHMARK(BM_StringCopy);

float dt1 = 13.35f;
volatile int dt2 = 100;
volatile bool repair = true;

int outsum = 0;

#include <sstream>



static void CondFmtTodn(benchmark::State& state) {
  // Code before the loop is not measured
  fmt::memory_buffer out;
  std::string x = "hello";
  int c = 10;

  for (auto _ : state) {
    c *= -1;
    fmt::format_to(out, "{} is {}", dt1, x );

    if (c > 0) {
      fmt::format_to(out, " {} errors", c);
    } else {
      fmt::format_to(out, "ok");
    }

    if (repair) {
      fmt::format_to(out, "{} fixed ", repair);
    }

    if (dt2 > 1) {
      fmt::format_to(out, " {} dt2", dt2);
    }

    benchmark::DoNotOptimize(out);
  }
}
BENCHMARK(CondFmtTodn);

static void CondStrstr(benchmark::State& state) {
  // Code before the loop is not measured
  std::string x = "hello";
  int c = 10;
  for (auto _ : state) {
    c *= -1;
    std::stringstream oss;
    oss << dt1 << " is " << x;
    if (c > 0) {
      oss << c << "errors";
    } else {
      oss << "ok";
    }

    if (repair) {
      oss << repair << " fixed";
    }

    if (dt2 > 1) {
      oss << dt2 << " dt2 ";
    }

    outsum += oss.str()[2];
  }
}
BENCHMARK(CondStrstr);


static void CondFmt(benchmark::State& state) {
  // Code before the loop is not measured
  std::string x = "hello";
  int c = 10;
  for (auto _ : state) {
    c *= -1;
    auto ret = fmt::format("{} is {}", dt1, x );

    if (c > 0) {
      ret += fmt::format(" {} errors", c);
    } else {
      ret += "ok";
    }

    if (repair) {
      ret += fmt::format("{} fixed ", repair);
    }

    if (dt2 > 1) {
      ret += fmt::format(" {} dt2", dt2);
    }

    outsum += ret.c_str()[2];
  }
}
BENCHMARK(CondFmt);


static void CondFmtTo(benchmark::State& state) {
  // Code before the loop is not measured
  fmt::memory_buffer out;
  std::string x = "hello";
  int c = 10;

  for (auto _ : state) {
    c *= -1;
    fmt::format_to(out, "{} is {}", dt1, x );

    if (c > 0) {
      fmt::format_to(out, " {} errors", c);
    } else {
      fmt::format_to(out, "ok");
    }

    if (repair) {
      fmt::format_to(out, "{} fixed ", repair);
    }

    if (dt2 > 1) {
      fmt::format_to(out, " {} dt2", dt2);
    }

    outsum += out.data()[2];
  }
}
BENCHMARK(CondFmtTo);



#ifdef ASIDE_WHILE_TESTING_SOMETHING_ELSE
BENCHMARK_MAIN();
#endif


void handle_cpu_freq()
{
  /*

 cpupower frequency-info



    */


}



#if 0



#include <iostream>


//#include <benchmark/benchmark_api>


#include "../commonTest.h"
#include "benchmark/benchmark_api.h"

void IntToString(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(
      IntToStringConversionTest(state.range_x())
    );
  }
}
BENCHMARK(IntToString)->Arg(TEST_NUM_COUNT1000);

void DoubleToString(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(
      DoubleToStringConversionTest(state.range_x())
    );
  }
}
BENCHMARK(DoubleToString)->Arg(TEST_NUM_COUNT1000);

BENCHMARK_MAIN()
float dt1 = 13.35f;
volatile int dt2 = 100;
volatile bool repair = true;
#include <sstream>

static void CondStrstr(benchmark::State& state) {
  // Code before the loop is not measured
  std::string x = "hello";
  int c = 10;
  for (auto _ : state) {
    c *= -1;
    std::stringstream oss;
    oss << dt1 << " is " << x;
    if (c > 0) {
      oss << c << "errors";
    } else {
      oss << "ok";
    }

    if (repair) {
      oss << repair << " fixed";
    }

    if (dt2 > 1) {
      oss << dt2 << " dt2 ";
    }

  }
}
BENCHMARK(CondStrstr);

#include <fmt/core.h>

static void CondFmt(benchmark::State& state) {
  // Code before the loop is not measured
  std::string x = "hello";
  int c = 10;
  for (auto _ : state) {
    c *= -1;
    auto ret = fmt::format("{} is {}", dt1, x );

    if (c > 0) {
      ret += fmt::format(" {} errors", c);
    } else {
      ret += "ok";
    }

    if (repair) {
      ret += fmt::format("{} fixed ", repair);
    }

    if (dt2 > 1) {
      ret += fmt::format(" {} dt2", dt2);
    }

  }
}
BENCHMARK(CondFmt);

BENCHMARK_MAIN();

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
#endif
#endif
