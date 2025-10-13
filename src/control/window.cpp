/*
 * Copyright (c) 2025 Hugo Dupanloup (Yeregorix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdexcept>
#include <iostream>

#include "glad.h"
#include "window.hpp"

#include <cstring>

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

inline Window* getWindow(GLFWwindow* glfwWindow) {
    return static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
}

Window::Window(Controller &controller) : _controller(controller) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    _window = glfwCreateWindow(800, 600, "Nihilo", nullptr, nullptr);
    if (_window == nullptr) {
        throw std::runtime_error("Failed to create window");
    }

    setContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetKeyCallback(_window, [](GLFWwindow* window, const int key, const int scanCode, const int action, int) {
        if (const Window* _this = getWindow(window)) {
            const char* name = glfwGetKeyName(key, scanCode);
            const char ch = name == nullptr || std::strlen(name) != 1 ? '\0' : *name;
            switch (action) {
                case GLFW_PRESS:
                    _this->_controller.keyPressed(key, ch);
                    break;
                case GLFW_RELEASE:
                    _this->_controller.keyReleased(key, ch);
                    break;
                default:
                    break;
            }
        }
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, const int button, const int action, int) {
        if (const Window* _this = getWindow(window)) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                _this->_controller.mouseReleased();
            }
        }
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, const double x, const double y) {
        if (const Window* _this = getWindow(window)) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                _this->_controller.mouseDragged(glm::vec2(x, y));
            }
        }
    });

    glfwSetScrollCallback(_window, [](GLFWwindow* window, double, const double dy) {
        if (const Window* _this = getWindow(window)) {
            if (std::abs(dy) > glm::epsilon<double>()) {
                _this->_controller.scrolled(dy);
            }
        }
    });
}

Window::~Window() {
    glfwDestroyWindow(_window);
    _window = nullptr;
}

void Window::center() const {
    int sizeX = 0, sizeY = 0;
    glfwGetWindowSize(_window, &sizeX, &sizeY);

    int posX = 0, posY = 0;
    glfwGetWindowPos(_window, &posX, &posY);

    int monitor_count = 0;
    GLFWmonitor** m = glfwGetMonitors(&monitor_count);
    if (!m) {
        return;
    }

    int monitorX = 0, monitorY = 0;
    int maxArea = 0;
    int targetX = 0, targetY = 0;
    for (int j = 0; j < monitor_count ; ++j) {
        glfwGetMonitorPos(m[j], &monitorX, &monitorY);
        const GLFWvidmode* mode = glfwGetVideoMode(m[j]);
        if (!mode) {
            continue;
        }

        const int minX = std::max(monitorX, posX);
        const int minY = std::max(monitorY, posY);

        const int maxX = std::min(monitorX + mode->width, posX + sizeX);
        const int maxY = std::min(monitorY + mode->height, posY + sizeY);

        if (const int area = std::max(maxX - minX, 0) * std::max(maxY - minY, 0); area > maxArea) {
            targetX = monitorX + (mode->width - sizeX) / 2;
            targetY = monitorY + (mode->height - sizeY) / 2;
            maxArea = area;
        }
    }

    if (maxArea) {
        glfwSetWindowPos(_window, targetX, targetY);
        return;
    }

    if (GLFWmonitor* primary = glfwGetPrimaryMonitor()) {
        if (const GLFWvidmode* desktop = glfwGetVideoMode(primary)) {
            glfwSetWindowPos(_window, (desktop->width - sizeX) / 2, (desktop->height - sizeY) / 2);
        }
    }
}

void Window::setContext() const {
    glfwMakeContextCurrent(_window);
}

void Window::clearContext() {
    glfwMakeContextCurrent(nullptr);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(_window);
}

void Window::update() const {
    glfwSwapBuffers(_window);
}

void Window::getSize(int& width, int& height) const {
    glfwGetFramebufferSize(_window, &width, &height);
}
