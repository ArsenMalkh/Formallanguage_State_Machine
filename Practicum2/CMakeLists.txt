cmake_minimum_required(VERSION 3.1)
project(Early)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(Early main.cpp Early.cpp)

enable_testing()
add_executable(Test tests.cpp Early.cpp)

add_test(Test ${Testing_SOURCE_DIR}/bin/testing_game)

target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

install (
        TARGETS Test
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

install (
        TARGETS Early
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
