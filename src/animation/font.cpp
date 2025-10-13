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

#include "font.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

#include "freetype/freetype.h"
#include "glad.h"
#include <glm/gtc/matrix_transform.hpp>

// language=glsl
const std::string textVertex = R"(
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in int character;

flat out int geomChar;

void main() {
    gl_Position = vec4(position, 0, 1);
    geomChar = character;
}
)";

// language=glsl
const std::string textGeometry = R"(
#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

flat in int[] geomChar;

flat out int character;
out vec2 texturePos;

uniform mat4 transformation;

void main() {
    vec2 pos = gl_in[0].gl_Position.xy;
    character = geomChar[0];
    texturePos = vec2(0, 1);
    gl_Position = transformation * vec4(pos + texturePos, 0, 1);
    EmitVertex();
    texturePos = vec2(0, 0);
    gl_Position = transformation * vec4(pos + texturePos, 0, 1);
    EmitVertex();
    texturePos = vec2(1, 1);
    gl_Position = transformation * vec4(pos + texturePos, 0, 1);
    EmitVertex();
    texturePos = vec2(1, 0);
    gl_Position = transformation * vec4(pos + texturePos, 0, 1);
    EmitVertex();
    EndPrimitive();
}
)";

// language=glsl
const std::string textFragment = R"(
#version 330 core

flat in int character;
in vec2 texturePos;

out vec4 outColor;

uniform sampler2DArray textureArray;
uniform vec3 color;

void main() {
    float a = texture(textureArray, vec3(texturePos.x, 1 - texturePos.y, character)).r;
    if (a == 0) {
        discard;
    }
    outColor = vec4(color, a);
}
)";

struct Glyph {
    glm::vec2 position;
    unsigned char character;
};

constexpr unsigned int glyphSize = 256;

Font::Font(const std::string& fontPath) :
_shader(textVertex, textGeometry, textFragment),
_transformation(_shader.uniform("transformation")), _color(_shader.uniform("color")),
_glyphs()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Failed to initialize FreeType");
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        throw std::runtime_error("Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, glyphSize, glyphSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &_textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _textureId);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_R8, glyphSize, glyphSize, 128, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            throw std::runtime_error("Failed to load character");
        }

        const auto glyph = face->glyph;

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, static_cast<int>(c), static_cast<int>(glyph->bitmap.width), static_cast<int>(glyph->bitmap.rows), 1, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        _chars[c] = {
            glm::vec2(glyph->bitmap.width, glyph->bitmap.rows) / static_cast<float>(glyphSize),
            glm::vec2(glyph->bitmap_left, glyph->bitmap_top) / static_cast<float>(glyphSize),
            static_cast<float>(glyph->advance.x) / static_cast<float>(glyphSize * 64)
        };
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    _attributes.use();
    _buffer.use();
    VertexAttributes::setFloat(0, 2, sizeof(Glyph), offsetof(Glyph, position));
    VertexAttributes::setByte(1, 1, sizeof(Glyph), offsetof(Glyph, character));
    VertexBuffer::clearUse();
    VertexAttributes::clearUse();
}

Font::~Font() {
    glDeleteTextures(1, &_textureId);
}

Box2 Font::setText(const std::string& text) {
    float x = 0, y = 0;
    Box2 textBox;

    std::vector<Glyph> glyphs;
    glyphs.reserve(text.length());

    for (unsigned char c : text) {
        if (c >= 128) {
            c = '?';
        }

        const auto& [size, bearing, advance] = _chars[c];

        Box2 charBox;
        charBox.min.x = x + bearing.x;
        charBox.max.x = charBox.min.x + size.x;
        charBox.max.y = y + bearing.y;
        charBox.min.y = charBox.max.y - size.y;

        textBox.extend(charBox);

        if (c == '\n') {
            y -= 1.3f;
            x = 0;
        } else {
            if (c != ' ') {
                glyphs.push_back({glm::vec2(charBox.min.x, charBox.max.y - 1.0f), c});
            }
            x += advance;
        }
    }

    _buffer.use();
    VertexBuffer::setData(glyphs, GL_DYNAMIC_DRAW);
    VertexBuffer::clearUse();

    _glyphs = glyphs.size();
    return textBox;
}

void Font::setColor(const glm::vec3 &color) const {
    _shader.use();
    _color.setVec3(color);
}

void Font::render(const glm::mat4& transformation) const {
    _shader.use();
    _transformation.setMat4(transformation);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _textureId);

    _attributes.use();
    VertexAttributes::draw(GL_POINTS, _glyphs);
    VertexAttributes::clearUse();
}
