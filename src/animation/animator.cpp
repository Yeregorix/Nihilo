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

#include "animator.hpp"

#include "../manager.hpp"

Animator::Animator(Manager& manager) : simulationSnapshot(), _manager(manager), _controller(_camera), _window(_controller) {
    _window.center();
    Window::clearContext();
    updateControlSnapshot();
}

Animator::~Animator() {
    _window.setContext();
}

void Animator::updateControls() {
    glfwPollEvents();

    _controller.update();
    updateControlSnapshot();

    if (_window.shouldClose()) {
        _manager.stop();
    }
}

void Animator::beforeRender() const {
    _window.setContext();
}

void Animator::updateRender() {
    const std::shared_ptr<SimulationSnapshot> snapshot = simulationSnapshot;
    if (snapshot == nullptr) {
        return;
    }

    const bool changed = snapshot.get() != _lastSimulationSnapshot.lock().get();
    _lastSimulationSnapshot = snapshot;
    _renderer.render(_controlSnapshot, *snapshot, changed);

    _window.update();
}

void Animator::afterRender() {
    Window::clearContext();
}

void Animator::updateControlSnapshot() {
    ControlSnapshot snapshot;
    _window.getSize(snapshot.width, snapshot.height);
    snapshot.fov = _camera.getFOV();
    snapshot.view = _camera.getView();
    _controlSnapshot = snapshot;
}
