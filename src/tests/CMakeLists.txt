include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
file(GLOB TEST_FILES_CC ./*.cc)
file(GLOB TEST_FILES_H ./test.h)
set(TEST_SOURCES ${TEST_FILES_CC})
set(TEST_HEADERS ${TEST_FILES_H})

FetchContent_MakeAvailable(googletest)

add_executable(
  all_containers_test
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_compile_options(
  all_containers_test PRIVATE
  -Wall -Werror -Wextra -pedantic -g
)

target_include_directories(
  all_containers_test
  PRIVATE
  ${CMAKE_BINARY_DIR}/s21_containers
  ${CMAKE_BINARY_DIR}/s21_containersplus
  ${CMAKE_BINARY_DIR}/lib
)

target_link_libraries(
  all_containers_test
  PUBLIC
  GTest::gtest_main
  containers_lib
  containersplus_lib
)

include(GoogleTest)
gtest_discover_tests(all_containers_test)
