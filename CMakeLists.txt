project(mathAnalyzer)
cmake_minimum_required(VERSION 2.10)
include_directories($ENV{GTEST_HOME}/googletest/include $ENV{GTEST_HOME}/googlemock/include)
link_directories($ENV{GTEST_HOME}/build/lib)
add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources 
    main.cpp
    mathAnalyzer.cpp)
set(testSources
    mathAnalyzerTest.cpp
    )
add_executable(test ${testSources} ${sources})
target_link_libraries(test gtest pthread)
