#include "GeometryBuffer.hpp"

GeometryBuffer::GeometryBuffer()
	: vao(0), vbo(0), ebo(0) {}

GeometryBuffer::~GeometryBuffer() {
	cleanUp();
}

GeometryBuffer::GeometryBuffer(const GeometryBuffer& other)
	: vao(0), vbo(0), ebo(0) {
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
	: vao(other.vao), vbo(other.vbo), ebo(other.ebo) {
	other.vao = 0;
	other.vbo = 0;
	other.ebo = 0;
}

GeometryBuffer& GeometryBuffer::operator=(GeometryBuffer&& other) noexcept {
	if (this != &other) {
		cleanUp();
		vao = other.vao;
		vbo = other.vbo;
		ebo = other.ebo;
		other.vao = 0;
		other.vbo = 0;
		other.ebo = 0;
	}
	return *this;
}

void GeometryBuffer::initialize(const float* vertices, int vertexSize, const unsigned int* indices, int indexSize) {
	this->indexCount = indexSize;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void GeometryBuffer::bind() const {
	glBindVertexArray(vao);
}

void GeometryBuffer::unbind() const {
	glBindVertexArray(0);
}

void GeometryBuffer::cleanUp() {
	if (ebo) {
		glDeleteBuffers(1, &ebo);
	}
	if (vbo) {
		glDeleteBuffers(1, &vbo);
	}
	if (vao) {
		glDeleteVertexArrays(1, &vao);
	}
}

void GeometryBuffer::copyFrom(const GeometryBuffer& other) {
	vao = other.vao;
	vbo = other.vbo;
	ebo = other.ebo;
}

size_t GeometryBuffer::getIndexCount() const {
	return indexCount;
}
