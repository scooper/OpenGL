#include "Model.h"
#include <sstream>

#include "Util\Logger.h"

Model::Model(char* path)
{
    LoadModel(path);
}

void Model::Draw(Shader& shader)
{
    for (Mesh mesh : m_Meshes)
    {
        mesh.Draw(shader);
    }
}

void Model::LoadModel(std::string path)
{
    // assimp importer
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    // error handling
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::stringstream ss;
        ss << "Assimp Error: " << importer.GetErrorString();
        LOG_ERROR(ss.str());
        return;
    }

    m_Dir = path.substr(0, path.find_last_of('/'));

    // process scene
    LoadNodeRecursive(scene->mRootNode, scene);
}

void Model::LoadNodeRecursive(aiNode* node, const aiScene* scene)
{
    // load any meshes at this heirarchy level
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(LoadMesh(mesh, scene));
    }

    // load any children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        LoadNodeRecursive(node->mChildren[i], scene);
    }
}

Mesh Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indicies;
    std::vector<Texture*> textures;

    // vertices
    // extract vertex info
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // pos
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            // normal
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // UVs
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 uv;
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
            vertex.UV = uv;
        }
        else
        {
            vertex.UV = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // indices
    // iterate faces in mesh, and indices of each primative
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indicies.push_back(face.mIndices[j]);
        }
    }

    // textures
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
        std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(vertices, indicies, textures);
}

// TODO: rework this so it works with an independent texture manager
std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type)
{
    std::vector<Texture*> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
    {
        aiString str;
        mat->GetTexture(aiType, i, &str);
        std::string filename = std::string(str.C_Str());
        std::string fullPath = m_Dir + "/" + filename;

        Texture* tex = Texture::Create(GL_TEXTURE_2D, fullPath.c_str(), true, type);
        textures.push_back(tex);
    }

    return textures;
}
