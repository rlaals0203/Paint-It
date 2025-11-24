#include "pch.h"
#include "ImpulseManager.h"

void ImpulseManager::Update()
{
    if (m_isShaking)
    {
        int x = (rand() % 100 - 50) * m_intensity / 50;
        int y = (rand() % 100 - 50) * m_intensity / 50;
        m_offset = { x, y };
        m_duration -= fDT;
        if (m_duration < 0.f)
        {
            m_isShaking = false;
            m_offset = { 0, 0 };
        }
    }
}

void ImpulseManager::ApplyImpulse(float _intensity, float _duration)
{
    m_isShaking = true;
    m_intensity = _intensity;
    m_duration = _duration;
}
