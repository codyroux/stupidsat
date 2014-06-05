cmake_minimum_required(VERSION 2.8.7)
project(STUPIDSAT CXX)
set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()
include(CTest)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++0x -fPIC")

# SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})
SET(CMAKE_SWIG_FLAGS "")

# Python
FIND_PACKAGE(PythonLibs 2.7)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

# Executable
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(stupidsat main.cpp solver.cpp litteral.cpp)

# Swig Setting
SET_SOURCE_FILES_PROPERTIES(solver.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(solver python solver.i solver.cpp litteral.cpp)
SWIG_LINK_LIBRARIES(solver ${PYTHON_LIBRARIES})
