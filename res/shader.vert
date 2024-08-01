#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;  // Neue Texturkoordinaten
layout (location = 2) in vec3 normal;    // Normalenvektor (optional, falls benötigt)

out vec2 TexCoord; // Ausgabe der Texturkoordinaten

void main() {
    gl_Position = vec4(position, 1.0f);
    TexCoord = texCoord; // Übergeben der Texturkoordinaten an das Fragment
}
