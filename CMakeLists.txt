cmake_minimum_required(VERSION 3.4)

option(BUILD_EXAMPLE "Build the sandbox project" ON)

add_subdirectory(Ren)

if(BUILD_EXAMPLE)
	add_subdirectory(Sandbox)
endif(BUILD_EXAMPLE)