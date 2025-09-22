cmake_minimum_required(VERSION 3.31)
project(Nihilo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_subdirectory(lib)
add_subdirectory(src)
