cmake_minimum_required(VERSION 3.14)
project(Containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")

set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS} --coverage")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

add_subdirectory(scp_containers)
add_subdirectory(scp_containersplus)
add_subdirectory(tests)
