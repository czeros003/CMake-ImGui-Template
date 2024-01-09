cmake_minimum_required(VERSION 3.15)
project(CMakeProject)

set(CMAKE_CXX_STANDARD 17)

# Adding other directories to include with Cmake
add_subdirectory(libs)
add_subdirectory(src)
