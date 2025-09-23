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

#ifndef NIHILO_CONTROLLER_HPP
#define NIHILO_CONTROLLER_HPP

#include <optional>

#include "camera.hpp"

class Controller {
    public:

    explicit Controller(Camera& camera);

    void keyPressed(int key, char ch);

    void keyReleased(int key, char ch);

    void mouseReleased();

    void mouseDragged(glm::vec2 pos);

    void scrolled(double value) const;

    void update();

    private:

    [[nodiscard]] float getZoomFactor() const;

    Camera& _camera;
    bool _zoomIn{}, _zoomOut{}, _left{}, _right{}, _forward{}, _backward{}, _up{}, _down{}, _speedUp{}, _slowDown{};
    float _speed = 1;
    bool _mouseDragging;
    glm::vec2 _previousMousePosition;
};

#endif //NIHILO_CONTROLLER_HPP