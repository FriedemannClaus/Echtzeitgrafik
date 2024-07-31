#include <iostream>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "helper/RootDir.h"

#include "shared/data.h"
#include "shared/functions.h"
#include "shared/readfile.h"
#include "Shader.hpp"
#include "GeometryBuffer.hpp"

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

#include <iostream>

// Both global to be correctly adjusted in the 
GLint shaderProgram;  
static bool usePerspectiveProjection = true; 

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Umschalten des Projektionstyps
        usePerspectiveProjection = !usePerspectiveProjection;

        // Überprüfen und Anpassen der Projektion
        glm::mat4 projection;
        if (usePerspectiveProjection) {
            std::cout << "Wechsel zu Perspektivprojektion" << std::endl;
            projection = glm::perspective(
                glm::radians(45.0f), // Field of View
                4.0f / 3.0f,         // Seitenverhältnis
                0.1f,                // Near Plane
                100.0f               // Far Plane
            );
        }
        else {
            std::cout << "Wechsel zu Orthogonaler Projektion" << std::endl;
            projection = glm::ortho(
                -1.0f, 1.0f,  // X-Achse
                -1.0f, 1.0f,  // Y-Achse
                0.1f, 100.0f  // Z-Achse
            );
        }

        GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
    }
}

int main(int argc, char** argv) {
    std::cout << "HelloTriangleRetained" << std::endl;


	GLFWwindow* window = initAndCreateWindow();
	glViewport(0, 0, WIDTH, HEIGHT);

    std::filesystem::path simpleVertexShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.vert";
    std::filesystem::path simpleFragmentShaderPath = std::filesystem::path(ROOT_DIR) / "res/shader.frag";


    Shader shader(simpleVertexShaderPath, simpleFragmentShaderPath);

    GeometryBuffer geometryBuffer;
    geometryBuffer.initialize(std::vector<float>(triangle, triangle + sizeof(triangle) / sizeof(triangle[0])));

    shader.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);


        geometryBuffer.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
        geometryBuffer.unbind();


		updateFPS();

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

    geometryBuffer.~GeometryBuffer();

    glfwTerminate();

    return 0;
}
