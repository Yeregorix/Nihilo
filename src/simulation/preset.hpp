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

#ifndef NIHILO_PRESET_HPP
#define NIHILO_PRESET_HPP

#include "simulation.hpp"

constexpr size_t SOLAR_SYSTEM_SIZE = 9;

inline float solarSystemRadius(const double original) {
    return static_cast<float>(std::log10(original) - 6.2) * 0.1f;
}

// Mass and radius from https://ssd.jpl.nasa.gov/planets/phys_par.html
const ParticleInfo SOLAR_SYSTEM_INFO[SOLAR_SYSTEM_SIZE] = {
    {1.9884e30, solarSystemRadius(696340e3), glm::vec3(1.0, 1.0, 1.0)}, // Sun
    {0.330103e24, solarSystemRadius(2439.4e3), glm::vec3(0.59, 0.59, 0.59)}, // Mercury
    {4.86731e24, solarSystemRadius(6051.8e3), glm::vec3(0.91, 0.83, 0.63)}, // Venus
    {5.97217e24, solarSystemRadius(6371.0084e3), glm::vec3(0.24, 0.47, 0.87)}, // Earth
    {0.641691e24, solarSystemRadius(3389.5e3), glm::vec3(0.78, 0.39, 0.20)}, // Mars
    {1898.125e24, solarSystemRadius(69911e3), glm::vec3(0.86, 0.71, 0.55)}, // Jupiter
    {568.317e24, solarSystemRadius(58232e3), glm::vec3(0.91, 0.83, 0.67)}, // Saturn
    {86.8099e24, solarSystemRadius(25362e3), glm::vec3(0.63, 0.78, 0.87)}, // Uranus
    {102.4092e24, solarSystemRadius(24622e3), glm::vec3(0.31, 0.47, 0.78)} // Neptune
};

// Generated from https://ssd.jpl.nasa.gov/horizons/
const ParticleState SOLAR_SYSTEM_INITIAL_STATE[SOLAR_SYSTEM_SIZE] = {
    {glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)},
    {glm::dvec3(-45585815911.46662, -49752893385.17383, 116574086.04887502), glm::dvec3(26020.021411254795, -30671.045397682545, -4893.291849179082)},
    {glm::dvec3(50242260908.78682, -96551015762.81287, -4223727867.731408), glm::dvec3(30829.262040791113, 16046.504594131315, -1558.9329126101604)},
    {glm::dvec3(-60700986715.16837, 134051133812.47296, -5721899.591960014), glm::dvec3(-27632.31803322083, -12399.072879769918, 1.3917506576399674)},
    {glm::dvec3(-227385061339.1068, -83412492600.96217, 3832540161.7231045), glm::dvec3(9249.88926289367, -20677.381021143472, -660.2948393711313)},
    {glm::dvec3(-627861285502.643, -515183551270.1503, 16188537956.805893), glm::dvec3(8137.805973281887, -9494.052776514323, -142.67931320428008)},
    {glm::dvec3(17820152385.465843, -1505376005753.9375, 25455934435.90474), glm::dvec3(9137.992038459157, 77.46618911487329, -365.52893444699316)},
    {glm::dvec3(2647332604737.6045, 1361741895770.39, -29221419325.70809), glm::dvec3(-3156.074334667391, 5729.151246953862, 62.4008341366924)},
    {glm::dvec3(4292269953779.307, -1279957446129.29, -72568953377.18726), glm::dvec3(1525.496768751638, 5232.244900811973, -142.97590953353745)}
};

#endif //NIHILO_PRESET_HPP
