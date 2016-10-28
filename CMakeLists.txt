cmake_minimum_required(VERSION 3.6)
project(PO2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp komunikazioa.c komunikazioa.h)
add_executable(PO2 ${SOURCE_FILES} funtzioak.c funtzioak.h)