#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "shared/readfile.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) {
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);
	compileShader(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

Shader::Shader(Shader&& other) noexcept
	: programID(other.programID) {
	other.programID = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	if (this != &other) {
		glDeleteProgram(programID);
		programID = other.programID;
		other.programID = 0;
	}
	return *this;
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::setUniform(const std::string& name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, float value) {
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) {
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::vec4& value) {
	glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

GLint Shader::getUniformLocation(const std::string& name) {
	return glGetUniformLocation(programID, name.c_str());
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode) {
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);
	checkCompileErrors(programID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::readShaderFile(const std::filesystem::path& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		std::cerr << "Unable to open file " << filePath << std::endl;
		return "";
	}
	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
