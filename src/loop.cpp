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

#include "loop.hpp"

#include <chrono>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <thread>

Loop::Loop(const std::function<void()>& function) : _function(function) {
}

void Loop::run() {
    if (_running.exchange(true)) {
        throw std::runtime_error("Loop already running");
    }

    auto startTime = std::chrono::steady_clock::now();

    while (_running) {
        try {
            _function();
        } catch (const std::exception& e) {
            std::cout << "Loop exception: " << e.what() << std::endl;
        }

        auto endTime = std::chrono::steady_clock::now();
        _currentPeriod = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

        if (const auto targetEndTime = startTime + std::chrono::nanoseconds(_targetPeriod); endTime < targetEndTime) {
            std::this_thread::sleep_until(targetEndTime);
            startTime = targetEndTime;
        } else {
            startTime = endTime;
        }
    }
}

void Loop::stop() {
    _running = false;
}

bool Loop::isRunning() const {
    return _running;
}

void Loop::setTargetFrequency(const double frequency) {
    if (frequency <= 0) {
        throw std::domain_error("Frequency must be greater than zero");
    }
    setTargetPeriod(ONE_SECOND / frequency);
}

void Loop::setTargetPeriod(const unsigned int period) {
    _targetPeriod = period;
}

double Loop::getTargetFrequency() const {
    return ONE_SECOND / _targetPeriod;
}

unsigned int Loop::getTargetPeriod() const {
    return _targetPeriod;
}

void Loop::getTiming(LoopTiming& timing) const {
    timing.currentPeriod = _currentPeriod;
    timing.targetPeriod = _targetPeriod;
}
