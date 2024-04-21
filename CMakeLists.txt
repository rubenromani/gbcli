
cmake_minimum_required(VERSION 3.1...3.29)
project(
  GBcli
  VERSION 1.0
  LANGUAGES CXX)

include_directories(src/include)
add_executable(GBcli src/main.cpp src/cpu.cpp)
