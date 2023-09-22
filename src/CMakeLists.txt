cmake_minimum_required(VERSION 3.14)
project(Containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_PROFILE --coverage)

add_subdirectory(s21_containers)
add_subdirectory(s21_containersplus)
add_subdirectory(tests)






# cmake_minimum_required(VERSION 3.14)
# project(Containers LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS_PROFILE --coverage)
# set(
#     SOURCES
#     s21_vector.cc
# )
# set(
#     HEADERS
#     s21_vector.h
# )
# enable_testing()

# add_subdirectory(tests)

# add_library(
#     matrixplus_lib STATIC
#     ${SOURCES}
#     ${HEADERS}
# )
# target_compile_options(
#     matrixplus_lib PRIVATE
#     -Wall -Werror -Wextra -pedantic -g
# )
# set_target_properties(
#     matrixplus_lib PROPERTIES
#     PREFIX ""
#     OUTPUT_NAME "s21_matrix_oop"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}" 
# )
