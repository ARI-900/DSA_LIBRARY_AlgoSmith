
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(test_linkedlist test_linkedlist.cpp)
target_link_libraries(test_linkedlist PRIVATE algosmith GTest::gtest_main)

add_executable(test_doublylinkedlist test_doublylinkedlist.cpp)
target_link_libraries(test_doublylinkedlist PRIVATE algosmith GTest::gtest_main)

add_executable(test_bst test_bst.cpp)
target_link_libraries(test_bst PRIVATE algosmith GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_linkedlist)
gtest_discover_tests(test_doublylinkedlist)
gtest_discover_tests(test_bst)

