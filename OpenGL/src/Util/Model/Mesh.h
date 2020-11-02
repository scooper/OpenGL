#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Util/Texture.h"
#include "Util/Shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture*> textures);
    ~Mesh();
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture*> m_Textures;

    void Draw(Shader& shader);

private:
    unsigned int m_VAO, m_VBO, m_EBO;

    void Init();
};