#include "pch.h"
#include "ScaleComponent.h"

ScaleComponent::ScaleComponent() 
    : m_start{ 1.f, 1.f }
    , m_target{ 1.f, 1.f }
    , m_duration(1.f)
    , m_t(0.f)
    , m_isScaling(false)
    , m_easeFunc(nullptr)
    , m_owner(nullptr)
{
}

ScaleComponent::~ScaleComponent()
{
}

void ScaleComponent::Init()
{
}

void ScaleComponent::LateUpdate()
{
    if (!m_isScaling)
        return;

    m_t += fDT / m_duration;
    if (m_t >= 1.f) m_t = 1.f;

    Vec2 scale = EaseLerp(m_start, m_target, m_t, m_easeFunc);
    m_owner->SetSize(scale);

    if (m_t >= 1.f)
        m_isScaling = false;
}

void ScaleComponent::Render(HDC _hdc)
{
}

void ScaleComponent::SetSize(Vec2 _target, float _duration, float(*_ease)(float))
{
    if (!m_owner)
        m_owner = GetOwner();

    m_start = m_owner->GetSize();
    m_target = _target;
    m_duration = _duration;
    m_easeFunc = _ease;
    m_t = 0.f;
    m_isScaling = true;
}
