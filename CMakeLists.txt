cmake_minimum_required(VERSION 3.14)
project(algo_labs C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googlebenchmark)

enable_testing()

add_executable(lab_5
        lab_5/main.c
        lab_5/krascal.c
        lab_5/krascal.h)

add_executable(lab_5_tests
        lab_5/tests.cpp
        lab_5/krascal.c)
add_executable(lab_5_bench
        lab_5/benchmark.cpp
        lab_5/krascal.c)
target_link_libraries(lab_5_bench benchmark::benchmark)
target_link_libraries(lab_5_tests gtest_main gtest stdc++ benchmark::benchmark)


include(GoogleTest)
gtest_discover_tests(lab_5_tests)
