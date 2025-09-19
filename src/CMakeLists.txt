add_executable(Nihilo main.cpp
        loop.cpp
        loop.hpp
        animation/animator.cpp
        animation/animator.hpp
        manager.cpp
        manager.hpp
        simulation/simulator.cpp
        simulation/simulator.hpp)

find_package(OpenGL REQUIRED)

target_link_libraries(Nihilo glfw OpenGL::GL glad)
