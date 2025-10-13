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

#include "camera.hpp"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera() : position(0), _fov(DEFAULT_FOV), _left(-1, 0, 0), _up(0, 1, 0), _forward(0, 0, 1) {
}

float Camera::getFOV() const {
    return _fov;
}

void Camera::setFOV(const float value) {
    _fov = std::clamp(value, MIN_FOV, MAX_FOV);
}

void Camera::resetFOV() {
    _fov = DEFAULT_FOV;
}

void Camera::zoom(const float delta) {
    setFOV(_fov + delta);
}

void Camera::move(const glm::vec3 delta) {
    position.x += _left.x * delta.x + _up.x * delta.y + _forward.x * delta.z;
    position.y += _left.y * delta.x + _up.y * delta.y + _forward.y * delta.z;
    position.z += _left.z * delta.x + _up.z * delta.y + _forward.z * delta.z;
}

void Camera::resetOrientation() {
    _left = glm::vec3(-1, 0, 0);
    _up = glm::vec3(0, 1, 0);
    _forward = glm::vec3(0, 0, 1);
}

void Camera::pitch(const float angle) {
    _up = glm::normalize(glm::rotate(_up, angle, _left));
    _forward = glm::normalize(glm::rotate(_forward, angle, _left));
}

void Camera::yaw(const float angle) {
    _left = glm::normalize(glm::rotate(_left, angle, _up));
    _forward = glm::normalize(glm::rotate(_forward, angle, _up));
}

void Camera::roll(const float angle) {
    _left = glm::normalize(glm::rotate(_left, angle, _forward));
    _up = glm::normalize(glm::rotate(_up, angle, _forward));
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, position + _forward, _up);
}

