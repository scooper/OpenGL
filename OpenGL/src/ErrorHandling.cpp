#include "ErrorHandling.h"
#include <sstream>
#include "Logger.h"

void APIENTRY ErrorMessageCallback(GLenum source,
    GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::stringstream ss;
    ss << "OpenGL Debug message (" << id << "): " << message;

    // break on error
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        LOG_ERROR(ss.str());
        ASSERT(false);
        break;
    default:
        LOG_INFO(ss.str());
    }
}

void ErrorHandling::GLErrorMessageInit()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(ErrorMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}