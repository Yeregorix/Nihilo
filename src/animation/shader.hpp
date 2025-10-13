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

#ifndef NIHILO_SHADER_HPP
#define NIHILO_SHADER_HPP

#include <string>

#include "glm/glm.hpp"

class Uniform {

    public:

    explicit Uniform(int id);

    void setInt(int value) const;

    void setFloat(float value) const;

    void setVec2(const glm::vec2& vec) const;

    void setVec3(const glm::vec3& vec) const;

    void setVec4(const glm::vec4& vec) const;

    void setMat4(const glm::mat4& mat) const;

    private:

    int _id;
};

class Shader {
    public:

    Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment);

    ~Shader();

    void use() const;

    [[nodiscard]] Uniform uniform(const std::string& name) const;

    private:

    unsigned int _id;
};


#endif //NIHILO_SHADER_HPP