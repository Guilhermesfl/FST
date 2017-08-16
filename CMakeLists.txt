cmake_minimum_required(VERSION 2.8)

project(FST C)

# Changes the binary output directory to 'bin/'.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lm)
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
#add_subdirectory(src)
add_executable(FST
	../src/FST.c
	../src/main.c)

target_link_libraries(FST m)
# Adds the directory containing the test files for this project.
#add_subdirectory(test EXCLUDE_FROM_ALL)

