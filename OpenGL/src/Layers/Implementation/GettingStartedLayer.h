#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Layers/Layer.h"
#include "Util/Shader.h"
#include "Util/Texture.h"

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
    void ProcessKeyEvent() override;

private:
    Shader* m_Shader = nullptr;
    Texture* m_Texture1 = nullptr;
    Texture* m_Texture2 = nullptr;

    glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 m_Projection;

    unsigned int m_VAO;
};

