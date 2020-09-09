#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float PITCH = 0.0f;
const float YAW = -90.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.2f;

enum class TranslateDirection
{
    FORWARDS,
    BACKWARDS,
    LEFT,
    RIGHT
};

enum class CameraProjection
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

struct ProjectionParameters
{
    int w;
    int h;
    CameraProjection type;
};

class FlyCamera
{
public:
    FlyCamera(ProjectionParameters projectionParams, glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 upPos = glm::vec3(0.0f, 1.0f, 0.0f), float pitch = PITCH, float yaw = YAW);
    ~FlyCamera();

    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    glm::mat4 m_ViewProjectionMatrix;

    float m_Pitch;
    float m_Yaw;
    float m_Speed;
    float m_Sensitivity;

    CameraProjection m_Type;


    void MouseInput(float xoffset, float yoffset);
    void KeyInput(TranslateDirection direction, float deltaTime);

    glm::mat4 GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

    void UpdateProjectionMatrix(int screenWidth, int screenHeight);

private:
    glm::mat4 m_Projection;
    void UpdateCameraVectors();
    void UpdateViewProjectionMatrix();
};