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

#include "controller.hpp"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>

#include "glm/gtx/norm.hpp"

Controller::Controller(Camera &camera) : _camera(camera), _mouseDragging(false), _previousMousePosition(0) {
}

void Controller::keyPressed(const int key, const char ch) {
    switch (key) {
        case GLFW_KEY_KP_1:
            _camera.resetFOV();
            break;
        case GLFW_KEY_KP_2:
            _camera.position = glm::vec3(0);
            break;
        case GLFW_KEY_KP_3:
            _camera.resetOrientation();
            break;
        case GLFW_KEY_KP_4:
            _speed = 1;
            break;
        case GLFW_KEY_UP:
            _zoomIn = true;
            break;
        case GLFW_KEY_DOWN:
            _zoomOut = true;
            break;
        case GLFW_KEY_RIGHT:
            _speedUp = true;
            break;
        case GLFW_KEY_LEFT:
            _slowDown = true;
            break;
        case GLFW_KEY_SPACE:
            _up = true;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            _down = true;
            break;
        default:
            switch (ch) {
                case 'c':
                    _right = true;
                    break;
                case 'w':
                    _left = true;
                    break;
                case 'd':
                    _forward = true;
                    break;
                case 'x':
                    _backward = true;
                    break;
                default:
                    break;
            }
            break;
    }
}

void Controller::keyReleased(const int key, const char ch) {
    switch (key) {
        case GLFW_KEY_UP:
            _zoomIn = false;
            break;
        case GLFW_KEY_DOWN:
            _zoomOut = false;
            break;
        case GLFW_KEY_RIGHT:
            _speedUp = false;
            break;
        case GLFW_KEY_LEFT:
            _slowDown = false;
            break;
        case GLFW_KEY_SPACE:
            _up = false;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            _down = false;
            break;
        default:
            switch (ch) {
                case 'c':
                    _right = false;
                    break;
                case 'w':
                    _left = false;
                    break;
                case 'd':
                    _forward = false;
                    break;
                case 'x':
                    _backward = false;
                    break;
                default:
                    break;
            }
            break;
    }
}

void Controller::mouseReleased() {
    _mouseDragging = false;
}

void Controller::mouseDragged(const glm::vec2 pos) {
    if (!_mouseDragging) {
        _previousMousePosition = pos;
        _mouseDragging = true;
        return;
    }

    const glm::vec2 delta = pos - _previousMousePosition;
    _previousMousePosition = pos;

    if (glm::length2(delta) > 1000) {
        return;
    }

    _camera.pitch(delta.y * -0.005f * getZoomFactor());
    _camera.yaw(delta.x * -0.005f * getZoomFactor());
}

void Controller::scrolled(const double value) const {
    _camera.roll(value * -0.05f);
}

void Controller::update() {
    float zoom = 0;
    if (_zoomIn) {
        zoom--;
    }
    if (_zoomOut) {
        zoom++;
    }

    if (zoom != 0) {
        _camera.zoom(zoom);
    }

    if (_speedUp) {
        _speed += 0.1f;
    }
    if (_slowDown) {
        _speed -= 0.1f;
    }

    if (_speed > 10) {
        _speed = 10;
    } else if (_speed < 0.1f) {
        _speed = 0.1f;
    }

    glm::vec3 delta(0, 0, 0);
    if (_right) {
        delta.x++;
    }
    if (_left) {
        delta.x--;
    }
    if (_forward) {
        delta.z++;
    }
    if (_backward) {
        delta.z--;
    }
    if (_up) {
        delta.y++;
    }
    if (_down) {
        delta.y--;
    }

    if (const float l = glm::length2(delta); l > glm::epsilon<float>()) {
        const float f = 0.4f * getZoomFactor() * _speed;
        _camera.move(delta * f);
    }
}

float Controller::getZoomFactor() const {
    return _camera.getFOV() / DEFAULT_FOV;
}
