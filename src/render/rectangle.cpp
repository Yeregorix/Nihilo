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

#include "rectangle.hpp"

#include "glad.h"

// language=glsl
const std::string rectangleVertex = R"(
#version 330 core

layout (location = 0) in vec2 position;

void main() {
    gl_Position = vec4(position, 0, 1);
}
)";

// language=glsl
const std::string rectangleGeometry = R"(
#version 330 core

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 transformation;

void main() {
    vec4 minPos = gl_in[0].gl_Position;
    vec4 maxPos = gl_in[1].gl_Position;
    gl_Position = transformation * vec4(minPos.x, maxPos.y, 0, 1);
    EmitVertex();
    gl_Position = transformation * minPos;
    EmitVertex();
    gl_Position = transformation * maxPos;
    EmitVertex();
    gl_Position = transformation * vec4(maxPos.x, minPos.y, 0, 1);
    EmitVertex();
    EndPrimitive();
}
)";

// language=glsl
const std::string rectangleFragment = R"(
#version 330 core

out vec4 outColor;
uniform vec4 color;

void main() {
    outColor = color;
}
)";

Rectangle::Rectangle() :
_shader(rectangleVertex, rectangleGeometry, rectangleFragment),
_transformation(_shader.uniform("transformation")), _color(_shader.uniform("color")) {
    _attributes.use();
    _buffer.use();
    VertexAttributes::setFloat(0, 2, sizeof(glm::vec2), 0);
    VertexBuffer::clearUse();
    VertexAttributes::clearUse();
}

void Rectangle::setBox(const Box2& box) const {
    _buffer.use();
    VertexBuffer::setData(sizeof(Box2), &box, GL_DYNAMIC_DRAW);
    VertexBuffer::clearUse();
}

void Rectangle::setColor(const glm::vec4& color) const {
    _shader.use();
    _color.setVec4(color);
}

void Rectangle::render(const glm::mat4& transformation) const {
    _shader.use();
    _transformation.setMat4(transformation);

    _attributes.use();
    VertexAttributes::draw(GL_LINES, 2);
    VertexAttributes::clearUse();
}
