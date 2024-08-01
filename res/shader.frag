#version 410 core

in vec2 TexCoord; // Eingabe der Texturkoordinaten
out vec4 FragColor;

uniform sampler2D texture1; // Die Textur, die wir anwenden wollen

void main() {
    FragColor = texture(texture1, TexCoord);
}
