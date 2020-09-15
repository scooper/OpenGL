#pragma once

#include "Layers/Layer.h"
#include "Util/Shader.h"
#include "Util/Texture.h"
#include "Util/Camera/FlyCamera.h"

#include <vector>

struct PointLight
{
    glm::vec3 Position;
    glm::vec3 Diffuse;
    float Constant;
    float Linear;
    float Quadratic;
};

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

    int m_GridNum = 3;
    std::vector<PointLight> m_PointLights;

    float m_LastX, m_LastY;

    bool m_MouseMode = false;

    //glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    glm::vec3 m_LightDir = glm::vec3(-2.0f, -1.0f, -0.3f);

    Shader* m_ObjectShader;
    Shader* m_LightSourceShader;
    Texture* m_BoxDiffuse;
    Texture* m_BoxSpecular;

    FlyCamera* m_Camera;

    static float m_Vertices[];

    void OnLightNumIncrease();
    void OnLightNumDecrease();

};