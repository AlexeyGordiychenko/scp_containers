file(GLOB FILE_SOURCES ./*/*.cc)
file(GLOB FILE_HEADERS ./*.h)
set(SOURCES ${FILE_SOURCES})
set(HEADERS ${FILE_HEADERS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  containersplus_lib STATIC
  ${SOURCES}
  ${HEADERS}
)

target_compile_options(
  containersplus_lib PRIVATE
  -Wall -Werror -Wextra -pedantic -g
)

set_target_properties(
  containersplus_lib PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "s21_"
  OUTPUT_NAME "containersplus"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" 
)
