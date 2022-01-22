enable_testing()
add_executable(
    goal_tree_test
    goal_tree_test.cpp
    test_utils.hpp
)

add_executable(
    block_test
    block_test.cpp
)

add_executable(
    table_test
    table_test.cpp
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(
    goal_tree_test
    GTest::gtest
    gtest_main
    src
)

target_link_libraries(
    block_test
    GTest::gtest
    gtest_main
    src
)

target_link_libraries(
    table_test
    GTest::gtest
    gtest_main
    src
)

include(GoogleTest)
gtest_discover_tests(goal_tree_test)