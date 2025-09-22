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
        file_util.cpp
        file_util.hpp)

find_package(OpenGL REQUIRED)

target_link_libraries(Nihilo glfw OpenGL::GL glad glm::glm)

add_custom_target(shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_dependencies(Nihilo shaders)
