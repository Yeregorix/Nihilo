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

#ifndef NIHILO_CAMERA_HPP
#define NIHILO_CAMERA_HPP

#include "glm/glm.hpp"

constexpr float MIN_FOV = 1, MAX_FOV = 80, DEFAULT_FOV = 50;

class Camera {
    public:

    glm::vec3 position;

    Camera();

    [[nodiscard]] float getFOV() const;

    void setFOV(float value);

    void resetFOV();

    void zoom(float delta);

    void move(glm::vec3 delta);

    void resetOrientation();

    void pitch(float angle);

    void yaw(float angle);

    void roll(float angle);

    [[nodiscard]] glm::mat4 getView() const;

    private:

    float _fov;
    glm::vec3 _left, _up, _forward;
};


#endif //NIHILO_CAMERA_HPP