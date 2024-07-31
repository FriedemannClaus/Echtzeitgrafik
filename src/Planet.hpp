#ifndef PLANET_HPP
#define PLANET_HPP
#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "GeometryBuffer.hpp"

class Planet {
public:
    Planet(const std::string& name, float size, float distanceToSun, float rotationSpeed, float orbitSpeed, bool reverseRotation = false);
    ~Planet();

    // copy constructor
    Planet(const Planet& other);
    // copy assignment
    Planet& operator=(const Planet& other);
    // move constructor
    Planet(Planet&& other) noexcept;
    // move assignment
    Planet& operator=(Planet&& other) noexcept;

    void draw();
    void update(float deltaTime);

    std::string getName() const;
    float getSize() const;
    float getDistanceToSun() const;
    float getRotationSpeed() const;
    float getOrbitSpeed() const;

private:
    std::string name;
    float size;
    float distanceToSun;
    float rotationSpeed;
    float orbitSpeed;
    bool reverseRotation;

    float currentRotationAngle;
    float currentOrbitAngle;

    GeometryBuffer geometryBuffer;
};

#endif
