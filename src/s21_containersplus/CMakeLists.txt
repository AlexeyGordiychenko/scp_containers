cmake_minimum_required(VERSION 3.14)
project(ContainersplusLib LANGUAGES CXX)

file(GLOB FILE_SOURCES ./*/*.cc)
file(GLOB FILE_HEADERS ./*.h)
set(SOURCES ${FILE_SOURCES})
set(HEADERS ${FILE_HEADERS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
  add_library(
    containersplus_lib INTERFACE
    ${SOURCES}
    ${HEADERS}
  )
else()
  add_library(
    containersplus_lib
    ${SOURCES}
    ${HEADERS}
  )
endif()

set_target_properties(
  containersplus_lib PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "s21_"
  OUTPUT_NAME "containersplus"
)
