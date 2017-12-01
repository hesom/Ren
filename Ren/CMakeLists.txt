cmake_minimum_required(VERSION 3.4)
project(Ren)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-std=c++14)
endif()

set(LIB_ROOT_DIR libs)

add_subdirectory(${LIB_ROOT_DIR}/glfw-3.2.1)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${LIB_ROOT_DIR}/glfw-3.2.1/include
  ${LIB_ROOT_DIR}/glad
  ${LIB_ROOT_DIR}/KHR
)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.c")

add_library(Ren STATIC ${SRC})

find_package(OpenGL)

target_link_libraries(Ren ${OPENGL_gl_LIBRARY})
target_link_libraries(Ren glfw)
