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

#include <glad.h>

#include "window.hpp"

#include <iostream>

#include "glm/vec2.hpp"

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(800, 600, "Nihilo", nullptr, nullptr);
    if (_window == nullptr) {
        throw std::runtime_error("Failed to create window");
    }

    setContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, const int width, const int height) {
        if (const auto _this = static_cast<Window*>(glfwGetWindowUserPointer(window))) {
            _this->_size = glm::uvec2(width, height);
        }
    });

    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    _size = glm::uvec2(width, height);
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

glm::uvec2 Window::size() const {
    return _size;
}

bool Window::isKeyPressed(const int key) const {
    return glfwGetKey(_window, key) == GLFW_PRESS;
}
