#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include <filesystem>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "GeometryBuffer.hpp"
#include "Planet.hpp"

class SolarSystem {
public:
    SolarSystem(const std::filesystem::path& meshPath);
    ~SolarSystem();

    // Kopierkonstruktor und -zuweisung deaktivieren
    SolarSystem(const SolarSystem& other) = delete;
    SolarSystem& operator=(const SolarSystem& other) = delete;

    // Move-Konstruktor und -zuweisung
    SolarSystem(SolarSystem&& other) noexcept;
    SolarSystem& operator=(SolarSystem&& other) noexcept;

    void draw();
    void update(float deltaTime);

private:
    void loadMesh(const std::filesystem::path& meshPath);
    void createGeometryBuffer(const aiScene* scene);
    void releaseResources();

    GeometryBuffer geometryBuffer;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Planet> planets; // Liste der Planeten
};

#endif // SOLAR_SYSTEM_HPP
