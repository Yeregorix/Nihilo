add_executable(Nihilo main.cpp
        loop.cpp
        loop.hpp
        animation/animator.cpp
        animation/animator.hpp
        manager.cpp
        manager.hpp
        simulation/simulator.cpp
        simulation/simulator.hpp
        animation/renderer.cpp
        animation/renderer.hpp
        animation/window.cpp
        animation/window.hpp
        animation/shader.cpp
        animation/shader.hpp
        animation/camera.cpp
        animation/camera.hpp
        animation/controller.cpp
        animation/controller.hpp
        animation/control.hpp
        simulation/simulation.hpp)

find_package(OpenGL REQUIRED)

target_link_libraries(Nihilo PRIVATE glfw OpenGL::GL glad glm::glm atomic)
