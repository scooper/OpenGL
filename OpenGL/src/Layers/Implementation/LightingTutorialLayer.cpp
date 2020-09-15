#include "LightingTutorialLayer.h"
#include <glad/glad.h>
#include <imgui.h>
#include <stdio.h>

float LightingTutorialLayer::m_Vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

    m_BoxDiffuse = new Texture(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/container-diffuse-map.png", true, TexLocation::Location0);
    m_BoxSpecular = new Texture(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/container-specular-map.png", true, TexLocation::Location1);

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

    // container/box
    glGenVertexArrays(1, &m_BoxVAO);
    glBindVertexArray(m_BoxVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // light source
    glGenVertexArrays(1, &m_LightSourceVAO);
    glBindVertexArray(m_LightSourceVAO);
    // bind VBO to light source VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_ObjectShader->Use();
    // set material for cube
    m_ObjectShader->SetUniform("material.Diffuse", (int)m_BoxDiffuse->m_Location);
    m_ObjectShader->SetUniform("material.Specular", (int)m_BoxSpecular->m_Location);
    m_ObjectShader->SetUniform("material.Shininess", 31.0f);

   /* m_ObjectShader->SetUniform("light.Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_ObjectShader->SetUniform("light.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_ObjectShader->SetUniform("light.Specular", glm::vec3(1.0f, 1.0f, 1.0f));*/

    m_ObjectShader->SetUniform("Ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    // dirlight
    m_ObjectShader->SetUniform("dirLight.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_ObjectShader->SetUniform("dirLight.Direction", m_LightDir);

   /* m_ObjectShader->SetUniform("light.Constant", 1.0f);
    m_ObjectShader->SetUniform("light.Linear", 0.09f);
    m_ObjectShader->SetUniform("light.Quadratic", 0.032f);*/
}

void LightingTutorialLayer::OnDeactivate()
{
    delete m_BoxDiffuse;
    delete m_BoxSpecular;
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::mat4 vp = m_Camera->GetViewProjectionMatrix();

    // calculate start position of grid so that centre is the same for each N
    float startPos = -((float)m_GridNum/2);
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 startPosMat = glm::translate(model, glm::vec3(startPos, startPos, 0.0f));
    

    // bind textures
    m_BoxDiffuse->Bind();
    m_BoxSpecular->Bind();

    // box shader
    m_ObjectShader->Use();
    glBindVertexArray(m_BoxVAO);
    //m_ObjectShader->SetUniform("light.Position", m_LightPos);
    m_ObjectShader->SetUniform("viewPos", m_Camera->m_Position);

    m_ObjectShader->SetUniform("nPointLights", (int)m_PointLights.size());
    // make a grid of cubes (this is kind of fucked with the triple for loop -> use UBO in future; and instanced/batch rendering)
    for (int i = 0; i < m_GridNum; i++)
    {
        for (int j = 0; j < m_GridNum; j++)
        {
            for (int li = 0; li < m_PointLights.size(); li++)
            {
                PointLight light = m_PointLights[li];
                auto index = std::to_string(li);
                m_ObjectShader->SetUniform("pointLights[" + index + "].Position", light.Position);
                m_ObjectShader->SetUniform("pointLights[" + index + "].Diffuse", light.Diffuse);
                m_ObjectShader->SetUniform("pointLights[" + index + "].Constant", light.Constant);
                m_ObjectShader->SetUniform("pointLights[" + index + "].Linear", light.Linear);
                m_ObjectShader->SetUniform("pointLights[" + index + "].Quadratic", light.Quadratic);
            }

            model = glm::translate(startPosMat, glm::vec3((float)j, (float)i, 0.0f));
            glm::mat4 objectMVP = vp * model;
            m_ObjectShader->SetUniform<glm::mat4&>("modelMatrix", model);
            m_ObjectShader->SetUniform<glm::mat4&>("mvp", objectMVP);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }   
    }

    // light shader
    m_LightSourceShader->Use();
    glBindVertexArray(m_LightSourceVAO);
    for (PointLight light : m_PointLights)
    {
        model = glm::mat4(1.0);
        // transform box
        model = glm::translate(model, light.Position);
        model = glm::scale(model, glm::vec3(0.2f));

        glm::mat4 lightMVP = vp * model;
        m_LightSourceShader->SetUniform<glm::mat4&>("mvp", lightMVP);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);

}

void LightingTutorialLayer::ImGuiDisplay()
{
    ImGui::Text("Press the middle mouse button to use mouse controls for the camera and 'Esc' to exit mouse controls");
    //ImGui::SliderFloat3("Light Position", &m_LightPos[0], -10.0f, 10.0f, "%.2f");
    ImGui::SliderInt("Grid Number", &m_GridNum, 1, 6);
    ImGui::Text("Number of Point Lights: %d", m_PointLights.size());
    if (ImGui::Button("Remove Point Light"))
        OnLightNumDecrease();
    if (ImGui::Button("Add Point Light"))
        OnLightNumIncrease();
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

void LightingTutorialLayer::OnLightNumIncrease()
{
    if (m_PointLights.size() == 32)
        return;

    glm::vec3 position = glm::vec3(rand() % 21 + (-10), rand() % 21 + (-10), rand() % 21 + (-10));
    glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);

    // default attuention params for now
    m_PointLights.push_back({ position, diffuse, 1.0f, 0.09f, 0.032f });

}

void LightingTutorialLayer::OnLightNumDecrease()
{
    if (m_PointLights.size() == 0)
        return;

    m_PointLights.pop_back();
}
