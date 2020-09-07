#include "Texture.h"
#include <sstream>
#include <string>
#include "Logger.h"

Texture::Texture(GLenum target, const char* filename, bool flip, TexLocation location)
{
    if (location > TexLocation::LocationMax)
    {
        LOG_ERROR("Texture Location too large. Texture locations are only supported from 0 to 15.");
    }

    m_Target = target;
    m_Location = location;
    glGenTextures(1, &m_Id);
    
    glActiveTexture(GL_TEXTURE0 + m_Location);
    glBindTexture(target, m_Id);
    //wrapping params
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(flip);

    // image data and load
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (data)
    {
        std::string name(filename);
        
        // is it a PNG, then alpha channel
        if (name.find(".png") != std::string::npos)
        {
            glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(target);
        std::stringstream logss;
        logss << "Loaded texture (" << filename << ")";
        LOG_INFO(logss.str());
    }
    else
    {
        LOG_ERROR("Failed to load texture");
    }

    Unbind();
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}

void Texture::Bind(GLenum target, unsigned int texture, TexLocation location)
{
    Activate(location);
    glBindTexture(target, texture);
}

void Texture::Unbind(GLenum target)
{
    glBindTexture(target, 0);
}

void Texture::Activate(TexLocation location)
{
    glActiveTexture(GL_TEXTURE0 + location);
}
