#include "Shader.h"
#include "Logger.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    m_infoStream = std::make_unique<std::stringstream>();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::stringstream eStream;
        eStream << "Error Reading Shader File" << e.what();
        LOG_ERROR(eStream.str());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // create shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    checkShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    checkShader(fragmentShader);

    m_Id = glCreateProgram();

    glAttachShader(m_Id, vertexShader);
    glAttachShader(m_Id, fragmentShader);
    glLinkProgram(m_Id);

    checkProgram();

    // delete shaders - no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
    glDeleteProgram(m_Id);
}

bool Shader::checkShader(unsigned int& id)
{
    int success;
    char infolog[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(id, sizeof(infolog), NULL, infolog);
        *m_infoStream << "Error Compiling Shader: " << infolog;
        LOG_ERROR(m_infoStream->str());
        m_infoStream->str(std::string());
        m_infoStream->clear();
        return false;
    }

    *m_infoStream << "Shader (ID: " << id << ") Successfully Compiled!";
    LOG_INFO(m_infoStream->str());
    m_infoStream->clear();
    m_infoStream->str(std::string());

    return true;
}

bool Shader::checkProgram()
{
    int success;
    char infolog[512];

    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_Id, sizeof(infolog), NULL, infolog);
        // glGetShaderInfoLog(shaderid, 512, NULL, infolog);
        *m_infoStream << "Error Linking Shader Program: " << infolog;
        LOG_ERROR(m_infoStream->str());
        m_infoStream->str(std::string());
        m_infoStream->clear();
        return false;
    }

    *m_infoStream << "Shader Program (ID: " << m_Id << ") Successfully Linked!";
    LOG_INFO(m_infoStream->str());
    m_infoStream->str(std::string());
    m_infoStream->clear();
    return true;
}

void Shader::Use()
{
    glUseProgram(m_Id);
}

void Shader::Reset()
{
    glUseProgram(0);
}

// bool
template <>
void Shader::SetUniform<bool>(const std::string& name, bool value)
{
    glUniform1i(getUniformLocation(name), value);
}

// int
template <>
void Shader::SetUniform<int>(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

// unsigned int
template <>
void Shader::SetUniform<unsigned int>(const std::string& name, unsigned int value)
{
    glUniform1ui(getUniformLocation(name), value);
}

// float
template <>
void Shader::SetUniform<float>(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

// vec 3
template <>
void Shader::SetUniform<glm::vec3>(const std::string& name, glm::vec3 value)
{
    glUniform3f(getUniformLocation(name), value.x, value.y, value.x);
}

// vec 4
template <>
void Shader::SetUniform<glm::vec4>(const std::string& name, glm::vec4 value)
{
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

// mat 4
template <>
void Shader::SetUniform<glm::mat4&>(const std::string& name, glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
    if (m_UniformCache.find(name) != m_UniformCache.end())
    {
        return m_UniformCache[name];
    }

    int location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
    {
        std::stringstream errorStream;
        errorStream << "Uniform doesn't exist (" << name << ")";
        LOG_ERROR(errorStream.str());
    }

    m_UniformCache[name] = location;

    return location;
}