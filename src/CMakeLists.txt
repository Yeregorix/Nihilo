add_executable(Nihilo main.cpp
        loop.cpp
        loop.hpp
        manager.cpp
        manager.hpp
        box.hpp
        timing.cpp
        timing.hpp
        control/window.cpp
        control/window.hpp
        control/camera.cpp
        control/camera.hpp
        control/controller.cpp
        control/controller.hpp
        control/control.hpp
        render/renderer.cpp
        render/renderer.hpp
        render/shader.cpp
        render/shader.hpp
        render/font.cpp
        render/font.hpp
        render/vertex.cpp
        render/vertex.hpp
        render/rectangle.cpp
        render/rectangle.hpp
        simulation/simulator.cpp
        simulation/simulator.hpp
        simulation/simulation.hpp
        simulation/motion.cpp
        simulation/motion.hpp
        simulation/force.cpp
        simulation/force.hpp
        simulation/integration.cpp
        simulation/integration.hpp
)

find_package(OpenGL REQUIRED)

target_link_libraries(Nihilo PRIVATE glfw OpenGL::GL glad glm::glm freetype atomic)
