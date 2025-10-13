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
        simulation/simulation.hpp
        simulation/motion.cpp
        simulation/motion.hpp
        simulation/force.cpp
        simulation/force.hpp
        simulation/integration.cpp
        simulation/integration.hpp
        animation/font.cpp
        animation/font.hpp
        box.hpp
        animation/vertex.cpp
        animation/vertex.hpp)

find_package(OpenGL REQUIRED)

target_link_libraries(Nihilo PRIVATE glfw OpenGL::GL glad glm::glm freetype atomic)
