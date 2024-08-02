#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glm/glm.hpp>
#include "Shader.hpp"

class PointLight {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color, float constant, float linear, float quadratic);

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;

    void configureShader(Shader& shader) const;

private:
    glm::vec3 position;
    glm::vec3 color;
    float constant;
    float linear;
    float quadratic;
};

#endif
