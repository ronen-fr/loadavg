cmake_minimum_required(VERSION 3.18)
project(bench1)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
find_package(fmt REQUIRED)


add_executable(bench1 main.cpp)

target_link_libraries(bench1 benchmark::benchmark fmt::fmt)
