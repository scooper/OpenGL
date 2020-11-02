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

    m_Shader = new Shader("D:/Projects/OpenGL/OpenGL/res/GettingStarted/VertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/GettingStarted/FragmentShader.glsl");
    m_Texture1 = Texture::Create(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/GettingStarted/wall.jpg", true);
    m_Texture2 = Texture::Create(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/GettingStarted/awesomeface.png", true);

    int width, height;

    glfwGetWindowSize(m_Window, &width, &height);

    m_Camera = new FlyCamera(ProjectionParameters{width, height, CameraProjection::PERSPECTIVE});

    m_LastX = width / 2;
    m_LastY = height / 2;

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
    // free opengl resources - so other layers can use them
    delete m_Shader;
    glDeleteVertexArrays(1, &m_VAO);

    Shader::Reset();
    glBindVertexArray(0);

    delete m_Camera;
}

void GettingStartedLayer::Update(float deltaTime)
{
    // keep track of deltatime
    m_DeltaTime = deltaTime;

    // dont process keys if window is focused, we may need them for text input
    if(!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
        ProcessKeyEvent();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Texture::Activate(0);
    Texture::Bind(m_Texture1);
    Texture::Activate(1);
    Texture::Bind(m_Texture2);

    // use shader
    m_Shader->Use();

    glBindVertexArray(m_VAO);

    m_Shader->SetUniform("texture1", 0);
    m_Shader->SetUniform("texture2", 1);
    m_Shader->SetUniform("mixValue", 0.2f);

    // gen cubes
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        // calculate model view projection matrix to pass to shader
        glm::mat4 mvp = m_Camera->GetViewProjectionMatrix() * model;
        
        m_Shader->SetUniform<glm::mat4&>("mvp", mvp);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}

void GettingStartedLayer::ImGuiDisplay()
{
    ImGui::Text("The learnopengl.com Getting Started tutorial, converted to my Layer format.\n");
    ImGui::Text("Press 'M' to use mouse controls for the camera and 'Esc' to exit mouse controls");
    ImGui::SliderFloat("Camera Speed", &m_Camera->m_Speed, 2.0f, 50.0f, "%.1f");
    ImGui::SliderFloat("Camera Sensitivity", &m_Camera->m_Sensitivity, 0.1f, 1.0f, "%.2f");
}

void GettingStartedLayer::OnWindowResize(int width, int height)
{
    m_Camera->UpdateProjectionMatrix(width, height);
}

void GettingStartedLayer::OnMouseEvent(double xpos, double ypos)
{
    if (m_MouseMode)
    {
        float xoffset = xpos - m_LastX;
        float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top

        m_Camera->MouseInput(xoffset, yoffset);
    }

    m_LastX = xpos;
    m_LastY = ypos;
}


void GettingStartedLayer::ProcessKeyEvent()
{
    // mouse mode on or off
    if (glfwGetKey(m_Window, GLFW_KEY_M) == GLFW_PRESS)
    {
        m_MouseMode = true;
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_MouseMode = false;
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera->KeyInput(TranslateDirection::FORWARDS, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->KeyInput(TranslateDirection::BACKWARDS, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->KeyInput(TranslateDirection::LEFT, m_DeltaTime);
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->KeyInput(TranslateDirection::RIGHT, m_DeltaTime);

}