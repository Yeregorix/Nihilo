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

#ifndef NIHILO_INTEGRATION_HPP
#define NIHILO_INTEGRATION_HPP

#include <functional>

#include "simulation.hpp"

/**
 * Computes the acceleration to apply to a given particle.
 */
typedef std::function<glm::vec3(const ParticleState&)> Accelerator;

/**
 * Computes the next state of the given particle using the Euler method.
 *
 * This method is compatible with any acceleration formula but lack accuracy.
 *
 * @param current The current state of the particle.
 * @param next The next state of the particle.
 * @param timeStep The time step.
 * @param accelerator The accelerator.
 */
void applyEuler(const ParticleState& current, ParticleState& next, float timeStep, const Accelerator& accelerator);

/**
 * Computes the next state of the given particle using the Runge-Kutta 4 method.
 *
 * This method is compatible with any acceleration formula but is more expensive.
 *
 * @param current The current state of the particle.
 * @param next The next state of the particle.
 * @param timeStep The time step.
 * @param accelerator The accelerator.
 */
void applyRungeKutta4(const ParticleState& current, ParticleState& next, float timeStep, const Accelerator& accelerator);

/**
 * Computes the next state of the given particle using the Verlet method.
 *
 * This method is fast and accurate but is only compatible with acceleration formula independent of speed.
 * Consequently, it is incompatible with the relativist acceleration.
 *
 * @param current The current state of the particle.
 * @param next The next state of the particle.
 * @param timeStep The time step.
 * @param accelerator The accelerator.
 */
void applyVerlet(const ParticleState& current, ParticleState& next, float timeStep, const Accelerator& accelerator);

#endif //NIHILO_INTEGRATION_HPP
