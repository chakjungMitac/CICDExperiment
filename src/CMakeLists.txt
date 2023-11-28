cmake_minimum_required(VERSION 3.25.1)

project(CICDExperiment)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wfatal-errors")

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Card)

add_subdirectory(Transaction)

add_subdirectory(External)
