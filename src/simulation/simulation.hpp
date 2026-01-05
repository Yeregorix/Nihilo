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

#ifndef NIHILO_SIMULATION_HPP
#define NIHILO_SIMULATION_HPP

#include <vector>
#include "glm/glm.hpp"

struct ParticleSnapshot {
    glm::vec3 position;
    float radius;
};

/**
 * Shared data between simulation and render threads.
 */
struct SimulationSnapshot {
    std::vector<ParticleSnapshot> particles;
};

struct ParticleInfo {
    float mass;
    float radius;
};

struct ParticleState {
    glm::vec3 position;
    glm::vec3 acceleration;
    glm::vec3 speed;
};

struct Particle : ParticleInfo {
    ParticleState state[2];
};

struct Simulation {
    unsigned long long age;
    std::vector<Particle> particles;
};

#endif //NIHILO_SIMULATION_HPP
