#include <iostream>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "helper/RootDir.h"

#include "shared/data.h"
#include "shared/functions.h"

double lastTime = 0.0;
int frameCount = 0;
float fps = 0.0f;


void updateFPS() {
	double currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - lastTime >= 1.0) { // Every second
		fps = frameCount / static_cast<float>(currentTime - lastTime);
		frameCount = 0;
		lastTime = currentTime;
		std::cout << "FPS: " << fps << std::endl;
	}
}

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}


int main(int argc, char** argv)
{
	std::cout << "HelloTriangleRetained" << std::endl;

	GLFWwindow* window = initAndCreateWindow();
	glViewport(0, 0, WIDTH, HEIGHT);

	// std::cout << std::filesystem::path(ROOT_DIR) / "res/shader.frag" << std::endl;
	std::filesystem::path simpleVertexShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.vert";
	std::filesystem::path simpleFragmentShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.frag";

	GLint shaderProgram = createShaderPipelineFromPaths(simpleVertexShaderPath, simpleFragmentShaderPath);

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	/* Position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	/* Color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glUseProgram(shaderProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

	while (glfwWindowShouldClose(window) == 0)
	{


		// clear the window
		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// update fps
		updateFPS();

		// swap buffer
		glfwSwapBuffers(window);
		

		// process user events
		glfwPollEvents();
	}

	glfwTerminate();
}