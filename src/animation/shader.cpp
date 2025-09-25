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

#include <glad.h>

#include "shader.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

unsigned int compileShader(const unsigned int type, const std::string& source) {
    const auto chars = source.c_str();
    const unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &chars, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[27 + 512] = "Shader compilation failed.\n";
        glGetShaderInfoLog(id, 512, nullptr, infoLog + 27);
        throw std::runtime_error(infoLog);
    }

    return id;
}

Shader::Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment) {
    std::vector<unsigned int> shaders;
    shaders.push_back(compileShader(GL_VERTEX_SHADER, vertex));
    if (!geometry.empty()) {
        shaders.push_back(compileShader(GL_GEOMETRY_SHADER, geometry));
    }
    shaders.push_back(compileShader(GL_FRAGMENT_SHADER, fragment));

    _id = glCreateProgram();
    for (const unsigned int shader : shaders) {
        glAttachShader(_id, shader);
    }
    glLinkProgram(_id);

    for (const unsigned int shader : shaders) {
        glDeleteShader(shader);
    }

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[31 + 512] = "Shader program linking failed.\n";
        glGetProgramInfoLog(_id, 512, nullptr, infoLog + 31);
        throw std::runtime_error(infoLog);
    }
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

void Shader::use() const {
    glUseProgram(_id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
