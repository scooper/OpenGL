#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <string>
#include <vector>
#include <unordered_map>

enum class TextureType
{
    Specular,
    Diffuse
};

class Texture
{
private:
    Texture(GLenum target, const char* filepath, bool flip, TextureType type = TextureType::Diffuse);
public:
    unsigned int m_Id;
    GLenum m_Target;
    TextureType m_Type;
    std::string m_Filename;
    std::string m_Filepath;
    
    ~Texture();
    static Texture* Create(GLenum target, const char* filepath, bool flip, TextureType type = TextureType::Diffuse);

    static void Bind(GLenum target, unsigned int texture);
    static void Bind(Texture* texture) { Bind(texture->m_Target, texture->m_Id); }

    static void Unbind(GLenum target);

    static void Activate(int slot);
};

class TextureManager
{
private:
    static TextureManager* m_Instance;

    TextureManager() {}
    ~TextureManager();
    std::unordered_map<std::string, Texture*> m_LoadedTextures;

public:
    static TextureManager* Instance()
    {
        if(!m_Instance)
            m_Instance = new TextureManager;
        return m_Instance;
    }

    void AddTexture(Texture* tex) { TextureManager::Instance()->m_LoadedTextures[tex->m_Filepath] = tex; }
    void RemoveTexture(std::string filename);
    Texture* TextureManager::GetTexture(std::string filepath, TextureType type = TextureType::Diffuse);

};


