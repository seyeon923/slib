enable_testing()

add_executable(list_test list_test.cc)
target_link_libraries(
    list_test 
    GTest::gtest_main
    slib)

include(GoogleTest)
gtest_discover_tests(list_test)