#include "Texture.h"
#include <sstream>
#include <string>
#include "Logger.h"

// TODO: make a texture manager which keeps track of all loaded textures
TextureManager* TextureManager::m_Instance = 0;

Texture::Texture(GLenum target, const char* filepath, bool flip, TextureType type)
{

    m_Type = type;
    m_Target = target;
    m_Filepath = std::string(filepath);
    glGenTextures(1, &m_Id);
    
    glBindTexture(target, m_Id);
    //wrapping params
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(flip);

    // image data and load
    int width, height, channels;
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);

    if (data)
    {
        std::string name(filepath);
        unsigned int channel = GL_RGB;

        if (channels == 4)
            channel = GL_RGBA;

        glTexImage2D(target, 0, GL_RGB, width, height, 0, channel, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(target);
        std::stringstream logss;
        logss << "Loaded texture (" << filepath << ")";
        LOG_INFO(logss.str());
    }
    else
    {
        LOG_ERROR("Failed to load texture");
    }

    Unbind(m_Target);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}

Texture* Texture::Create(GLenum target, const char* filepath, bool flip, TextureType type)
{
    // check if texture is already loaded with the same type
    Texture* loaded = TextureManager::Instance()->GetTexture(filepath, type);

    if (loaded == nullptr)
    {
        Texture* tex = new Texture(target, filepath, flip, type);
        TextureManager::Instance()->AddTexture(tex);
        return tex;
    }
    else
        return loaded;
}

void Texture::Bind(GLenum target, unsigned int texture)
{
    glBindTexture(target, texture);
}

void Texture::Unbind(GLenum target)
{
    glBindTexture(target, 0);
}

void Texture::Activate(int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

TextureManager::~TextureManager()
{
    for (auto value: m_LoadedTextures)
    {
        delete value.second;
    }
}

// NOTE: cant really think of a use of this right now
void TextureManager::RemoveTexture(std::string filename)
{
    //
}


Texture* TextureManager::GetTexture(std::string filepath, TextureType type)
{
    if (m_LoadedTextures.find(filepath) != m_LoadedTextures.end())
        return m_LoadedTextures[filepath];
    else
        return nullptr;
}
