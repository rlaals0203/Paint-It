#include "pch.h"
#include "MoveComponent.h"
#include "Object.h"
#include "Ease.h"

MoveComponent::MoveComponent() : m_start{}
    , m_target{}
    , m_duration(1.f)
    , m_t(0.f)
    , m_isMoving(false)
    , m_owner(nullptr)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Init()
{
}

void MoveComponent::LateUpdate()
{
    if (!m_isMoving)
        return;

    m_t += fDT / m_duration;
    if (m_t >= 1.f)
        m_t = 1.f;

    Vec2 pos = EaseLerp(m_start, m_target, m_t, m_easeFunc);
    m_owner->SetPos(pos);

    if (m_t >= 1.f) {
        m_isMoving = false;
    }
}

void MoveComponent::Render(HDC _hdc)
{
}

void MoveComponent::SetMove(Vec2 start, Vec2 target, float duration, float(*_ease)(float))
{
    if(m_owner == nullptr)
        m_owner = GetOwner();

    m_start = start;
    m_target = target;
    m_duration = duration;
    m_isMoving = true;
    m_easeFunc = _ease;
    m_t = 0.f;
}
