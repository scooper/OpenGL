#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <unordered_map>

class Layer
{
public:
    Layer(GLFWwindow* window, std::string name) { m_Window = window; m_LayerName = name; }
    virtual ~Layer() {}

    virtual void OnActivate() {}
    virtual void OnDeactivate() {}

    virtual void OnMouseEvent(double xpos, double ypos) {}
    virtual void OnKeyEvent(int key, int scancode, int action, int mods) {}
    virtual void OnWindowResize(int width, int height) {}
    virtual void ProcessKeyEvent() {}

    virtual void Update(float deltaTime) {}
    virtual void ImGuiDisplay() {}


public:
    std::string m_LayerName;
    GLFWwindow* m_Window;
    float m_DeltaTime;
};

