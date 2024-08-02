#include <iostream>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>
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
#include "PointLight.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

double lastTime = 0.0;
int frameCount = 0;
float fps = 0.0f;

static bool usePerspectiveProjection = true;
Camera camera(glm::vec3(-200.0f, 100.0f, 200.0f), glm::vec3(0.0f, 1.0f, 0.0f), -25.0f, -15.0f);
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
glm::mat4 projection;

void togglePerspectiveProjection(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		usePerspectiveProjection = !usePerspectiveProjection;
		std::cout << (usePerspectiveProjection ? "Wechsel zu Perspektivprojektion" : "Wechsel zu Orthogonaler Projektion") << std::endl;
	}
}

void updateFPS() {
    double currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - lastTime >= 1.0) {
        fps = frameCount / static_cast<float>(currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
        std::cout << "FPS: " << fps << std::endl;
    }
}

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(GLFW_KEY_W, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(GLFW_KEY_S, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(GLFW_KEY_A, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(GLFW_KEY_D, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.processMouseScroll(yoffset);
}

int main(int argc, char** argv)
{
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

	glfwSetKeyCallback(window, togglePerspectiveProjection);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

    PointLight pointLight(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f), 0.5, 0.001, 0.00000000003); // Closer position


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window, deltaTime);

		if (usePerspectiveProjection) {
			projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 10000.0f);
		}
		else {
			projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 10000.0f);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		shader.use();

		shader.setUniform("model", glm::mat4(1.0f));
		shader.setUniform("view", camera.getViewMatrix());
		shader.setUniform("projection", projection);

		pointLight.configureShader(shader);

		solarSystem.update(0.01f); 
		texture.bind();
		solarSystem.draw(shader);
		texture.unbind();

		updateFPS();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
