#include "Planet.hpp"

Planet::Planet(const std::string& name, float size, float distanceToSun, float rotationSpeed, float orbitSpeed, const std::filesystem::path& texturePath, bool reverseRotation)
    : name(name), size(size), distanceToSun(distanceToSun), rotationSpeed(rotationSpeed), orbitSpeed(orbitSpeed), reverseRotation(reverseRotation),
    currentRotationAngle(0.0f), currentOrbitAngle(0.0f), texture(texturePath) {}

Planet::~Planet() {
    geometryBuffer.cleanUp();
}

// Kopierkonstruktor und Copy-Zuweisungsoperator löschen
// Planet::Planet(const Planet& other) = delete;
// Planet& Planet::operator=(const Planet& other) = delete;

Planet::Planet(Planet&& other) noexcept
    : name(std::move(other.name)), size(other.size), distanceToSun(other.distanceToSun),
    rotationSpeed(other.rotationSpeed), orbitSpeed(other.orbitSpeed),
    currentRotationAngle(other.currentRotationAngle), currentOrbitAngle(other.currentOrbitAngle),
    geometryBuffer(std::move(other.geometryBuffer)), texture(std::move(other.texture)) {
    other.size = 0.0f;
    other.distanceToSun = 0.0f;
    other.rotationSpeed = 0.0f;
    other.orbitSpeed = 0.0f;
    other.currentRotationAngle = 0.0f;
    other.currentOrbitAngle = 0.0f;
}

Planet& Planet::operator=(Planet&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        size = other.size;
        distanceToSun = other.distanceToSun;
        rotationSpeed = other.rotationSpeed;
        orbitSpeed = other.orbitSpeed;
        currentRotationAngle = other.currentRotationAngle;
        currentOrbitAngle = other.currentOrbitAngle;
        geometryBuffer = std::move(other.geometryBuffer);
        texture = std::move(other.texture);

        other.size = 0.0f;
        other.distanceToSun = 0.0f;
        other.rotationSpeed = 0.0f;
        other.orbitSpeed = 0.0f;
        other.currentRotationAngle = 0.0f;
        other.currentOrbitAngle = 0.0f;
    }
    return *this;
}

void Planet::draw() {
    texture.bind();
    geometryBuffer.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    geometryBuffer.unbind();
    texture.unbind();
}

void Planet::update(float deltaTime) {
    float rotationDirection = reverseRotation ? -1.0f : 1.0f;
    currentRotationAngle += rotationDirection * rotationSpeed * deltaTime;
    if (currentRotationAngle > 360.0f) {
        currentRotationAngle -= 360.0f;
    }

    currentOrbitAngle += orbitSpeed * deltaTime;
    if (currentOrbitAngle > 360.0f) {
        currentOrbitAngle -= 360.0f;
    }
}

std::string Planet::getName() const {
    return name;
}

float Planet::getSize() const {
    return size;
}

float Planet::getDistanceToSun() const {
    return distanceToSun;
}

float Planet::getRotationSpeed() const {
    return rotationSpeed;
}

float Planet::getOrbitSpeed() const {
    return orbitSpeed;
}

const Texture& Planet::getTexture() const {
    return texture;
}
