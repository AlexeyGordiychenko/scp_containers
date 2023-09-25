cmake_minimum_required(VERSION 3.14)
project(Containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_PROFILE --coverage)

add_subdirectory(s21_containers)
add_subdirectory(s21_containersplus)
add_subdirectory(tests)
