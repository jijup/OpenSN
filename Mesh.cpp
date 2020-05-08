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
        meshes.push_back(tempMesh);
    }
}

/*
 * Sets up coordinates for given mesh for use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Mesh::setupMeshCoordinates() {

    // Read vertices and indices into arrays
    std::vector<Mesh::Vertex> mVertices = this->meshes[0].vertices;
    std::vector<unsigned int> mIndices = this->meshes[0].indices;

    //GLfloat vertices[mVertices.size() * 8];
    for (int i = 0; i < mVertices.size(); ++i) {
        this->pVertices.push_back(mVertices[i].position.x);
        this->pVertices.push_back(mVertices[i].position.y);
        this->pVertices.push_back(mVertices[i].position.z);

        this->pVertices.push_back(mVertices[i].normal.x);
        this->pVertices.push_back(mVertices[i].normal.y);
        this->pVertices.push_back(mVertices[i].normal.z);

        this->pVertices.push_back(mVertices[i].uv.x);
        this->pVertices.push_back(mVertices[i].uv.y);
    }

    this->numIndices = mIndices.size();
    this->pIndices = mIndices;

    return 0;
}

/*
 * Sets up coordinates for square to use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Mesh::setupSquareCoordinates() {
    GLfloat vertices[] = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    this->numIndices = 6;
    this->pVertices.assign(std::begin(vertices), std::end(vertices));
    this->pIndices.assign(std::begin(indices), std::end(indices));

    return 0;
}

/*
 * Sets up coordinates for a cube to use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Mesh::setupCubeCoordinates() {
    GLfloat vertices[] = {
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.000059f, 1.0f-0.000004f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       1.000023f, 1.0f-0.000013f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.999958f, 1.0f-0.336064f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.667969f, 1.0f-0.671889f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       1.000023f, 1.0f-0.000013f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.000059f, 1.0f-0.000004f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336098f, 1.0f-0.000071f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       1.000004f, 1.0f-0.671847f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.999958f, 1.0f-0.336064f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.336098f, 1.0f-0.000071f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.000004f, 1.0f-0.671870f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667969f, 1.0f-0.671889f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       1.000004f, 1.0f-0.671847f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f
    };

    GLuint indices[36];
    for (int i = 0; i < 36; ++i) {
        indices[i] = i;
    }

    this->numIndices = 36;
    this->pVertices.assign(std::begin(vertices), std::end(vertices));
    this->pIndices.assign(std::begin(indices), std::end(indices));

    return 0;
}

/*
 * Drives mesh generation.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
std::vector<Mesh::s_Mesh> Mesh::generateMesh() {

    // Read object file into Mesh
    printf("\nStarting mesh generation.");
    printf("\nAttempting to read mesh from file.\n");
    readObjIntoMesh();
    printf("Successfully read mesh from file.");
    printf("\nFormatting mesh for rendering.");
    setupMeshCoordinates();
    printf("\nSuccessfully completed mesh generation.\n");

    return meshes;
}


