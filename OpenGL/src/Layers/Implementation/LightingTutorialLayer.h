#pragma once

#include "Layers/Layer.h"

class LightingTutorialLayer : public Layer
{
public:
    LightingTutorialLayer();
    ~LightingTutorialLayer();

    void OnActivate() override;
    void OnDeactivate() override;
    void Update(float deltaTime) override;
    void ImGuiDisplay() override;

    void OnWindowResize(int width, int height) override;
    void OnMouseEvent(double xpos, double ypos) override;
    void ProcessKeyEvent() override;

private:
};