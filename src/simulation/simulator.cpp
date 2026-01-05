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

#include "simulator.hpp"

#include "integration.hpp"
#include "force.hpp"
#include "motion.hpp"
#include "preset.hpp"

Simulator::Simulator() : _reset(true) {
    std::vector<Particle>& particles = _simulation.particles;
    particles.reserve(SOLAR_SYSTEM_SIZE);
    for (const ParticleInfo& particle : SOLAR_SYSTEM_INFO) {
        particles.push_back(Particle(particle));
    }
}

void Simulator::reset() {
    _reset = true;
}

void Simulator::update() {
    if (_reset.exchange(false)) {
        _simulation.age = 0;

        std::vector<Particle>& particles = _simulation.particles;
        for (int i = 0; i < SOLAR_SYSTEM_SIZE; i++) {
            particles[i].state[0] = SOLAR_SYSTEM_INITIAL_STATE[i];
        }
    } else {
        const auto previousIndex = _simulation.age % 2;
        _simulation.age++;
        const auto nextIndex = _simulation.age % 2;

        for (std::vector<Particle>& particles = _simulation.particles; Particle& p1 : particles) {
            applyVerlet(p1.state[previousIndex], p1.state[nextIndex], 3600.0 * 24, [p1, particles, previousIndex](const ParticleState& state1) {
                glm::dvec3 force(0);
                for (const Particle& p2 : particles) {
                    const ParticleState& state2 = p2.state[previousIndex];
                    force += gravity(p1.mass, p2.mass, state1.position, state2.position, 1.0);
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
        ParticleSnapshot p(particle.state[index].position / POSITION_SCALE, particle.radius);
        particles.push_back(p);
    }
}
