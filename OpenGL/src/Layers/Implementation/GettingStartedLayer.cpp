#include "GettingStartedLayer.h"
#include "Util/Logger.h"

#include <imgui.h>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

GettingStartedLayer::GettingStartedLayer(GLFWwindow* window) : Layer(window, "Getting Started Layer")
{
}

GettingStartedLayer::~GettingStartedLayer()
{
}

void GettingStartedLayer::OnActivate()
{
    std::stringstream logss;
    logss << "Loaded layer: " << m_LayerName;
    LOG_INFO(logss.str());

    m_Shader = new Shader("D:/Projects/OpenGL/OpenGL/res/shaders/VertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/shaders/FragmentShader.glsl");
    m_Texture1 = new Texture(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/test_textures/wall.jpg", true, TexLocation::Location0);
    m_Texture2 = new Texture(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/test_textures/awesomeface.png", true, TexLocation::Location1);

    int width, height;

    glfwGetWindowSize(m_Window, &width, &height);
    m_Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    unsigned int VBO;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GettingStartedLayer::OnDeactivate()
{
    std::stringstream logss;
    logss << "Unload layer: " << m_LayerName;
    LOG_INFO(logss.str());

    delete m_Shader;
    delete m_Texture1;
    delete m_Texture2;
    glDeleteVertexArrays(1, &m_VAO);

    Shader::Reset();
    glBindVertexArray(0);
}

void GettingStartedLayer::Update(float deltaTime)
{
    m_DeltaTime = deltaTime;

    ProcessKeyEvent();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Texture1->Bind();
    m_Texture2->Bind();

    glm::mat4 view;
    view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

    // use shader
    m_Shader->Use();

    glBindVertexArray(m_VAO);

    m_Shader->SetUniform("texture1", (int)m_Texture1->m_Location);
    m_Shader->SetUniform("texture2", (int)m_Texture2->m_Location);
    m_Shader->SetUniform("mixValue", 0.2f);

    // gen cubes
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // calculate model view projection matrix to pass to shader
        glm::mat4 mvp = m_Projection * view * model;
        
        m_Shader->SetUniform<glm::mat4&>("mvp", mvp);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}

void GettingStartedLayer::ImGuiDisplay()
{
    
}

void GettingStartedLayer::OnWindowResize(int width, int height)
{
    m_Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}


void GettingStartedLayer::ProcessKeyEvent()
{
    const float cameraSpeed = 2.5f * m_DeltaTime;

    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_CameraPos += cameraSpeed * m_CameraFront;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_CameraPos -= cameraSpeed * m_CameraFront;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    }
}