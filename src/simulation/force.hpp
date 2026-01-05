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

#ifndef NIHILO_FORCE_HPP
#define NIHILO_FORCE_HPP

#include "glm/glm.hpp"

/**
 * Computes the gravitational force exerted by particle 2 on particle 1.
 *
 * The softening parameter prevents the force from going to infinity when particles are too close.
 * See <a href="https://en.wikipedia.org/wiki/N-body_simulation#Softening">Wikipedia</a>.
 *
 * @param mass1 Mass of particle 1
 * @param mass2 Mass of particle 2
 * @param position1 Position of particle 1
 * @param position2 Position of particle 2
 * @param softSq Squared value of the softening parameter
 * @return The force received by particle 1
 */
glm::dvec3 gravity(double mass1, double mass2, const glm::dvec3& position1, const glm::dvec3& position2, double softSq);

#endif //NIHILO_FORCE_HPP
