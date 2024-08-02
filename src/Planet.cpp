#include "Planet.hpp"
#include <glm/gtc/matrix_transform.hpp>

Planet::Planet(const std::string& name, float size, float distanceToSun, float rotationSpeed, float orbitSpeed, const std::filesystem::path& texturePath, GeometryBuffer& sharedBuffer, bool reverseRotation)
	: name(name), size(size), distanceToSun(distanceToSun), rotationSpeed(rotationSpeed), orbitSpeed(orbitSpeed), reverseRotation(reverseRotation),
	currentRotationAngle(0.0f), currentOrbitAngle(0.0f), texture(texturePath), geometryBuffer(sharedBuffer) {}

Planet::~Planet() {
}

Planet::Planet(Planet&& other) noexcept
	: name(std::move(other.name)), size(other.size), distanceToSun(other.distanceToSun),
	rotationSpeed(other.rotationSpeed), orbitSpeed(other.orbitSpeed),
	reverseRotation(other.reverseRotation), currentRotationAngle(other.currentRotationAngle),
	currentOrbitAngle(other.currentOrbitAngle), geometryBuffer(other.geometryBuffer), texture(std::move(other.texture)) {
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
		reverseRotation = other.reverseRotation;
		currentRotationAngle = other.currentRotationAngle;
		currentOrbitAngle = other.currentOrbitAngle;
		geometryBuffer = other.geometryBuffer;
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

void Planet::draw(Shader& shader) {
	shader.setUniform("model", modelMatrix);
	if (name == "Sun") {
		shader.setUniform("isSun", true);
	} else {
		shader.setUniform("isSun", false);
	}
	texture.bind();
	geometryBuffer.bind();
	glDrawElements(GL_TRIANGLES, geometryBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);
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

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(distanceToSun * cos(glm::radians(currentOrbitAngle)), 0.0f, distanceToSun * sin(glm::radians(currentOrbitAngle))));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size));
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
