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

#include <stdexcept>

#include "../file_util.hpp"

const std::string shadersDir = "shaders/";

Shader::Shader(const std::string& name) {
    std::string shaderString = read_file(shadersDir + name + ".vert");
    auto source = shaderString.c_str();
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[34 + 512] = "Vertex shader compilation failed.\n";
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog + 34);
        throw std::runtime_error(infoLog);
    }

    shaderString = read_file(shadersDir + name + ".frag");
    source = shaderString.c_str();
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[36 + 512] = "Fragment shader compilation failed.\n";
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog + 36);
        throw std::runtime_error(infoLog);
    }

    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[31 + 512] = "Shader program linking failed.\n";
        glGetProgramInfoLog(_id, 512, nullptr, infoLog + 31);
        throw std::runtime_error(infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(_id);
    _id = 0;
}

void Shader::use() const {
    glUseProgram(_id);
}
