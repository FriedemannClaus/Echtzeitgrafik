#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP
#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <GL/glew.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "GeometryBuffer.hpp"

class SolarSystem {
public:
    SolarSystem(const std::filesystem::path& meshPath);
    ~SolarSystem();

    // copy constructor
    SolarSystem(const SolarSystem& other);
    // copy assignment
    SolarSystem& operator=(const SolarSystem& other);
    // move constructor
    SolarSystem(SolarSystem&& other) noexcept;
    // move assignment
    SolarSystem& operator=(SolarSystem&& other) noexcept;

    void draw();
    void update();

private:
    void loadMesh(const std::filesystem::path& meshPath);
    void createGeometryBuffer(const aiScene* scene);
    void releaseResources();

    GeometryBuffer geometryBuffer;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

#endif // SOLAR_SYSTEM_HPP


