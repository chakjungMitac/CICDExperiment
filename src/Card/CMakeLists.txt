add_library(Card STATIC Card.cpp)
target_include_directories(Card
    PRIVATE ${GLOG_INCLUDE_DIR}
)
target_link_libraries(Card
    PRIVATE glog::glog
)
