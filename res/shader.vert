#version 330 core
layout(location = 0) in vec3 in_pos;
layout (location = 1) in vec2 texCoord;
layout(location = 2) in vec3 in_normal;

out vec3 fragPos;
out vec3 normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragPos = vec3(model * vec4(in_pos, 1.0));
    normal = mat3(transpose(inverse(model))) * in_normal;
    TexCoord = texCoord;

    gl_Position = projection * view * model * vec4(in_pos, 1.0);
}
