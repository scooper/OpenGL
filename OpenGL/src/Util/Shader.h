#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

// for shader parsing
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>

class Shader
{
public:
    unsigned int m_Id;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use();
    static void Reset();

    template <typename T>
    void SetUniform(const std::string& name, T value);

private:
    std::unique_ptr<std::stringstream> m_infoStream;
    std::unordered_map<std::string, unsigned int> m_UniformCache;

    bool checkShader(unsigned int& id);
    bool checkProgram();
    unsigned int getUniformLocation(const std::string &name);
};