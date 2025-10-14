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

#ifndef NIHILO_RENDERER_HPP
#define NIHILO_RENDERER_HPP

#include "../timing.hpp"
#include "../control/control.hpp"
#include "../simulation/simulation.hpp"
#include "font.hpp"
#include "rectangle.hpp"
#include "shader.hpp"
#include "vertex.hpp"

class Renderer {
    public:

    Renderer();

    void render(const ControlSnapshot& control, const SimulationSnapshot& simulation, bool simulationChanged, const ManagerTiming& timing);

    private:

    Shader _shader;
    Uniform _view, _projection;
    VertexAttributes _attributes;
    VertexBuffer _buffer;
    Rectangle _rectangle;
    Font _font;
};

#endif //NIHILO_RENDERER_HPP
