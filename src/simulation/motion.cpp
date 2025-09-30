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

#include "motion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"

// speed of light in vacuum in m/s
constexpr float C = 299792458.0;
constexpr float C2 = C * C;

glm::vec3 classicAcceleration(const glm::vec3& force, const float mass) {
    return force / mass;
}

glm::vec3 relativistAcceleration(const glm::vec3& force, const float mass, const glm::vec3& speed) {
    const float lorentz = 1.0f / std::sqrt(1.0f - glm::length2(speed) / C2);
    return (force - (glm::cross(force, speed) * speed / C2)) / (mass * lorentz);
}
