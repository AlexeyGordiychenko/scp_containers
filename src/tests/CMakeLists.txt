cmake_minimum_required(VERSION 3.14)
project(ContainersTests LANGUAGES CXX)

find_package(GTest)

if (NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

file(GLOB TEST_FILES_CC ./*.cc)
file(GLOB TEST_FILES_H ./test.h)
set(TEST_SOURCES ${TEST_FILES_CC})
set(TEST_HEADERS ${TEST_FILES_H})

add_executable(
  all_containers_test
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_include_directories(
  all_containers_test
  PRIVATE
  ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
  all_containers_test
  PUBLIC
  gtest
  containers_lib
  containersplus_lib
)

include(GoogleTest)
gtest_discover_tests(all_containers_test)
