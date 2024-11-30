cmake_minimum_required(VERSION 3.26)
project(GapBuffer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.0
)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add executable for your test cases
add_executable(gbtest
        src/GapBufferTest.cpp
)

# Link GoogleTest with your test executable
target_link_libraries(gbtest gtest_main gtest)

# Enable testing
enable_testing()

# Add test cases
add_test(
        NAME GapBufferTests
        COMMAND gbtest
)

# Add a custom command to run tests with Valgrind via CTest
add_test(
    NAME GapBufferTestsValgrind
    COMMAND valgrind --track-origins=yes --leak-check=full --log-file=valgrind_output.txt ./gbtest
)
