#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H
#pragma once

#include <GL/glew.h>
#include <vector>

class GeometryBuffer {
public:
    GeometryBuffer();
    ~GeometryBuffer();

    GeometryBuffer(const GeometryBuffer& other);
    GeometryBuffer& operator=(const GeometryBuffer& other);

    GeometryBuffer(GeometryBuffer&& other) noexcept;
    GeometryBuffer& operator=(GeometryBuffer&& other) noexcept;

    void initialize(const float* vertices, int vertexSize, const unsigned int* indices, int indexSize);
    void bind() const;
    void unbind() const;
    void cleanUp();
    size_t getIndexCount() const;

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    void copyFrom(const GeometryBuffer& other);
    size_t indexCount;
};

#endif

