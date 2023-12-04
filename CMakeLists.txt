cmake_minimum_required(VERSION 3.25.1)

project(CICDExperiment)

# Requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors")

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
