#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const GLuint WIDTH = 800, HEIGHT = 600;
static const GLuint INFOLOG_LEN = 512;

GLfloat triangle[] = 
{
    /*   Positions            Colors */
         0.9f, -0.9f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,
         0.0f,  0.9f, 0.0f,   0.0f, 0.0f, 1.0f
};

float rectangle[] = 
{
    // first triangle
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top left
};

float cube[] = {
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
};

float rectangleIndexed[] = 
{
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,// bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,// bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f // top left 
};
unsigned int indices[] = 
{  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

// Funktionen zur Initialisierung der Matrizen
// void initMatrices(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
// {
//     // Erstellen der Modelmatrix (Translation, Skalierung, Rotation)
//     model = glm::mat4(1.0f); // Identitätsmatrix
//     model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); // Beispiel: Verschieben
//     model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Beispiel: Rotieren
//     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); // Beispiel: Skalieren

//     // Erstellen der Viewmatrix (Kameraposition und -blickrichtung)
//     view = glm::lookAt(
//         glm::vec3(0.0f, 0.0f, 3.0f), // Kameraposition
//         glm::vec3(0.0f, 0.0f, 0.0f), // Blickrichtung
//         glm::vec3(0.0f, 1.0f, 0.0f)  // Up-Vektor
//     );

//     //Erstellen der Projektionsmatrix (Perspektivprojektion)
//     projection = glm::perspective(
//         glm::radians(45.0f), // Field of View
//         4.0f / 3.0f,         // Seitenverhältnis
//         0.1f,                // Near Plane
//         100.0f               // Far Plane
//     );
// }
