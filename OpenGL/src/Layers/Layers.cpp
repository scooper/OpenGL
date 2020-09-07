#include "Layers.h"

Layers::Layers()
{
}

Layers::~Layers()
{
    for (Layer* layer : m_Layers)
    {
        delete layer;
    }
}

void Layers::Add(Layer* layer)
{
    m_Layers.push_back(layer);
}

void Layers::Remove(Layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it >= m_Layers.begin())
    {
        m_Layers.erase(it);
    }
}

void Layers::SetActiveLayer(Layer* layer)
{
    if (m_ActiveLayer)
    {
        m_ActiveLayer->OnDeactivate();
    }

    if(!layer)
    {
        m_ActiveLayer = nullptr;
        return;
    }

    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    m_ActiveLayer = *it;

    m_ActiveLayer->OnActivate();
}
