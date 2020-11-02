#pragma once

#include "Layers/Layer.h";
#include "Util/Shader.h"
#include "Util/Texture.h"
#include "Util/Camera/FlyCamera.h"
#include "Util/Model/Model.h"

class ModelLoadingLayer : public Layer
{
public:
    ModelLoadingLayer(GLFWwindow* window);
    ~ModelLoadingLayer();

    void OnActivate() override;
    void OnDeactivate() override;

    void OnMouseEvent(double xpos, double ypos) override;
    void OnWindowResize(int width, int height) override;
    void ProcessKeyEvent() override;

    void Update(float deltaTime) override;
    void ImGuiDisplay() override;

private:
    float m_LastX, m_LastY;

    bool m_MouseMode = false;
    glm::vec3 m_LightDir = glm::vec3(-2.0f, -1.0f, -0.3f);
    Shader* m_ObjectShader;
    Shader* m_LightSourceShader;
    Model* m_Model;

    FlyCamera* m_Camera;
};