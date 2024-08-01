﻿#include "SolarSystem.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

SolarSystem::SolarSystem(const std::filesystem::path& meshPath) {
    loadMesh(meshPath);
    // name, size, distanceToSun, rotationSpeed, orbitSpeed, sharedBuffer, reverseRotation
    planets.emplace_back("Sun", 109.0f, 0.0f, 360.0f / 600.0f, 0.0f, geometryBuffer);
    planets.emplace_back("Mercury", 0.383f, 57.9f, 360.0f / 84.456f, 47.87f, geometryBuffer);
    planets.emplace_back("Venus", 0.949f, 108.2f, 360.0f / 349.947f, 35.02f, geometryBuffer, true);  // Rotates in opposite direction
    planets.emplace_back("Earth", 1.0f, 149.6f, 360.0f / 1.436f, 29.78f, geometryBuffer);
    planets.emplace_back("Mars", 0.532f, 227.9f, 360.0f / 1.477f, 24.08f, geometryBuffer);
    planets.emplace_back("Jupiter", 11.21f, 778.6f, 360.0f / 0.595f, 13.07f, geometryBuffer);
    planets.emplace_back("Saturn", 9.45f, 1433.5f, 360.0f / 0.647f, 9.69f, geometryBuffer);
    planets.emplace_back("Uranus", 4.01f, 2872.5f, 360.0f / 1.034f, 6.81f, geometryBuffer, true);  // Rotates in opposite direction
    planets.emplace_back("Neptune", 3.88f, 4495.1f, 360.0f / 0.966f, 5.43f, geometryBuffer);
}

SolarSystem::~SolarSystem() {
    releaseResources();
}

SolarSystem::SolarSystem(SolarSystem&& other) noexcept
    : planets(std::move(other.planets)), geometryBuffer(std::move(other.geometryBuffer)), vertices(std::move(other.vertices)), indices(std::move(other.indices)) {}

SolarSystem& SolarSystem::operator=(SolarSystem&& other) noexcept {
    if (this != &other) {
        releaseResources();
        planets = std::move(other.planets);
        geometryBuffer = std::move(other.geometryBuffer);
        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
    }
    return *this;
}

void SolarSystem::loadMesh(const std::filesystem::path& meshPath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error: " << importer.GetErrorString() << std::endl;
        return;
    }

    aiMesh* mesh = scene->mMeshes[0];
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }

        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    geometryBuffer.initialize(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void SolarSystem::draw(Shader& shader) {
    for (auto& planet : planets) {
        planet.draw(shader);
    }
}

void SolarSystem::update(float deltaTime) {
    for (auto& planet : planets) {
        planet.update(deltaTime);
    }
}

void SolarSystem::releaseResources() {
    geometryBuffer.cleanUp();
}

