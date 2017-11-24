cmake_minimum_required(VERSION 3.7)
project(CppGrammer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp 18-NewC11standard/newc11standard.h 18-NewC11standard/newc11standard.cpp 18-NewC11standard/18-test.cpp 17-InputOutputFile/inputOutputFile.h 17-InputOutputFile/inputOutputFile.cpp)
add_executable(CppGrammer ${SOURCE_FILES})