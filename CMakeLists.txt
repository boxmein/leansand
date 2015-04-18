cmake_minimum_required(VERSION 3.2)

project (leansand) #Define project name

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake") #Set cmake directory with custom .cmake scripts to module path

include_directories(include/) #Include directory

find_package(SDL2 REQUIRED) #Find SDL2, uses FindSDL2.cmake from cmake/

add_executable(leansand src/leansand.cpp)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(leansand ${SDL2_LIBRARY})

