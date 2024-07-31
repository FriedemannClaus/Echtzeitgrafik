#include "GeometryBuffer.hpp"

GeometryBuffer::GeometryBuffer()
    : vao(0), vbo(0) {
}

GeometryBuffer::~GeometryBuffer() {
    cleanUp();
}

GeometryBuffer::GeometryBuffer(const GeometryBuffer& other)
    : vao(0), vbo(0) {
    copyFrom(other);
}

GeometryBuffer& GeometryBuffer::operator=(const GeometryBuffer& other) {
    if (this != &other) {
        cleanUp();
        copyFrom(other);
    }
    return *this;
}

GeometryBuffer::GeometryBuffer(GeometryBuffer&& other) noexcept
    : vao(other.vao), vbo(other.vbo) {
    other.vao = 0;
    other.vbo = 0;
}

GeometryBuffer& GeometryBuffer::operator=(GeometryBuffer&& other) noexcept {
    if (this != &other) {
        cleanUp();
        vao = other.vao;
        vbo = other.vbo;
        other.vao = 0;
        other.vbo = 0;
    }
    return *this;
}

void GeometryBuffer::initialize(const float* vertices, int size) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //sizeof(cube) already gives the correct byte size on linux. no need to multiply by float size
    //glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void GeometryBuffer::bind() const {
    glBindVertexArray(vao);
}

void GeometryBuffer::unbind() const {
    glBindVertexArray(0);
}

void GeometryBuffer::cleanUp() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}

void GeometryBuffer::copyFrom(const GeometryBuffer& other) {
    vao = other.vao;
    vbo = other.vbo;
}

