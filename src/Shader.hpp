#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <filesystem>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use();
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::vec4& value);
    void setUniform(const std::string& name, const glm::mat4& value);

private:
    GLuint programID;
    std::string readShaderFile(const std::filesystem::path& filePath);
    void compileShader(const char* vertexCode, const char* fragmentCode);
    void checkCompileErrors(GLuint shader, std::string type);
    GLint getUniformLocation(const std::string& name);
};

#endif
