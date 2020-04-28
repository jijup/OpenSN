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
 * Drives mesh generation.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
std::vector<Mesh::s_Mesh> Mesh::generateMesh() {

    // Read object file into Mesh
    printf("\nStarting mesh generation.\n");
    readObjIntoMesh();
    printf("Successfully completed mesh generation.\n");

    return meshes;
}


