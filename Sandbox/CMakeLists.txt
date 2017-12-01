cmake_minimum_required(VERSION 3.4)
project(Sandbox)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-std=c++14)
endif()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/Ren/include
)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.c")

add_executable(Sandbox ${SRC})

target_link_libraries(Sandbox Ren)
