project(mathAnalyzer)
cmake_minimum_required(VERSION 2.10)
include_directories($ENV{GTEST_HOME}/googletest/include)
link_directories($ENV{GTEST_HOME}/build/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(commonSources
    src/mathAnalyzer.cpp
    src/token.cpp
    src/tokenStream.cpp
    )
set (mainSources
    app/main.cpp
    )
set(testSources
    test/mainTests.cpp
    test/mathAnalyzerTest.cpp
    )


add_executable(mathAnalyzer ${commonSources} ${mainSources})
add_executable(mathAnalyzerTest ${commonSources} ${testSources})
target_link_libraries(mathAnalyzer gtest pthread)
target_link_libraries(mathAnalyzerTest gtest pthread)
