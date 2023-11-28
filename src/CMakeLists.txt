cmake_minimum_required(VERSION 3.25.1)

project(CICDExperiment)

set(CMAKE_CXX_FLAGS "-std=gnu++20 -Wall -Wextra -Werror -Wfatal-errors")

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${GLOG_INCLUDE_DIR}
    PRIVATE Card
    PRIVATE Transaction
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE glog::glog
    PRIVATE Card
    PRIVATE Transaction
)

add_subdirectory(Card)

add_subdirectory(Transaction)

add_subdirectory(External)
