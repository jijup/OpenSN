/**
 * Mesh.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of meshes generated from OBJ files.
 */

#include "Mesh.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}

/*
 * Reads .obj file into Mesh struct.
 */
void Mesh::readObjIntoMesh() {

    // File to Mesh
    //std::string filename = "../Meshes/TestVase.obj";
    //std::string filename = "../Meshes/AdjustedVase.obj";
    std::string filename = "../Meshes/ModernVase.obj";

    printf("    OBJ file read: %s\n", filename.c_str());

    // Load OBJ file
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenNormals);

    for (unsigned int i = 0; i < scene -> mNumMeshes; ++i) {

        // Get current mesh
        aiMesh* mesh = scene->mMeshes[i];

        //Create vectors for the vertices and indices
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Mesh vertices
        for (unsigned int j = 0; j < mesh -> mNumVertices; ++j) {

            Vertex tempVertex;

            // Set the positions
            tempVertex.position.x = mesh->mVertices[j].x;
            tempVertex.position.y = mesh->mVertices[j].y;
            tempVertex.position.z = mesh->mVertices[j].z;

            // Set the normals
            tempVertex.normal.x = mesh->mNormals[j].x;
            tempVertex.normal.y = mesh->mNormals[j].y;
            tempVertex.normal.z = mesh->mNormals[j].z;

            // Set the uv coordinates
            tempVertex.uv.x = mesh->mTextureCoords[0][j].x;
            tempVertex.uv.y = mesh->mTextureCoords[0][j].y;

            vertices.push_back(tempVertex);
        }

        // Mesh faces
        for (unsigned int j = 0; j < mesh -> mNumFaces; ++j) {

            // Get the face
            aiFace face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }

        Mesh::s_Mesh tempMesh = s_Mesh(vertices, indices);
        this->meshes.push_back(tempMesh);
    }
}

/*
 * Reads noise values into Mesh struct.
 */
void Mesh::readNoiseIntoMesh(std::vector<Noise::Point> noise, int width, int height) {

    std::vector<Vertex> vertices;
    std::vector<Vertex> indexAdjVertices;
    std::vector<unsigned int> indices;

    // Set vertices and texture coordinates
    for (int i = 0; i < noise.size(); i++) {

        Vertex tempVertex;

        // Set the positions
        tempVertex.position.x = (float)noise[i].x / (float)width;
        tempVertex.position.y = noise[i].colour;
        tempVertex.position.z = (float)noise[i].y / (float)height;

        // Set the normals
        tempVertex.normal.x = 0.5f;
        tempVertex.normal.y = 0.5f;
        tempVertex.normal.z = 0.5f;

        // Set the uv coordinates
        tempVertex.uv.x = (float)noise[i].x / (float)width;
        tempVertex.uv.y = (float)noise[i].y / (float)height;

        vertices.push_back(tempVertex);
    }

    // Set indices
    int counter = 0;
    for (unsigned int i = 0; i < width - 1; i++) {
        for (unsigned int j = 0; j < height - 1; j++) {
    //for (unsigned int i = 0; i < 149; i++) {
    //    for (unsigned int j = 0; j < 149; j++) {

            int tempIndices[4];
            tempIndices[0] = i * width + j;
            tempIndices[1] = (i + 1) * width + j;
            tempIndices[2] = i * width + j + 1;
            tempIndices[3] = (i + 1) * width + j + 1;

            // First triangle indices and vertices in current cell
            indexAdjVertices.push_back(vertices[tempIndices[0]]);
            indices.push_back(counter++);
            indexAdjVertices.push_back(vertices[tempIndices[1]]);
            indices.push_back(counter++);
            indexAdjVertices.push_back(vertices[tempIndices[2]]);
            indices.push_back(counter++);

            // Second triangle indices and vertices in current cell
            indexAdjVertices.push_back(vertices[tempIndices[1]]);
            indices.push_back(counter++);
            indexAdjVertices.push_back(vertices[tempIndices[2]]);
            indices.push_back(counter++);
            indexAdjVertices.push_back(vertices[tempIndices[3]]);
            indices.push_back(counter++);

        }
    }

    Mesh::s_Mesh tempMesh = s_Mesh(indexAdjVertices, indices);
    this->meshes.push_back(tempMesh);

    printf("sizeof vertices (before): %lu \n", sizeof(vertices));
    std::vector<Vertex>().swap(vertices);
    printf("sizeof vertices (before): %lu \n", sizeof(vertices));
    std::vector<Vertex>().swap(indexAdjVertices);
    std::vector<unsigned int>().swap(indices);

    /*
    vertices.clear();
    vertices.shrink_to_fit();
    indexAdjVertices.clear();
    indexAdjVertices.shrink_to_fit();
    indices.clear();
    indices.shrink_to_fit();
     */
}

/*
 * Sets up coordinates for given mesh for use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Mesh::setupMeshCoordinates() {

    this->numIndices = this->meshes[0].indices.size();

    // Format vertices
    printf("\n        numIndices: %lu | numVertices: %lu ", this->meshes[0].indices.size(), this->meshes[0].vertices.size());
    for (int i = 0; i < this->meshes[0].vertices.size(); ++i) {
        this->pVertices.push_back(this->meshes[0].vertices[i].position.x);
        this->pVertices.push_back(this->meshes[0].vertices[i].position.y);
        this->pVertices.push_back(this->meshes[0].vertices[i].position.z);

        this->pVertices.push_back(this->meshes[0].vertices[i].normal.x);
        this->pVertices.push_back(this->meshes[0].vertices[i].normal.y);
        this->pVertices.push_back(this->meshes[0].vertices[i].normal.z);

        this->pVertices.push_back(this->meshes[0].vertices[i].uv.x);
        this->pVertices.push_back(this->meshes[0].vertices[i].uv.y);
    }

    // Format indices
    this->pIndices = this->meshes[0].indices;

    return 0;
}

/*
 * Drives mesh generation from external files.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generateMeshFromFile() {

    // Read object file into Mesh
    printf("\nStarting mesh generation.");
    printf("\nAttempting to read mesh from file.\n");
    readObjIntoMesh();
    printf("Successfully read mesh from file.");
    printf("\nFormatting mesh for rendering.");
    setupMeshCoordinates();
    printf("\nSuccessfully completed mesh generation.\n");
}

/*
 * Drives mesh generation from noise values.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generateMeshFromNoise(std::vector<Noise::Point> noise, int width, int height) {

    // Read object file into Mesh
    printf("\nStarting mesh generation.");
    readNoiseIntoMesh(noise, width, height);
    printf("\nFormatting mesh for rendering.");
    setupMeshCoordinates();
    printf("\nSuccessfully completed mesh generation.\n");
}


