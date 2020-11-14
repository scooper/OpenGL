#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>

#include "Util/Logger.h"
#include "Util/ErrorHandling.h"

#include "Layers/Layer.h"
#include "Layers/Layers.h"
#include "Layers/Implementation/TestLayer.h"
#include "Layers/Implementation/GettingStartedLayer.h"
#include "Layers/Implementation/LightingTutorialLayer.h"
#include "Layers/Implementation/ModelLoadingLayer.h"
#include "Layers/Implementation/AdvancedLayer.h"

// to keep track of frame time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Layers layers;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays
    Layer* activeLayer = layers.GetActiveLayer();
    if (activeLayer)
        activeLayer->OnWindowResize(width, height);
    glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Layer* activeLayer = layers.GetActiveLayer();
    if (activeLayer)
        activeLayer->OnMouseEvent(xpos, ypos);
}

// NOTE: this isnt really an amazing idea if you want game-like controls, doesn't really work
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Layer* activeLayer = layers.GetActiveLayer();
    if (activeLayer)
        activeLayer->OnKeyEvent(key, scancode, action, mods);
}

GLFWwindow* OpenGLInit(int width, int height)
{

    Assimp::Importer importer;

    GLFWwindow* window;

    LOG_INFO("Initialising OpenGL");

    /* Initialize the library */
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // request debug context (should be some sort of debug/release defines to sort this
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetKeyCallback(window, KeyCallback);

    glfwSwapInterval(1);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        LOG_ERROR("Error Loading GLAD");
        return nullptr;
    }

    // debug for error handling
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        // initialize debug output 
        ErrorHandling::GLErrorMessageInit();
    }

    std::stringstream verss;
    verss << "OpenGL Info: " << glGetString(GL_VERSION);
    LOG_INFO(verss.str());

    return window;
}

void ImGuiInit(GLFWwindow* window)
{
    // IMGUI VERSION SETUP
    // --------------------------------------------------
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    return;
}

int main(void)
{
    // initialise logger
    Logger::Init();
    int width = 800;
    int height = 600;
   

    GLFWwindow* window = OpenGLInit(800, 600);

    if (window == nullptr)
    {
        return -1;
    }
    
    ImGuiInit(window);

    layers.Add(new TestLayer(window));
    layers.Add(new GettingStartedLayer(window));
    layers.Add(new LightingTutorialLayer(window));
    layers.Add(new ModelLoadingLayer(window));
    layers.Add(new AdvancedLayer(window));

    //layers.SetActiveLayer(*layers.begin());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();


        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto activeLayer = layers.GetActiveLayer();
        if (activeLayer != nullptr)
        {
            float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
            activeLayer->Update(deltaTime);
            ImGui::Begin(activeLayer->m_LayerName.c_str());
            activeLayer->ImGuiDisplay();
            //test
            //          
            if (ImGui::Button("Back To Menu"))
                layers.SetActiveLayer(nullptr);
            ImGui::End();
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            ImGui::Begin("Menu");
            //  imgui menu
            for (Layer* layer : layers)
            {
                if (ImGui::Button(layer->m_LayerName.c_str()))
                    layers.SetActiveLayer(layer);
            }
            ImGui::End();
        }
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    
    glfwTerminate();
    return 0;
}

