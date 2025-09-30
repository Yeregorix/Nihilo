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

#include "force.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"

// gravitational constant in SI unit
constexpr float G = 6.67430e-11f;

glm::vec3 gravity(const float mass1, const float mass2, const glm::vec3& position1, const glm::vec3& position2, const float softSq) {
    const glm::vec3 delta = position2 - position1;
    const float length2 = glm::length2(delta);
    if (length2 < glm::epsilon<float>()) {
        return glm::vec3(0, 0, 0);
    }
    return delta * (G * mass1 * mass2 / ((length2 + softSq) * std::sqrt(length2)));
}
