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
 * Reads .obj file into vertices and indices arrays.
 */
void Mesh::generateFileMesh() {

    // File to Mesh
    //std::string filename = "../res/meshes/ModernVase.obj";                          // Vase
    //std::string filename = "../res/meshes/Basketball_Triangulated.obj";           // Basketball
    //std::string filename = "../res/meshes/Chair_Triangulated.obj";                  // Chair
    //std::string filename = "../res/meshes/torus_triangulated_sphereProj.obj";                            // Torus
    //std::string filename = "../res/meshes/Sphere_Smooth_Poked.obj";               // Sphere

    //std::string filename = "../res/meshes/sphere.fbx";                            // tangent sphere
    //std::string filename = "../res/meshes/vase.fbx";                              // tangent vase
    //std::string filename = "../res/meshes/basketball_origUV.fbx";                 // tangent basketball old UV
    //std::string filename = "../res/meshes/tree.fbx";                              // tangent tree
    //std::string filename = "../res/meshes/bootside.fbx";                              // tangent bootside
    std::string filename = "../res/meshes/bootangle.fbx";                              // tangent bootangle
    //std::string filename = "../res/meshes/boot2.fbx";                              // tangent boot

    //std::string filename = "../res/meshes/torus1.fbx";                            // tangent torus



    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;

    // Load OBJ file
    Assimp::Importer importer;
    printf("\nAttempting to read mesh from file.\n");
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenNormals);
    printf("    OBJ file read: %s\n"
           "Successfully read mesh from file.\n"
           "Formatting mesh for rendering.", filename.c_str());

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {

        // Get current mesh
        aiMesh* mesh = scene->mMeshes[i];

        // Mesh vertices
        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {

            // Set the positions
            pVertices.push_back(mesh->mVertices[j].x);
            pVertices.push_back(mesh->mVertices[j].y);
            pVertices.push_back(mesh->mVertices[j].z);

            // Set the normals
            pVertices.push_back(mesh->mNormals[j].x);
            pVertices.push_back(mesh->mNormals[j].y);
            pVertices.push_back(mesh->mNormals[j].z);

            // Set the uv coordinates
            pVertices.push_back(mesh->mTextureCoords[0][j].x);
            pVertices.push_back(mesh->mTextureCoords[0][j].y);

            ///
            pVertices.push_back(mesh->mTangents[j].x);
            pVertices.push_back(mesh->mTangents[j].y);
            pVertices.push_back(mesh->mTangents[j].z);

            pVertices.push_back(mesh->mBitangents[j].x);
            pVertices.push_back(mesh->mBitangents[j].y);
            pVertices.push_back(mesh->mBitangents[j].z);
            ///

        }

        // Mesh faces
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {

            // Get the face
            aiFace face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                pIndices.push_back(face.mIndices[k]);
            }
        }
    }

    this->numIndices = pIndices.size();

    this->verticesMesh = new GLfloat[pVertices.size()];
    this->indicesMesh = new GLuint[pIndices.size()];

    std::copy(pVertices.begin(), pVertices.end(), verticesMesh);
    std::copy(pIndices.begin(), pIndices.end(), indicesMesh);
}

/*
 * Generates flat mesh and stores in vertices and indices arrays.
 */
void Mesh::generateFlatMesh(int width, int height, std::vector<Noise::Point> noise) {

    // Grid resolution
    int n_width = width;
    int n_height = height;

    // Grid dimensions (centered at (0, 0))
    float f_width = 5.0f;
    float f_height = 5.0f;

    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;

    // Generate vertex and texture coordinates
    for (int j = 0; j < n_width; ++j) {
        for (int i = 0; i < n_height; ++i) {

            // Calculate vertex positions
            pVertices.push_back(-f_width / 2 + j / (float)n_width * f_width);
            pVertices.push_back(0.0f);
            //pVertices.push_back(noise[j * 1000 + i].colour);
            pVertices.push_back(-f_height / 2 + i / (float)n_height * f_height);

            // Push null normals
            pVertices.push_back(0.0f);
            pVertices.push_back(0.0f);
            pVertices.push_back(0.0f);

            // Calculate texture coordinates
            pVertices.push_back(i / (float)(n_width - 1));
            pVertices.push_back(j / (float)(n_height - 1));
        }
    }

    for (unsigned int i = 0; i < width - 1; i++) {
        for (unsigned int j = 0; j < height - 1; j++) {

            unsigned int tempIndices[4];
            tempIndices[0] = i * width + j;
            tempIndices[1] = (i + 1) * width + j;
            tempIndices[2] = i * width + j + 1;
            tempIndices[3] = (i + 1) * width + j + 1;

            // First triangle indices and vertices in current cell
            pIndices.push_back(tempIndices[0]);
            pIndices.push_back(tempIndices[1]);
            pIndices.push_back(tempIndices[2]);

            // Second triangle indices and vertices in current cell
            pIndices.push_back(tempIndices[1]);
            pIndices.push_back(tempIndices[2]);
            pIndices.push_back(tempIndices[3]);
        }
    }

    this->numIndices = pIndices.size();

    this->verticesMesh = new GLfloat[pVertices.size()];
    this->indicesMesh = new GLuint[pIndices.size()];

    std::copy(pVertices.begin(), pVertices.end(), verticesMesh);
    std::copy(pIndices.begin(), pIndices.end(), indicesMesh);
}

/*
 * Generates cube mesh and stores in vertices and indices arrays.
 */
void Mesh::generateCubeMesh() {


    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;

    /*GLfloat vertices[] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };*/

    GLfloat vertices[] = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    /*for (int i = 0; i < 108; i++) {
        vertices[i] = vertices[i] * 10.0f;
    }*/

    GLuint indices[36];
    for (int i = 0; i < 36; ++i) {
        indices[i] = i;
    }

    this->numIndicesSkybox = 36;
    this->verticesMeshSkybox = new GLfloat[108];
    this->indicesMeshSkybox = new GLuint[36];

    this->verticesMeshSkybox = vertices;
    this->indicesMeshSkybox = indices;

    /*this->numIndicesSkybox = pIndices.size();
    this->verticesMeshSkybox = new GLfloat[pVertices.size()];
    this->indicesMeshSkybox = new GLuint[pIndices.size()];

    std::copy(pVertices.begin(), pVertices.end(), verticesMeshSkybox);
    std::copy(pIndices.begin(), pIndices.end(), indicesMeshSkybox);*/
}

/*
 * Reads .obj file into vertices and indices arrays.
 */
void Mesh::generateSphereMesh() {

    // File to Mesh
    std::string filename = "../res/meshes/Sphere_Smooth_Poked.obj";               // Sphere

    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;

    // Load OBJ file
    Assimp::Importer importer;
    printf("\nAttempting to read mesh from file.\n");
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenNormals);
    printf("    OBJ file read: %s\n"
           "Successfully read mesh from file.\n"
           "Formatting mesh for rendering.", filename.c_str());

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {

        // Get current mesh
        aiMesh* mesh = scene->mMeshes[i];

        // Mesh vertices
        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {

            // Set the positions
            pVertices.push_back(mesh->mVertices[j].x);
            pVertices.push_back(mesh->mVertices[j].y);
            pVertices.push_back(mesh->mVertices[j].z);

            // Set the normals
            pVertices.push_back(mesh->mNormals[j].x);
            pVertices.push_back(mesh->mNormals[j].y);
            pVertices.push_back(mesh->mNormals[j].z);

            // Set the uv coordinates
            pVertices.push_back(mesh->mTextureCoords[0][j].x);
            pVertices.push_back(mesh->mTextureCoords[0][j].y);
        }

        // Mesh faces
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {

            // Get the face
            aiFace face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                pIndices.push_back(face.mIndices[k]);
            }
        }
    }

    this->numIndicesPlanet = pIndices.size();

    this->verticesMeshPlanet = new GLfloat[pVertices.size()];
    this->indicesMeshPlanet = new GLuint[pIndices.size()];

    std::copy(pVertices.begin(), pVertices.end(), verticesMeshPlanet);
    std::copy(pIndices.begin(), pIndices.end(), indicesMeshPlanet);
}

/*
 * Drives mesh generation from external files.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generateMeshFromFile() {

    // Read object file into Mesh
    printf("\nStarting mesh generation (from file).");
    generateFileMesh();
    printf("\nSuccessfully completed mesh generation (from file).\n");
}

/*
 * Drives flat mesh generation.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generateMeshFromNoise(int width, int height, std::vector<Noise::Point> noise) {

    // Read object file into Mesh
    printf("\nStarting mesh generation (flat mesh).");
    generateFlatMesh(width, height, noise);
    printf("\nSuccessfully completed mesh generation (flat mesh).\n");
}

/*
 * Drives skybox generation.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generateSkybox() {

    // Read object file into Mesh
    printf("\nStarting mesh generation (skybox).");
    generateCubeMesh();
    printf("\nSuccessfully completed mesh generation (skybox).\n");
}

/*
 * Drives planet generation.
 *
 * Returns:
 *      Vector of Meshes (typically just one mesh)
 */
void Mesh::generatePlanet() {

    // Read object file into Mesh
    printf("\nStarting mesh generation (planet).");
    generateSphereMesh();
    printf("\nSuccessfully completed mesh generation (planet).\n");
}


