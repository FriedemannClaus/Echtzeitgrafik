#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec3 Color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float constant;
uniform float linear;
uniform float quadratic;

void main() {
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 objColor = vec3(0.78, 0.66, 0.46);
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // Ambient lighting
    float ambientStr = 0.5;
    vec3 ambient = ambientStr * lightColor;
    
    // Diffuse lighting
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    // Specular lighting
    float specularStr = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = specularStr * pow(max(dot(viewDir, reflectDir), 0.0001), 32) * lightColor;

    // Attenuation
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    vec3 result = (ambient + diffuse + specular) * Color * attenuation;
    FragColor = vec4(result, 1.0);
}
