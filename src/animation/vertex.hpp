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

#ifndef NIHILO_VERTEX_HPP
#define NIHILO_VERTEX_HPP
#include <vector>

class VertexAttributes {

    public:

    VertexAttributes();

    ~VertexAttributes();

    void use() const;

    static void clearUse();

    static void setFloat(unsigned int index, int size, int stride, unsigned int offset);

    static void setByte(unsigned int index, int size, int stride, int offset);

    static void draw(unsigned int mode, unsigned long long size);

    private:

    unsigned int _id;
};

class VertexBuffer {

    public:

    VertexBuffer();

    ~VertexBuffer();

    void use() const;

    static void clearUse();

    static void setData(unsigned long long size, const void* data, unsigned int usage);

    template<typename T>
    static void setData(const std::vector<T>& data, const unsigned int usage) {
        setData(sizeof(T) * data.size(), &data[0], usage);
    }

    private:

    unsigned int _id;
};


#endif //NIHILO_VERTEX_HPP