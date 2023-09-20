# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        release-1.11.0
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# file(GLOB TEST_FILES ./*.cc)
# set(TEST_SOURCES ${TEST_FILES})

# FetchContent_MakeAvailable(googletest)

# add_executable(
#   matrixplus_test
#   ${TEST_SOURCES}
# )
# target_compile_options(
#   matrixplus_test PRIVATE
#   -Wall -Werror -Wextra -pedantic
# )
# target_link_libraries(
#   matrixplus_test
#   GTest::gtest_main
#   matrixplus_lib
# )

# include(GoogleTest)
# gtest_discover_tests(matrixplus_test)
