cmake_minimum_required(VERSION 3.14)
project(ContainersLib LANGUAGES CXX)

file(GLOB FILE_SOURCES ./*/*.cc)
file(GLOB FILE_HEADERS ./*/*.h)
set(SOURCES ${FILE_SOURCES})
set(HEADERS ${FILE_HEADERS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (APPLE)
  add_library(
    containers_lib INTERFACE
    ${SOURCES}
    ${HEADERS}
  )
else()
  add_library(
    containers_lib
    ${SOURCES}
    ${HEADERS}
  )
endif()


set_target_properties(
  containers_lib PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "scp_"
  OUTPUT_NAME "containers"
)
