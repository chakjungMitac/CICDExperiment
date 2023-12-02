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
