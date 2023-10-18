cmake_minimum_required(VERSION 3.14)
project(ContainersLib LANGUAGES CXX)

file(GLOB FILE_SOURCES ./*/*.cc)
file(GLOB FILE_HEADERS ./*/*.h)
set(SOURCES ${FILE_SOURCES})
set(HEADERS ${FILE_HEADERS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  containers_lib
  ${SOURCES}
  ${HEADERS}
)

set_target_properties(
  containers_lib PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "s21_"
  OUTPUT_NAME "containers"
  # ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" 
)
