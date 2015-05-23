cmake_minimum_required(VERSION 3.0)

project (leansand) #Define project name

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake") #Set cmake directory with custom .cmake scripts to module path

include_directories(include/) #Include directory

find_package(SDL2 REQUIRED) #Find SDL2, uses FindSDL2.cmake from cmake/

option(NOJIT "Use vanilla Lua instead of LuaJIT" OFF)
if(NOJIT)
  find_package(Lua51 REQUIRED)
  add_definitions(-D_NOJIT)
else(NOJIT)
  find_package(LuaJIT REQUIRED)
endif(NOJIT)

file(GLOB leansandsrc
    "src/*.cpp"
)

add_executable(leansand ${leansandsrc})

include_directories(${SDL2_INCLUDE_DIR} ${LUA_INCLUDE_DIR})
target_link_libraries(leansand ${SDL2_LIBRARY} ${LUA_LIBRARY})

