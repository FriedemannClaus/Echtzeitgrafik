#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>
#include <glm/glm.hpp>
#include <filesystem>
#include "Texture.hpp"
#include "GeometryBuffer.hpp"

class Planet {
public:
    Planet(const std::string& name, float size, float distanceToSun, float rotationSpeed, float orbitSpeed, const std::filesystem::path& texturePath, GeometryBuffer& sharedBuffer, bool reverseRotation = false);
    ~Planet();

    // Kopierkonstruktor und -zuweisung deaktivieren
    Planet(const Planet& other) = delete;
    Planet& operator=(const Planet& other) = delete;

    // Move-Konstruktor und -zuweisung
    Planet(Planet&& other) noexcept;
    Planet& operator=(Planet&& other) noexcept;

    void draw();
    void update(float deltaTime);

    std::string getName() const;
    float getSize() const;
    float getDistanceToSun() const;
    float getRotationSpeed() const;
    float getOrbitSpeed() const;
    const Texture& getTexture() const;

private:
    std::string name;
    float size;
    float distanceToSun;
    float rotationSpeed;
    float orbitSpeed;
    bool reverseRotation;
    float currentRotationAngle;
    float currentOrbitAngle;
    GeometryBuffer& geometryBuffer;
    Texture texture; // Textur-Variable
};

#endif // PLANET_HPP
