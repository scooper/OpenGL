#pragma once
#include <vector>
#include "Layer.h"

class Layers
{
public:
    Layers();
    ~Layers();

    void Add(Layer* layer);
    void Remove(Layer* layer);

    void SetActiveLayer(Layer* layer);

    Layer* GetActiveLayer() { return m_ActiveLayer; }

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
    Layer* m_ActiveLayer = nullptr;
    std::vector<Layer*> m_Layers;
};

