include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
file(GLOB TEST_FILES ./*.cc)
set(TEST_SOURCES ${TEST_FILES})

FetchContent_MakeAvailable(googletest)

add_executable(
  all_containers_test
  ${TEST_SOURCES}
)

target_compile_options(
  all_containers_test PRIVATE
  -Wall -Werror -Wextra -pedantic -g
)

target_include_directories(
  all_containers_test
  PRIVATE
  ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  all_containers_test
  containers_lib
  containersplus_lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(all_containers_test)
