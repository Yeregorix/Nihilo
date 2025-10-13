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

#ifndef NIHILO_FONT_HPP
#define NIHILO_FONT_HPP

#include <string>

#include "shader.hpp"
#include "vertex.hpp"
#include "glm/glm.hpp"
#include "../box.hpp"

struct Character {
    glm::vec2 size;
    glm::vec2 bearing;
    float advance;
};

class Font {

    public:

    explicit Font(const std::string& fontPath);

    ~Font();

    [[nodiscard]] Box2 box(const std::string& text) const;

    void render(const std::string& text, const glm::mat4& transformation, const glm::vec3& color) const;

    private:

    Shader _shader;
    Uniform _transformation, _color;
    VertexAttributes _attributes;
    VertexBuffer _buffer;
    unsigned int _textureId{};
    Character _chars[128]{};
};


#endif //NIHILO_FONT_HPP