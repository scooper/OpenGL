#include "LightingTutorialLayer.h"
#include <glad/glad.h>
#include <imgui.h>

float LightingTutorialLayer::m_Vertices[] = {
    // positions          // normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

LightingTutorialLayer::LightingTutorialLayer(GLFWwindow *window) : Layer(window, "Lighting Layer")
{
    
}

LightingTutorialLayer::~LightingTutorialLayer()
{
}

void LightingTutorialLayer::OnActivate()
{

    m_ObjectShader = new Shader("D:/Projects/OpenGL/OpenGL/res/LightingTutorial/VertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/FragmentShader.glsl");
    m_LightSourceShader = new Shader("D:/Projects/OpenGL/OpenGL/res/LightingTutorial/LightSourceVertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/LightSourceFragmentShader.glsl");

    int width, height;

    glfwGetWindowSize(m_Window, &width, &height);
    m_Camera = new FlyCamera(ProjectionParameters{ width, height, CameraProjection::PERSPECTIVE }, glm::vec3(0.0f, 0.0f, 3.0f));

    m_LastX = width / 2;
    m_LastY = height / 2;

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_BoxVAO);
    glBindVertexArray(m_BoxVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glGenVertexArrays(1, &m_LightSourceVAO);
    glBindVertexArray(m_LightSourceVAO);
    // bind VBO to light source VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_ObjectShader->Use();
    // set material for cube
    m_ObjectShader->SetUniform("material.Ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_ObjectShader->SetUniform("material.Diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_ObjectShader->SetUniform("material.Specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_ObjectShader->SetUniform("material.Shininess", 32.0f);

    m_ObjectShader->SetUniform("light.Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_ObjectShader->SetUniform("light.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_ObjectShader->SetUniform("light.Specular", glm::vec3(1.0f, 1.0f, 1.0f));

}

void LightingTutorialLayer::OnDeactivate()
{
    delete m_ObjectShader;
    delete m_LightSourceShader;

    Shader::Reset();

    glDeleteVertexArrays(1, &m_BoxVAO);
    glDeleteVertexArrays(1, &m_LightSourceVAO);

    glBindVertexArray(0);

}

void LightingTutorialLayer::Update(float deltaTime)
{
    m_DeltaTime = deltaTime;

    ProcessKeyEvent();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 vp = m_Camera->GetViewProjectionMatrix();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 objectMVP = vp * model;

    m_ObjectShader->Use();
    glBindVertexArray(m_BoxVAO);
    m_ObjectShader->SetUniform("light.Position", m_LightPos);
    m_ObjectShader->SetUniform("viewPos", m_Camera->m_Position);
    m_ObjectShader->SetUniform<glm::mat4&>("mvp", objectMVP);
    m_ObjectShader->SetUniform<glm::mat4&>("modelMatrix", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    m_LightSourceShader->Use();
    glBindVertexArray(m_LightSourceVAO);
    model = glm::translate(model, m_LightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    glm::mat4 lightMVP = vp * model;
    m_LightSourceShader->SetUniform<glm::mat4&>("mvp", lightMVP);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

}

void LightingTutorialLayer::ImGuiDisplay()
{
    ImGui::Text("Press 'M' to use mouse controls for the camera and 'Esc' to exit mouse controls");
    ImGui::SliderFloat3("Light Position", &m_LightPos[0], -10.0f, 10.0f, "%.2f");
}

void LightingTutorialLayer::OnWindowResize(int width, int height)
{
    m_Camera->UpdateProjectionMatrix(width, height);
}

void LightingTutorialLayer::OnMouseEvent(double xpos, double ypos)
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

void LightingTutorialLayer::ProcessKeyEvent()
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
