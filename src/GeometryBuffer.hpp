#ifndef GEOMETRYBUFFER_H
#define GEOMETRYBUFFER_H
#pragma once

#include <GL/glew.h> // Include GLEW (or any other OpenGL loader library)
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
    GLuint getVAO() const { return vao; }

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    void copyFrom(const GeometryBuffer& other);
};

#endif // GEOMETRYBUFFER_H

