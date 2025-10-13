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

#ifndef NIHILO_MANAGER_HPP
#define NIHILO_MANAGER_HPP

#include "loop.hpp"
#include "control/controller.hpp"
#include "control/window.hpp"
#include "render/renderer.hpp"
#include "simulation/simulator.hpp"

class Manager {
    public:

    Manager();

    ~Manager();

    void run();

    void stop();

    private:

    void updateControls();

    void updateSimulation();

    void updateRender();

    Controller _controller;
    Window _window;
    Renderer _renderer;
    Simulator _simulator;

    Loop _controlLoop, _simulationLoop, _renderLoop;

    std::atomic<std::shared_ptr<ControlSnapshot>> _controlSnapshot;
    std::atomic<std::shared_ptr<SimulationSnapshot>> _simulationSnapshot;
    std::weak_ptr<SimulationSnapshot> _lastSimulationSnapshot;
};


#endif //NIHILO_MANAGER_HPP