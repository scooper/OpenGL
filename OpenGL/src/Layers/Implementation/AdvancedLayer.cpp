#include "AdvancedLayer.h"
#include "Util/Logger.h"
#include <string>
#include <imgui.h>

float AdvancedLayer::m_CubeVertices[] = {
    // positions          // texture coords
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

float AdvancedLayer::m_QuadVertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
};

AdvancedLayer::AdvancedLayer(GLFWwindow* window) : Layer(window, "Advanced OpenGL")
{
}

AdvancedLayer::~AdvancedLayer()
{
}

void AdvancedLayer::OnActivate()
{

    m_FrameShader = new Shader("D:/Projects/OpenGL/OpenGL/res/Advanced/FramebufferShaders/framebuffer_vs.glsl",
        "D:/Projects/OpenGL/OpenGL/res/Advanced/FramebufferShaders/framebuffer_fs.glsl");

    m_ScreenShader = new Shader("D:/Projects/OpenGL/OpenGL/res/Advanced/FramebufferShaders/screen_vs.glsl",
        "D:/Projects/OpenGL/OpenGL/res/Advanced/FramebufferShaders/screen_fs.glsl");

    int width, height;

    glfwGetWindowSize(m_Window, &width, &height);
    m_Camera = new FlyCamera(ProjectionParameters{ width, height, CameraProjection::PERSPECTIVE }, glm::vec3(0.0f, 0.0f, 3.0f));
    m_LastX = width / 2;
    m_LastY = height / 2;


    m_Container = Texture::Create(GL_TEXTURE_2D, "D:/Projects/OpenGL/OpenGL/res/LightingTutorial/container-diffuse-map.png", true);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_CubeVertices), m_CubeVertices, GL_STATIC_DRAW);

    // container/box
    glGenVertexArrays(1, &m_BoxVAO);
    glBindVertexArray(m_BoxVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // screen quad
    unsigned int quadVBO;
    glGenVertexArrays(1, &m_QuadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(m_QuadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_QuadVertices), &m_QuadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // framebuffer
    glGenFramebuffers(1, &m_FBO);

    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glGenTextures(1, &m_texColourBufferRBO);
    glBindTexture(GL_TEXTURE_2D, m_texColourBufferRBO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColourBufferRBO, 0);

    glGenRenderbuffers(1, &m_depthStencilRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOG_ERROR("Framebuffer is not complete");

    // TODO: complete the framebuffers tutorial

}

void AdvancedLayer::OnDeactivate()
{
    glDeleteVertexArrays(1, &m_BoxVAO);
    glDeleteFramebuffers(1, &m_FBO);
    delete m_ScreenShader;
    delete m_FrameShader;
    delete m_Camera;

    Shader::Reset();

    glBindVertexArray(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AdvancedLayer::OnMouseEvent(double xpos, double ypos)
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

void AdvancedLayer::OnWindowResize(int width, int height)
{

    // resize framebuffer texture buffer and render buffer object (stencil and depth)
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glBindTexture(GL_TEXTURE_2D, m_texColourBufferRBO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // update projection matrix
    m_Camera->UpdateProjectionMatrix(width, height);

}

void AdvancedLayer::ProcessKeyEvent()
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

void AdvancedLayer::Update(float deltaTime)
{
    m_DeltaTime = deltaTime;

    ProcessKeyEvent();

    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_FrameShader->Use();
    Texture::Activate(0);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 vp = m_Camera->GetViewProjectionMatrix();
    glm::mat4 mvp = vp * model;
    m_FrameShader->SetUniform<glm::mat4&>("mvp", mvp);

    glBindVertexArray(m_BoxVAO);
    Texture::Bind(m_Container);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

    m_ScreenShader->Use();
    for(int i = 0; i < 9; i++)
    {
        auto index = std::to_string(i);
        m_ScreenShader->SetUniform("kernel[" + index + "]", m_Kernel[i]);
    };

    m_ScreenShader->SetUniform("greyscale", m_Greyscale);

    glBindVertexArray(m_QuadVAO);
    glBindTexture(GL_TEXTURE_2D, m_texColourBufferRBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void AdvancedLayer::ImGuiDisplay()
{

    ImGui::Text("Kernel Array");
    ImGui::Columns(3, NULL);

    ImGui::Separator();
    // kernel controls
    float* ptr = &m_Kernel[0];
    for (int i = 0; i < m_Kernel.size(); i++)
    {
        // we want the kernel to be displayed from left to right
        if (i != 0)
            ImGui::NextColumn();
        ImGui::InputFloat(("i=" + std::to_string(i)).c_str(), ptr, 0.1f, 0.5f, "%.1f");
        ptr++;
    }

    ImGui::Separator();
    ImGui::Columns(1);
    ImGui::Text("Preset Kernels");
    ImGui::NewLine();
    ImGui::SameLine();
    // buttons to load a preset kernel that demonstrates some concept
    if (ImGui::Button("Edge Kernel"))
        m_Kernel = Kernel_Edge;
    ImGui::SameLine();
    if (ImGui::Button("Blur Kernel"))
        m_Kernel = Kernel_Blur;

    ImGui::Separator();
    ImGui::Text("Options");
    ImGui::Checkbox("Greyscale", &m_Greyscale);
}
