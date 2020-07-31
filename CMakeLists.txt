project(mathAnalyzer)
cmake_minimum_required(VERSION 2.10)
include_directories($ENV{GTEST_HOME}/googletest/include $ENV{GTEST_HOME}/googlemock/include)
link_directories($ENV{GTEST_HOME}/build/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(sources 
    main.cpp
    mathAnalyzer.cpp)
set(testSources
    mathAnalyzerTest.cpp
    )
add_executable(mathAnalyzerTest ${testSources} ${sources})
target_link_libraries(mathAnalyzerTest gtest pthread)
