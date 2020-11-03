cmake_minimum_required(VERSION 3)
project(FormalPrac)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(FormalPrac main.cpp Regular.cpp)

enable_testing()
add_executable(Test tests.cpp Regular.cpp)

add_test(Test ${Testing_SOURCE_DIR}/bin/testing_game)

target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

install (
        TARGETS Test
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

install (
        TARGETS practicum
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
