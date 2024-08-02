#include "PointLight.hpp"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float constant, float linear, float quadratic)
    : position(position), color(color), constant(constant), linear(linear), quadratic(quadratic) {}

PointLight::~PointLight() {}

PointLight::PointLight(const PointLight& other)
    : position(other.position), color(other.color), constant(other.constant), linear(other.linear), quadratic(other.quadratic) {}

PointLight& PointLight::operator=(const PointLight& other) {
    if (this == &other) {
        return *this;
    }
    position = other.position;
    color = other.color;
    constant = other.constant;
    linear = other.linear;
    quadratic = other.quadratic;
    return *this;
}

PointLight::PointLight(PointLight&& other) noexcept
    : position(std::move(other.position)), color(std::move(other.color)),
      constant(other.constant), linear(other.linear), quadratic(other.quadratic) {
    other.constant = 1.0f;
    other.linear = 0.0f;
    other.quadratic = 0.0f;
}

PointLight& PointLight::operator=(PointLight&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    position = std::move(other.position);
    color = std::move(other.color);
    constant = other.constant;
    linear = other.linear;
    quadratic = other.quadratic;

    other.constant = 1.0f;
    other.linear = 0.0f;
    other.quadratic = 0.0f;

    return *this;
}

void PointLight::setPosition(const glm::vec3& position) {
    this->position = position;
}

void PointLight::setColor(const glm::vec3& color) {
    this->color = color;
}

glm::vec3 PointLight::getPosition() const {
    return position;
}

glm::vec3 PointLight::getColor() const {
    return color;
}

float PointLight::getConstant() const {
    return constant;
}

float PointLight::getLinear() const {
    return linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::configureShader(Shader& shader) const {
    shader.setUniform("lightPos", getPosition());
    shader.setUniform("lightColor", getColor());
    shader.setUniform("constant", getConstant());
    shader.setUniform("linear", getLinear());
    shader.setUniform("quadratic", getQuadratic());
}
