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

#ifndef NIHILO_BOX_HPP
#define NIHILO_BOX_HPP

#include "glm/glm.hpp"

template <int N, typename T, glm::qualifier Q>
class Box {
    public:

    glm::vec<N, T, Q> min{}, max{};

    void extend(const Box& other) {
        for (int i = 0; i < N; i++) {
            min[i] = std::min(min[i], other.min[i]);
            max[i] = std::max(max[i], other.max[i]);
        }
    }

    void inflate(const glm::vec<N, T, Q>& vec) {
        min -= vec;
        max += vec;
    }
};

typedef Box<2, float, glm::defaultp> Box2;

#endif //NIHILO_BOX_HPP
