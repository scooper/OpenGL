#include "Layers/Layer.h";
#include "Util/Shader.h"
#include "Util/Texture.h"
#include "Util/Camera/FlyCamera.h"
#include "Util/Model/Model.h"

class AdvancedLayer : public Layer
{
public:
    AdvancedLayer(GLFWwindow* window);
    ~AdvancedLayer();

    void OnActivate() override;
    void OnDeactivate() override;

    void OnMouseEvent(double xpos, double ypos) override;
    void OnWindowResize(int width, int height) override;
    void ProcessKeyEvent() override;

    void Update(float deltaTime) override;
    void ImGuiDisplay() override;

private:
    unsigned int m_BoxVAO;
    unsigned int m_QuadVAO;

    unsigned int m_FBO;
    unsigned int m_depthStencilRBO;
    unsigned int m_texColourBufferRBO;

    Shader* m_ScreenShader;
    Shader* m_FrameShader;

    Texture* m_Container;

    float m_LastX, m_LastY;

    bool m_MouseMode = false;

    FlyCamera* m_Camera;

    // identity kernel
    std::vector<float> m_Kernel =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    const std::vector<float> Kernel_Edge =
    {
        1.0f, 1.0f, 1.0f,
        1.0f, -9.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    const std::vector<float> Kernel_Blur =
    {
        1.0f / 16, 2.0f / 16, 1.0f / 16,
        2.0f / 16, 4.0f / 16, 2.0f / 16,
        1.0f / 16, 2.0f / 16, 1.0f / 16
    };

    bool m_Greyscale = false;

    static float m_CubeVertices[];
    static float m_QuadVertices[];
};