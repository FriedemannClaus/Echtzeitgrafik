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
#include <glm/gtc/matrix_transform.hpp>

#include "shared/data.h"
#include "shared/functions.h"
#include "shared/readfile.h"
#include "Shader.hpp"
#include "GeometryBuffer.hpp"
#include "SolarSystem.hpp"
#include "Texture.hpp"

double lastTime = 0.0;
int frameCount = 0;
float fps = 0.0f;

static bool usePerspectiveProjection = true;

void togglePerspectiveProjection(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		usePerspectiveProjection = !usePerspectiveProjection;
		std::cout << (usePerspectiveProjection ? "Wechsel zu Perspektivprojektion" : "Wechsel zu Orthogonaler Projektion") << std::endl;
	}
}


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

int main(int argc, char** argv) {
    std::cout << "HelloTriangleRetained" << std::endl;

    GLFWwindow* window = initAndCreateWindow();
    glViewport(0, 0, WIDTH, HEIGHT);

    std::filesystem::path simpleVertexShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.vert";
    std::filesystem::path simpleFragmentShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.frag";
	Shader shader(simpleVertexShaderPath, simpleFragmentShaderPath);

    std::filesystem::path meshPath = std::filesystem::path(ROOT_DIR) / "res/sphere.obj";
    SolarSystem solarSystem{ meshPath };

    std::filesystem::path texturePath = std::filesystem::path(ROOT_DIR) / "res/textures/2k_earth.jpg";
    Texture texture(texturePath);
    texture.setFiltering(GL_LINEAR, GL_LINEAR);
    texture.setWrapping(GL_REPEAT, GL_REPEAT);

	glEnable(GL_DEPTH_TEST);

	glm::mat4 model, view, projection;

	model = glm::mat4(1.0f); // Identity matrix, cube starts at origin
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Position it at the origin
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Example: Rotation
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // Example: Scaling

	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f), // Camera position
		glm::vec3(0.0f, 0.0f, 0.0f), // Look-at point
		glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
	);

	glfwSetKeyCallback(window, togglePerspectiveProjection);
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	shader.use();

	while (!glfwWindowShouldClose(window))
	{
		if (usePerspectiveProjection) {
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
		}
		else {
			projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 1000.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);

		shader.use();
		shader.setUniform("model", model);
		shader.setUniform("view", view);
		shader.setUniform("projection", projection);

		solarSystem.update(0.01f); 
        texture.bind();
        solarSystem.draw();
        texture.unbind();

        updateFPS();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glfwTerminate();
	return 0;
}
