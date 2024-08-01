#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.hpp"
#include <iostream>

Texture::Texture(const std::filesystem::path& filePath, GLenum target)
	: textureID(0), target(target), width(0), height(0), channels(0) {
	glGenTextures(1, &textureID);
	bind();
	loadTexture(filePath);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

Texture::Texture(Texture&& other) noexcept
	: textureID(other.textureID), target(other.target), width(other.width), height(other.height), channels(other.channels) {
	other.textureID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (this != &other) {
		glDeleteTextures(1, &textureID);

		textureID = other.textureID;
		target = other.target;
		width = other.width;
		height = other.height;
		channels = other.channels;

		other.textureID = 0;
	}
	return *this;
}

void Texture::bind() const {
	glBindTexture(target, textureID);
}

void Texture::unbind() const {
	glBindTexture(target, 0);
}

void Texture::setFiltering(GLenum minFilter, GLenum magFilter) {
	bind();
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	unbind();
}

void Texture::setWrapping(GLenum wrapS, GLenum wrapT) {
	bind();
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
	unbind();
}

void Texture::loadTexture(const std::filesystem::path& filePath) {
	unsigned char* data = stbi_load(filePath.string().c_str(), &width, &height, &channels, 0);
	if (data) {
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(target);
	}
	else {
		std::cerr << "Failed to load texture: " << filePath << std::endl;
	}
	stbi_image_free(data);
}
