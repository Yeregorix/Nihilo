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

#include <iostream>

#include "simulator.hpp"
#include "integration.hpp"
#include "glm/gtc/random.hpp"
#include "force.hpp"
#include "motion.hpp"

Simulator::Simulator() : _reset(true) {
    std::vector<Particle>& particles = _simulation.particles;
    constexpr std::size_t count = 500;
    particles.reserve(count);

    Particle particle;
    particle.radius = 1.0f;
    particle.mass = 100000000.0f;

    for (unsigned int i = 0; i < count; i++) {
        particles.push_back(particle);
    }
}

void Simulator::reset() {
    _reset = true;
}

void Simulator::update() {
    if (_reset.exchange(false)) {
        _simulation.age = 0;

        std::srand(0);
        for (Particle& particle : _simulation.particles) {
            particle.state[0] = { glm::ballRand(100.0f), glm::sphericalRand(0.1f) };
        }
    } else {
        const auto previousIndex = _simulation.age % 2;
        _simulation.age++;
        const auto nextIndex = _simulation.age % 2;

        for (std::vector<Particle>& particles = _simulation.particles; Particle& p1 : particles) {
            applyEuler(p1.state[previousIndex], p1.state[nextIndex], 1.0f, [p1, particles, previousIndex](const ParticleState& state1) {
                glm::vec3 force(0);
                for (const Particle& p2 : particles) {
                    const ParticleState& state2 = p2.state[previousIndex];
                    force += gravity(p1.mass, p2.mass, state1.position, state2.position, 1.0f);
                }
                return classicAcceleration(force, p1.mass);
            });
        }
    }
}

void Simulator::snapshot(SimulationSnapshot& snapshot) const {
    std::vector<ParticleSnapshot>& particles = snapshot.particles;
    particles.reserve(_simulation.particles.size());

    const auto index = _simulation.age % 2;
    for (const Particle& particle : _simulation.particles) {
        ParticleSnapshot p(particle.state[index].position, particle.radius);
        particles.push_back(p);
    }
}
