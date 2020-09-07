#pragma once

#include "Layers/Layer.h"
#include "Util/Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class TestLayer : public Layer
{
public:
    TestLayer(GLFWwindow* window);
    ~TestLayer();

    void OnActivate() override;
    void OnDeactivate() override;


    void Update(float deltaTime) override;

    void ImGuiDisplay() override;

private:
    glm::vec4 m_ClearColour;
    Shader* m_Shader = nullptr;
};

