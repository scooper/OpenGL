#include "TestLayer.h"
#include "Util/Logger.h"
#include <sstream>
#include <imgui.h>

// maybe this will take a new Window object which gives us more data and control
TestLayer::TestLayer(GLFWwindow* window) : Layer(window, "Test Layer")
{
    m_ClearColour = glm::vec4(0.5f, 0.3f, 0.2f, 1.0f);
}

TestLayer::~TestLayer()
{
}

void TestLayer::OnActivate()
{
    std::stringstream logss;
    logss << "Loaded layer: " << m_LayerName;
    LOG_INFO(logss.str());
    m_Shader = new Shader("D:/Projects/OpenGL/OpenGL/res/shaders/VertexShader.glsl", "D:/Projects/OpenGL/OpenGL/res/shaders/FragmentShader.glsl");
    
    // do stuff when it's added to the list of layers
    // e.g init camera/matrices(mvp)/load shader/etc
}

void TestLayer::OnDeactivate()
{
    std::stringstream logss;
    logss << "Unload layer: " << m_LayerName;
    LOG_INFO(logss.str());
    delete m_Shader;
    Shader::Reset();
    // do stuff when it's removed from the list of layers
}

void TestLayer::Update(float deltaTime)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    glClearColor(m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, m_ClearColour.a);
}

void TestLayer::ImGuiDisplay()
{
    ImGui::ColorEdit4("Clear Colour", &m_ClearColour[0]);
}
