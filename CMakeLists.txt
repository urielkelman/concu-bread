cmake_minimum_required(VERSION 3.16)
project(concu_bread)

set(CMAKE_CXX_STANDARD 11)

add_executable(concu_bread main.cpp concurrencia/MemoriaCompartida.h)