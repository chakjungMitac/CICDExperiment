cmake_minimum_required(VERSION 3.25.1)

project(CICDExperiment)

# Requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors")

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${GLOG_INCLUDE_DIR}
    PRIVATE Card
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE glog::glog
    PRIVATE Card
)

add_subdirectory(Card)

add_subdirectory(Transaction)

add_subdirectory(External)
