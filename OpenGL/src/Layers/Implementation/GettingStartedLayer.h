#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Layers/Layer.h"
#include "Util/Shader.h"
#include "Util/Texture.h"
#include "Util/Camera/FlyCamera.h"

class GettingStartedLayer : public Layer
{
public:
    GettingStartedLayer(GLFWwindow* window);
    ~GettingStartedLayer();

    void OnActivate() override;
    void OnDeactivate() override;
    void Update(float deltaTime) override;
    void ImGuiDisplay() override;

    void OnWindowResize(int width, int height) override;
    void OnMouseEvent(double xpos, double ypos) override;
    void ProcessKeyEvent() override;

private:
    Shader* m_Shader = nullptr;
    Texture* m_Texture1 = nullptr;
    Texture* m_Texture2 = nullptr;

    FlyCamera* m_Camera = nullptr;
    
    // last mouse positions
    float m_LastX, m_LastY;

    bool m_MouseMode = false;

    unsigned int m_VAO;
};

