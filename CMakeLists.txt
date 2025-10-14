cmake_minimum_required(VERSION 3.31)
project(Nihilo)

set(CMAKE_CXX_STANDARD 23)

# -fno-rtti: GCC bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=110572
# -mwindows: hide console
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -mwindows -fno-rtti")

add_subdirectory(assets)
add_subdirectory(lib)
add_subdirectory(src)
