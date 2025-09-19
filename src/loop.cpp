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

#define NANOS_PER_SECOND 1E9

Loop::Loop(const std::function<void()>& function) : _function(function) {
}

void Loop::run() {
    if (_running.exchange(true)) {
        throw std::runtime_error("Loop already running");
    }

    auto t = std::chrono::steady_clock::now();

    while (_running) {
        try {
            _function();
        } catch (const std::exception& e) {
            std::cout << "Loop exception: " << e.what() << std::endl;
        }

        auto t2 = std::chrono::steady_clock::now();

        const unsigned int duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t).count();
        _currentPeriod = duration;
        if (const unsigned int target = _targetPeriod; duration < target) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(target - duration));
        }

        t = t2;
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
    setTargetPeriod(NANOS_PER_SECOND / frequency);
}

void Loop::setTargetPeriod(const unsigned int period) {
    _targetPeriod = period;
}

double Loop::getTargetFrequency() const {
    return NANOS_PER_SECOND / getTargetPeriod();
}

unsigned int Loop::getTargetPeriod() const {
    return _targetPeriod;
}

double Loop::getCurrentFrequency() const {
    return NANOS_PER_SECOND / getCurrentPeriod();
}

unsigned int Loop::getCurrentPeriod() const {
    return std::max<unsigned int>(_currentPeriod, _targetPeriod);
}
