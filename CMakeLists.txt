cmake_minimum_required(VERSION 3.13) 
project(comp)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(elements)
add_executable(comp Comp.cpp DOM.h DOM.cpp)
target_link_libraries(comp ELEMENTS)