add_executable(CardTest CardTest.cpp)
target_include_directories(CardTest
    PRIVATE ${PROJECT_SOURCE_DIR}/src/Card
)
target_link_libraries(CardTest
    PRIVATE GTest::gtest_main
    PRIVATE Card
)
gtest_discover_tests(CardTest)
