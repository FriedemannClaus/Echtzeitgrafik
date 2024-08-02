#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <filesystem>
#include <GL/glew.h>

class Texture {
public:
	Texture(const std::filesystem::path& filePath, GLenum target = GL_TEXTURE_2D);
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void bind() const;
	void unbind() const;
	void setFiltering(GLenum minFilter, GLenum magFilter);
	void setWrapping(GLenum wrapS, GLenum wrapT);

private:
	GLuint textureID;
	GLenum target;
	int width, height, channels;

	void loadTexture(const std::filesystem::path& filePath);
};

#endif
