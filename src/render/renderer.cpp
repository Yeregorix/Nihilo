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

#include "renderer.hpp"

#include <iostream>

#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

// language=glsl
const std::string particleVertex = R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in float radius;

flat out float geomRadius;

void main() {
    gl_Position = vec4(position, 1);
    geomRadius = radius;
}
)";

// language=glsl
const std::string particleGeometry = R"(
#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

flat in float[] geomRadius;

flat out float radius2;
out vec2 offset;

uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 pos = view * gl_in[0].gl_Position;
    float radius = geomRadius[0];
    radius2 = radius * radius;
    offset = vec2(-radius, -radius);
    gl_Position = projection * (pos + vec4(offset, 0, 0));
    EmitVertex();
    offset = vec2(radius, -radius);
    gl_Position = projection * (pos + vec4(offset, 0, 0));
    EmitVertex();
    offset = vec2(-radius, radius);
    gl_Position = projection * (pos + vec4(offset, 0, 0));
    EmitVertex();
    offset = vec2(radius, radius);
    gl_Position = projection * (pos + vec4(offset, 0, 0));
    EmitVertex();
    EndPrimitive();
}
)";

// language=glsl
const std::string particleFragment = R"(
#version 330 core

flat in float radius2;
in vec2 offset;

out vec4 color;

void main() {
    float offset2 = dot(offset, offset);
    if (offset2 > radius2) {
        discard;
    }
    color = vec4(1, 1, 1, 1);
}
)";

Renderer::Renderer() :
_shader(particleVertex, particleGeometry, particleFragment),
_view(_shader.uniform("view")), _projection(_shader.uniform("projection")),
_font("SpaceMono-Regular.ttf") {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _attributes.use();
    _buffer.use();
    VertexAttributes::setFloat(0, 3, sizeof(ParticleSnapshot), offsetof(ParticleSnapshot, position));
    VertexAttributes::setFloat(1, 1, sizeof(ParticleSnapshot), offsetof(ParticleSnapshot, radius));
    VertexBuffer::clearUse();
    VertexAttributes::clearUse();

    _rectangle.setColor(glm::vec4(0.2, 0.2, 0.2, 0.9));
    _font.setColor(glm::vec3(0.5, 0.8, 0.2));
}

void Renderer::render(const ControlSnapshot& control, const SimulationSnapshot& simulation, const bool simulationChanged) {
    if (simulationChanged) {
        _buffer.use();
        VertexBuffer::setData(simulation.particles, GL_DYNAMIC_DRAW);
        VertexBuffer::clearUse();
    }

    glViewport(0, 0, control.width, control.height);
    glClearColor(0, 0, 0, 1.0f);
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float aspect = static_cast<float>(control.width) / static_cast<float>(control.height);
    const auto projection = glm::perspective(glm::radians(control.fov), aspect, 0.01f, 10000.0f);

    _shader.use();
    _view.setMat4(control.view);
    _projection.setMat4(projection);

    _attributes.use();
    VertexAttributes::draw(GL_POINTS, simulation.particles.size());
    VertexAttributes::clearUse();

    glDepthMask(GL_FALSE);

    const std::string text = "Lorem ipsum dolor sit amet";
    const glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.05, 0.05 * aspect, 0));
    const glm::mat4 transformation = glm::translate(scale, glm::vec3(0));

    Box2 box = _font.setText(text);
    box.inflate(glm::vec2(0.5));
    _rectangle.setBox(box);

    _rectangle.render(transformation);
    _font.render(transformation);
}
