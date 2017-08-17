cmake_minimum_required(VERSION 2.8)

project(FST C)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Changes the binary output directory to 'bin/'.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Generates a verbose Makefile.
# HINT: Run `make VERBOSE=1`.
#set(CMAKE_VERBOSE_MAKEFILE true)

# Instructs the compiler to generate code for x86 ISA (this setting has global
# scope).
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -m32)

# Adds the qlibc library directory.
#add_subdirectory(lib/minqlibc)

# Tells the application where to find the libraries' header files.
#include_directories(lib/minunit)

# Adds the directory containing the source files for this project.
add_executable(FST
	../src/main.c
	../src/FST.c)
target_link_libraries(FST m)
# Adds the directory containing the test files for this project.
#add_subdirectory(test EXCLUDE_FROM_ALL)
set(CMAKE_BUILD_TYPE Release)
