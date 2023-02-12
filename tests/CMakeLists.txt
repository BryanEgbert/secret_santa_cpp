include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(secret_santa_test secret_santa_test.cpp)

target_link_libraries(
    secret_santa_test
    PRIVATE
    GTest::GTest
    secret_santa_lib
)

include(GoogleTest)
add_test(secret_santa_gtest secret_santa_test)
set_tests_properties(secret_santa_gtest PROPERTIES TIMEOUT 100)