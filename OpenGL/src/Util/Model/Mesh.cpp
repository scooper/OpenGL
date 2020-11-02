#include "Mesh.h"
#include <string>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
    m_Vertices = vertices;
    m_Indices = indices;
    m_Textures = textures;

    Init();
}

Mesh::~Mesh()
{
    //glDeleteVertexArrays(1, &m_VAO);
}


// TODO: colour in case something is missing a texture
void Mesh::Draw(Shader& shader)
{
    // TODO: can use these as uniform values to say how many of each textures we have (if zero, use a colour value instead of a sample)
    unsigned int diffuseNum = 0;
    unsigned int specularNum = 0;

    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        std::string name;

        switch (m_Textures[i]->m_Type)
        {
        case TextureType::Diffuse:
            name = "textureDiffuse" + std::to_string(++diffuseNum);
            break;
        case TextureType::Specular:
            name = "textureSpecular" + std::to_string(++specularNum);
            break;
        }

        shader.SetUniform("material." + name, (int)i);

        Texture::Activate(i);
        // sequentially bind textures to a location (this should be managed by some manager class eventually
        //                                               since we have limited slots and possibly many textures)
        Texture::Bind(m_Textures[i]);
    }
    Texture::Activate(0);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // reset active texture
}

void Mesh::Init()
{
    // opengl buffer bindings

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
