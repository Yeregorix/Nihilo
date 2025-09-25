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

out float geomRadius;

uniform mat4 view;
uniform mat4 projection;

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

in float[] geomRadius;

out float radius2;
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

in float radius2;
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

Renderer::Renderer() : _particleShader(particleVertex, particleGeometry, particleFragment), _vao{}, _vbo{} {
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleSnapshot), reinterpret_cast<void *>(offsetof(ParticleSnapshot, position)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleSnapshot), reinterpret_cast<void *>(offsetof(ParticleSnapshot, radius)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}

void Renderer::render(const ControlSnapshot& control, const SimulationSnapshot& simulation, const bool simulationChanged) const {
    if (simulationChanged) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleSnapshot) * simulation.particles.size(), &simulation.particles[0], GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glViewport(0, 0, control.width, control.height);
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const auto projection = glm::perspective(glm::radians(control.fov), static_cast<float>(control.width) / static_cast<float>(control.height), 0.01f, 10000.0f);

    _particleShader.use();
    _particleShader.setMat4("view", control.view);
    _particleShader.setMat4("projection", projection);

    glBindVertexArray(_vao);
    glDrawArrays(GL_POINTS, 0, simulation.particles.size());
}
