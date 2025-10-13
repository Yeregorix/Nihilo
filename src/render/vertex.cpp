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

#include "vertex.hpp"

#include "glad.h"

VertexAttributes::VertexAttributes() : _id(0) {
    glGenVertexArrays(1, &_id);
}

VertexAttributes::~VertexAttributes() {
    glDeleteVertexArrays(1, &_id);
}

void VertexAttributes::use() const {
    glBindVertexArray(_id);
}

void VertexAttributes::clearUse() {
    glBindVertexArray(0);
}

void VertexAttributes::setFloat(const unsigned int index, const int size, const int stride, const unsigned int offset) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(index);
}

void VertexAttributes::setByte(const unsigned int index, const int size, const int stride, const int offset) {
    glVertexAttribIPointer(index, size, GL_UNSIGNED_BYTE, stride, reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(index);
}

void VertexAttributes::draw(const unsigned int mode, const unsigned long long size) {
    glDrawArrays(mode, 0, static_cast<int>(size));
}

VertexBuffer::VertexBuffer() : _id(0) {
    glGenBuffers(1, &_id);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_id);
}

void VertexBuffer::use() const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::clearUse() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const unsigned long long size, const void* data, const unsigned int usage) {
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(size), data, usage);
}
