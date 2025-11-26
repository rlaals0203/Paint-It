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
    if (!m_isMoving) return;

    m_t += fDT / m_duration;
    if (m_t >= 1.f) m_t = 1.f;

    Vec2 pos = EaseLerp(m_start, m_target, m_t, m_easeFunc);
    m_owner->SetPos(pos);

    if (m_t >= 1.f)
        m_isMoving = false;
}

void MoveComponent::Render(HDC _hdc) {}

void MoveComponent::StartMove(Vec2 _target, bool _local, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    m_start = m_owner->GetPos();
    m_target = _target;
    m_duration = _duration;
    m_easeFunc = _ease;
    m_t = 0.f;
    m_isMoving = true;
    m_localMove = _local;
}

void MoveComponent::DOMove(Vec2 _target, float _duration, float(*_ease)(float))
{
    StartMove(_target, false, _duration, _ease);
}

void MoveComponent::DOMoveX(float _target, float _duration, float(*_ease)(float))
{
    Vec2 target = { _target, m_owner->GetPos().y };
    StartMove(target, false, _duration, _ease);
}

void MoveComponent::DOMoveY(float _target, float _duration, float(*_ease)(float))
{
    Vec2 target = { m_owner->GetPos().x, _target };
    StartMove(target, false, _duration, _ease);
}

void MoveComponent::DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    Vec2 current = m_owner->GetPos();
    Vec2 target = current + _target;
    StartMove(target, false, _duration, _ease);
}

void MoveComponent::DOLocalMoveX(float _target, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    Vec2 current = m_owner->GetPos();
    Vec2 target = { current.x + _target, current.y };
    StartMove(target, false, _duration, _ease);
}

void MoveComponent::DOLocalMoveY(float _target, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    Vec2 current = m_owner->GetPos();
    Vec2 target = { current.x, current.y + _target };
    StartMove(target, false, _duration, _ease);
}