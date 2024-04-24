cmake_minimum_required(VERSION 3.1...3.29)
project(
  GBcli
  VERSION 1.0
  LANGUAGES CXX)

project(
  GBtest
  VERSION 1.0
  LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(src/include)
add_executable(GBcli src/main.cpp src/cpu.cpp)
add_executable(GBtest src/cpu.cpp test/cpu_test.cpp)
target_link_libraries(GBtest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(GBtest)
