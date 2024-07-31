#include "SolarSystem.hpp"
#include <iostream>
#include <utility>

SolarSystem::SolarSystem(const std::filesystem::path& meshPath) {
    loadMesh(meshPath);
}

SolarSystem::~SolarSystem() {
    releaseResources();
}

SolarSystem::SolarSystem(const SolarSystem& other)
    : vertices(other.vertices), indices(other.indices) {
    geometryBuffer.initialize(vertices.data(), vertices.size());
}

SolarSystem& SolarSystem::operator=(const SolarSystem& other) {
    if (this != &other) {
        releaseResources();

        vertices = other.vertices;
        indices = other.indices;
        geometryBuffer = other.geometryBuffer;
        geometryBuffer.initialize(vertices.data(), vertices.size());

    }
    return *this;
}

SolarSystem::SolarSystem(SolarSystem&& other) noexcept
    : geometryBuffer(std::move(other.geometryBuffer)), vertices(std::move(other.vertices)), indices(std::move(other.indices)) {}

SolarSystem& SolarSystem::operator=(SolarSystem&& other) noexcept {
    if (this != &other) {
        releaseResources();

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
    createGeometryBuffer(scene);
    importer.FreeScene();
}

void SolarSystem::createGeometryBuffer(const aiScene* scene) {
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

    geometryBuffer.initialize(vertices.data(), vertices.size());
}


void SolarSystem::draw() {
    geometryBuffer.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
    geometryBuffer.unbind();
}

void SolarSystem::update() {
}

void SolarSystem::releaseResources() {
    std::cout << "solar system released" << std::endl;
    geometryBuffer.cleanUp();
}
