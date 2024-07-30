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

    void initialize(const std::vector<float>& vertices);
    void bind() const;
    void unbind() const;
    GLuint getVAO() const { return vao; }

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    void cleanUp();
    void copyFrom(const GeometryBuffer& other);
};

#endif // GEOMETRYBUFFER_H

