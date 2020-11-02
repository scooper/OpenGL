#include "ModelLoadingLayer.h"
#include <glad/glad.h>
#include <imgui.h>
#include <stdio.h>

ModelLoadingLayer::ModelLoadingLayer(GLFWwindow* window) : Layer(window, "Model Loading")
{
    
}

ModelLoadingLayer::~ModelLoadingLayer()
{
}

void ModelLoadingLayer::OnActivate()
{
    m_ObjectShader = new Shader("D:/Projects/OpenGL/OpenGL/res/ModelLoading/vertex.shader", "D:/Projects/OpenGL/OpenGL/res/ModelLoading/fragment.shader");
    m_LightSourceShader = new Shader("D:/Projects/OpenGL/OpenGL/res/LightingTutorial/LightSourceVertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/LightSourceFragmentShader.glsl");
    m_Model = new Model("D:/Projects/OpenGL/OpenGL/res/ModelLoading/BackpackModel/backpack.obj");

    int width, height;

    glfwGetWindowSize(m_Window, &width, &height);
    m_Camera = new FlyCamera(ProjectionParameters{ width, height, CameraProjection::PERSPECTIVE }, glm::vec3(0.0f, 0.0f, 3.0f));
    m_LastX = width / 2;
    m_LastY = height / 2;

    m_ObjectShader->Use();
    m_ObjectShader->SetUniform("Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_ObjectShader->SetUniform("nPointLights", 0);
    m_ObjectShader->SetUniform("dirLight.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_ObjectShader->SetUniform("dirLight.Direction", m_LightDir);
    m_ObjectShader->SetUniform("material.Shininess", 31.0f);


}

void ModelLoadingLayer::OnDeactivate()
{
    delete m_Model;
    delete m_ObjectShader;
    delete m_LightSourceShader;
    delete m_Camera;

    Shader::Reset();

    glBindVertexArray(0);
}

void ModelLoadingLayer::OnMouseEvent(double xpos, double ypos)
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

void ModelLoadingLayer::OnWindowResize(int width, int height)
{
    m_Camera->UpdateProjectionMatrix(width, height);
}

void ModelLoadingLayer::ProcessKeyEvent()
{
    // mouse mode on or off
    if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
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

void ModelLoadingLayer::Update(float deltaTime)
{
    m_DeltaTime = deltaTime;

    ProcessKeyEvent();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::mat4 vp = m_Camera->GetViewProjectionMatrix();
    glm::mat4 model = glm::mat4(1.0);

    glm::mat4 mvp = vp * model;

    m_ObjectShader->Use();

    m_ObjectShader->SetUniform("viewPos", m_Camera->m_Position);

    m_ObjectShader->SetUniform<glm::mat4&>("modelMatrix", model);
    m_ObjectShader->SetUniform<glm::mat4&>("mvp", mvp);

    m_Model->Draw(*m_ObjectShader);

    // not sure if needed
    //Texture::Unbind(GL_TEXTURE_2D);

    glBindVertexArray(0);


}

void ModelLoadingLayer::ImGuiDisplay()
{
    ImGui::Text("Press the middle mouse button to use mouse controls for the camera and 'Esc' to exit mouse controls");
}


