#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float constant;
uniform float linear;
uniform float quadratic;
uniform bool isSun;

uniform sampler2D texture1;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 objColor = vec3(0.78, 0.66, 0.46);
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float ambientStr = 0.1;
    vec3 ambient = ambientStr * lightColor;
    
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    float specularStr = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = vec3(0.0); // Initialize specular to zero

    // Only calculate specular if the surface is facing the light or if it's the sun
    if((dot(norm, lightDir) > 0.0) || (isSun == true)){
        specular = specularStr * pow(max(dot(viewDir, reflectDir), 0.0), 32) * lightColor;
    }
    
    // Attenuation
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
}
