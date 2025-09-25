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

#ifndef NIHILO_ANIMATOR_HPP
#define NIHILO_ANIMATOR_HPP

#include <atomic>
#include <memory>

#include "camera.hpp"
#include "controller.hpp"
#include "window.hpp"
#include "renderer.hpp"

class Manager;

class Animator {
    public:

    std::atomic<std::shared_ptr<SimulationSnapshot>> simulationSnapshot;

    explicit Animator(Manager& manager);

    ~Animator();

    void updateControls();

    void beforeRender() const;

    void updateRender();

    static void afterRender();

    private:

    void updateControlSnapshot();

    Manager& _manager;
    Camera _camera;
    Controller _controller;
    Window _window;
    Renderer _renderer;
    std::atomic<ControlSnapshot> _cameraSnapshot;
    std::weak_ptr<SimulationSnapshot> _lastSimulationSnapshot;
};


#endif //NIHILO_ANIMATOR_HPP