#pragma once
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Util\Shader.h"
#include "Mesh.h"

class Model
{
public:
    Model(char* path);
    void Draw(Shader &shader);

private:
    std::vector<Mesh> m_Meshes;
    std::string m_Dir;

    void LoadModel(std::string path);

    void LoadNodeRecursive(aiNode *node, const aiScene *scene);
    Mesh LoadMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);
};