#include "pch.h"
#include "DOTweenCompo.h"

DOTweenCompo::DOTweenCompo() : m_owner(nullptr)
    , m_moveStart({ 0,0 }), m_moveTarget({ 0,0 }), m_moveDuration(1.f)
    , m_moveT(0.f), m_isMoving(false), m_moveEase(nullptr)
    , m_scaleStart({ 1,1 }), m_scaleTarget({ 1,1 }), m_scaleDuration(1.f)
    , m_scaleT(0.f), m_isScaling(false), m_scaleEase(nullptr)
{
}

DOTweenCompo::~DOTweenCompo() {}

void DOTweenCompo::Init() { if (!m_owner) m_owner = GetOwner(); }

void DOTweenCompo::LateUpdate()
{
    float dt = fDT;

    if (m_isMoving) {
        m_moveT += dt / m_moveDuration;
        if (m_moveT >= 1.f) m_moveT = 1.f;

        Vec2 pos = EaseLerp(m_moveStart, m_moveTarget, m_moveT, m_moveEase);
        m_owner->SetPos(pos);

        if (m_moveT >= 1.f) m_isMoving = false;
    }

    if (m_isScaling) {
        m_scaleT += dt / m_scaleDuration;
        if (m_scaleT >= 1.f) m_scaleT = 1.f;

        Vec2 size = EaseLerp(m_scaleStart, m_scaleTarget, m_scaleT, m_scaleEase);
        m_owner->SetSize(size);

        if (m_scaleT >= 1.f) m_isScaling = false;
    }
}

void DOTweenCompo::Render(HDC _hdc) {}

void DOTweenCompo::DOMove(Vec2 _target, float _duration, float(*_ease)(float)) { StartMove(_target, _duration, _ease); }
void DOTweenCompo::DOMoveX(float _target, float _duration, float(*_ease)(float)) { StartMove({ _target, m_owner->GetPos().y }, _duration, _ease); }
void DOTweenCompo::DOMoveY(float _target, float _duration, float(*_ease)(float)) { StartMove({ m_owner->GetPos().x, _target }, _duration, _ease); }
void DOTweenCompo::DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float)) { StartMove(m_owner->GetPos() + _target, _duration, _ease); }
void DOTweenCompo::DOLocalMoveX(float _target, float _duration, float(*_ease)(float)) { StartMove({ m_owner->GetPos().x + _target, m_owner->GetPos().y }, _duration, _ease); }
void DOTweenCompo::DOLocalMoveY(float _target, float _duration, float(*_ease)(float)) { StartMove({ m_owner->GetPos().x, m_owner->GetPos().y + _target }, _duration, _ease); }

void DOTweenCompo::DOSize(Vec2 _target, float _duration, float(*_ease)(float)) { StartScale(_target, _duration, _ease); }
void DOTweenCompo::DOScaleX(float _target, float _duration, float(*_ease)(float)) { StartScale({ _target, m_owner->GetSize().y }, _duration, _ease); }
void DOTweenCompo::DOScaleY(float _target, float _duration, float(*_ease)(float)) { StartScale({ m_owner->GetSize().x, _target }, _duration, _ease); }
void DOTweenCompo::DOScale(float _target, float _duration, float(*_ease)(float)) { StartScale({ _target, _target }, _duration, _ease); }

void DOTweenCompo::StartMove(Vec2 _target, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    m_moveStart = m_owner->GetPos();
    m_moveTarget = _target;
    m_moveDuration = _duration;
    m_moveEase = _ease;
    m_moveT = 0.f;
    m_isMoving = true;
}

void DOTweenCompo::StartScale(Vec2 _target, float _duration, float(*_ease)(float))
{
    if (!m_owner) m_owner = GetOwner();

    m_scaleStart = m_owner->GetSize();
    m_scaleTarget = _target;
    m_scaleDuration = _duration;
    m_scaleEase = _ease;
    m_scaleT = 0.f;
    m_isScaling = true;
}