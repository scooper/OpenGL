#include "FlyCamera.h"

FlyCamera::FlyCamera(ProjectionParameters projectionParams, glm::vec3 startPos, glm::vec3 upPos, float pitch, float yaw) :
    m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Speed(SPEED), m_Sensitivity(SENSITIVITY)
{
    m_Pitch = pitch;
    m_Yaw = yaw;
    m_WorldUp = upPos;
    m_Position = startPos;
    m_Type = projectionParams.type;

    UpdateCameraVectors();

    UpdateProjectionMatrix(projectionParams.w, projectionParams.h);
    
}

FlyCamera::~FlyCamera()
{

}

void FlyCamera::MouseInput(float xoffset, float yoffset)
{
    xoffset *= m_Sensitivity;
    yoffset *= m_Sensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;


    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    UpdateCameraVectors();
}

void FlyCamera::KeyInput(TranslateDirection direction, float deltaTime)
{
    float velocity = m_Speed * deltaTime;
    if(direction == TranslateDirection::FORWARDS)
        m_Position += m_Front * velocity;
    if(direction == TranslateDirection::BACKWARDS)
        m_Position -= m_Front * velocity;
    if(direction == TranslateDirection::LEFT)
        m_Position -= m_Right * velocity;
    if(direction == TranslateDirection::RIGHT)
        m_Position += m_Right * velocity;

    UpdateCameraVectors();
}

void FlyCamera::UpdateProjectionMatrix(int screenWidth, int screenHeight)
{
    switch (m_Type)
    {
    case CameraProjection::ORTHOGRAPHIC:
        m_Projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, 0.1f, 100.0f);
        break;
    case CameraProjection::PERSPECTIVE:
    default:
        m_Projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        break;
    }

    UpdateViewProjectionMatrix();
}

void FlyCamera::UpdateCameraVectors()
{

    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));

    UpdateViewProjectionMatrix();
}

void FlyCamera::UpdateViewProjectionMatrix()
{
    m_ViewProjectionMatrix = m_Projection * glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}
