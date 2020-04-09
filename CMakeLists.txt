Cmake_minimum_required(VERSION 3.10)
include_directories(.)
add_definitions(-ggdb)
add_library(a SHARED a.cpp)
target_link_libraries(a PUBLIC pthread)

add_executable(b b.cpp)
target_link_libraries(b a dl)
