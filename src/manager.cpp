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
_animator(*this),
_controlLoop([this] { _animator.updateControls(); }),
_renderLoop([this] { _animator.updateRender(); }),
_simulationLoop([this] {
    _simulator.update();
    _animator.simulationSnapshot = _simulator.snapshot();
}) {
    _controlLoop.setTargetFrequency(60);
    _renderLoop.setTargetFrequency(60);
    _simulationLoop.setTargetFrequency(30);
}

void Manager::run() {
    std::thread renderThread([this] {
        _animator.beforeRender();
        _renderLoop.run();
        Animator::afterRender();
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
