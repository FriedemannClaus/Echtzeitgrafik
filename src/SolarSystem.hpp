#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include <filesystem>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "GeometryBuffer.hpp"
#include "Planet.hpp"
#include "GeometryBuffer.hpp"
#include "Shader.hpp"

class SolarSystem {
public:
	SolarSystem(const std::filesystem::path& meshPath);
	~SolarSystem();

	SolarSystem(const SolarSystem& other) = delete;
	SolarSystem& operator=(const SolarSystem& other) = delete;
	SolarSystem(SolarSystem&& other) noexcept;
	SolarSystem& operator=(SolarSystem&& other) noexcept;

	void draw(Shader& shader);
	void update(float deltaTime);

private:
	void loadMesh(const std::filesystem::path& meshPath);
	void releaseResources();

	GeometryBuffer geometryBuffer;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<Planet> planets;
};

#endif
