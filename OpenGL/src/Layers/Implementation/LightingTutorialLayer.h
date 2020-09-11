#pragma once

#include "Layers/Layer.h"
#include "Util/Shader.h"
#include "Util/Texture.h"
#include "Util/Camera/FlyCamera.h"

class LightingTutorialLayer : public Layer
{
public:
    LightingTutorialLayer(GLFWwindow* window);
    ~LightingTutorialLayer();

    void OnActivate() override;
    void OnDeactivate() override;
    void Update(float deltaTime) override;
    void ImGuiDisplay() override;

    void OnWindowResize(int width, int height) override;
    void OnMouseEvent(double xpos, double ypos) override;
    void ProcessKeyEvent() override;

private:
    unsigned int m_LightSourceVAO;
    unsigned int m_BoxVAO;

    float m_LastX, m_LastY;

    bool m_MouseMode = false;

    glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    Shader* m_ObjectShader;
    Shader* m_LightSourceShader;
    Texture* m_BoxDiffuse;
    Texture* m_BoxSpecular;

    FlyCamera* m_Camera;

    static float m_Vertices[];

};