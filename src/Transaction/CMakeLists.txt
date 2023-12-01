add_library(Transaction STATIC Transaction.cpp)
target_include_directories(Transaction
    PRIVATE ${GLOG_INCLUDE_DIR}
    PRIVATE ${PROJECT_SOURCE_DIR}/Card
)
target_link_libraries(Transaction
    PRIVATE glog::glog
    PRIVATE Card
)
