cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(secret_santa VERSION 1.0.0)

include(CTest)
enable_testing()

find_package(SQLite3 REQUIRED)

add_subdirectory(tests)
add_subdirectory(src)

include_directories(${SQLITE3_INCLUDE_DIRS})

add_executable(secret_santa_app main.cpp)
target_link_libraries(secret_santa_app ${SQLITE3_LIBRARIES} secret_santa_lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
