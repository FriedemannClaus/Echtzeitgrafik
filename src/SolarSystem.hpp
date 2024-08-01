#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include <string>
#include <filesystem>
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

    std::vector<Planet> planets;
    GeometryBuffer geometryBuffer;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

#endif


