#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>

enum TexLocation
{
    Location0, Location1, Location2, Location3, Location4, Location5, Location6,
    Location7, Location8, Location9, Location10, Location11, Location12, Location13,
    Location14, Location15,
    LocationMax = Location15
};

class Texture
{
public:
    unsigned int m_Id;
    GLenum m_Target;
    TexLocation m_Location;

    Texture(GLenum target, const char* filename, bool flip, TexLocation location);
    ~Texture();

    static void Bind(GLenum target, unsigned int texture, TexLocation location);
    void Bind() { this->Activate(m_Location); this->Bind(m_Target, m_Id, m_Location); }

    static void Unbind(GLenum target);
    void Unbind() { this->Unbind(m_Target); }

    static void Activate(TexLocation location);
};

