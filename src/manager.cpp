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

#include "manager.hpp"

#include <thread>

Manager::Manager() :
_window(_controller),
_controlLoop([this] { updateControls(); }),
_simulationLoop([this] { updateSimulation(); }),
_renderLoop([this] { updateRender(); }),
_controlSnapshot(),
_simulationSnapshot() {
    _window.center();
    Window::clearContext(); // we will transfer gl context to the render thread

    _controlLoop.setTargetFrequency(60);
    _renderLoop.setTargetFrequency(60);
    _simulationLoop.setTargetFrequency(30);
}

Manager::~Manager() {
    _window.setContext(); // take back the gl context from the render thread
}

void Manager::run() {
    std::thread renderThread([this] {
        _window.setContext();
        _renderLoop.run();
        Window::clearContext();
    });
    std::thread simulationThread([this] {
        _simulationLoop.run();
    });

    _controlLoop.run();

    simulationThread.join();
    renderThread.join();
}

void Manager::stop() {
    _controlLoop.stop();
    _renderLoop.stop();
    _simulationLoop.stop();
}

void Manager::updateControls() {
    glfwPollEvents();

    _controller.update();

    const auto snapshot = std::make_shared<ControlSnapshot>();
    _controller.snapshot(*snapshot);
    _window.getSize(snapshot->width, snapshot->height);
    _controlSnapshot = snapshot;

    if (_window.shouldClose()) {
        stop();
    }
}

void Manager::updateSimulation() {
    _simulator.update();

    const auto snapshot = std::make_shared<SimulationSnapshot>();
    _simulator.snapshot(*snapshot);
    _simulationSnapshot = snapshot;
}

void Manager::updateRender() {
    const std::shared_ptr<SimulationSnapshot> simulationSnapshot = _simulationSnapshot;
    if (simulationSnapshot == nullptr) {
        return;
    }

    const std::shared_ptr<ControlSnapshot> controlSnapshot = _controlSnapshot;
    if (controlSnapshot == nullptr) {
        return;
    }

    const bool changed = simulationSnapshot.get() != _lastSimulationSnapshot.lock().get();
    _lastSimulationSnapshot = simulationSnapshot;
    _renderer.render(*controlSnapshot, *simulationSnapshot, changed);

    _window.update();
}
