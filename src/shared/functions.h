#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "data.h"
#include "readfile.h"

GLFWwindow* initAndCreateWindow(bool debugContext = false)
{
	GLFWwindow* window;

	if (glfwInit() == 0)
	{
		std::cerr << "GLFW failed to initiate." << std::endl;
	}
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugContext);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Echtzeitgrafik", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "GLFW failed to create window." << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLFW failed to create window." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		auto debugCallback = [](
			GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei messageLength, const GLchar* message, const void* userParam)
			{
				std::cerr << "[OpenGL] " << id << ": " << message << std::endl;
			};
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugCallback, nullptr);
	}
	glEnable(GL_MULTISAMPLE);

	return window;
}


GLint createShaderPipeline(const char* vertexSource, const char* fragmentSource)
{
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[INFOLOG_LEN];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, INFOLOG_LEN, NULL, infoLog);
		printf("Vertex-Shader compilation failed\n%s\n", infoLog);
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, INFOLOG_LEN, NULL, infoLog);
		printf("Fragment-Shader compilation failed\n%s\n", infoLog);
	}

	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, INFOLOG_LEN, NULL, infoLog);
		printf("Shader linking failed\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLint createShaderPipelineFromPaths(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) 
{
	std::string vertexSourceStr = readFile(vertexPath);
	std::string fragmentSourceStr = readFile(fragmentPath);

	return createShaderPipeline(vertexSourceStr.c_str(), fragmentSourceStr.c_str());
}

