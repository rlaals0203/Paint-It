#include "pch.h"
#include "DOTweenCompo.h"

DOTweenCompo::DOTweenCompo() : m_owner(nullptr)
    , m_moveStart({ 0,0 }), m_moveTarget({ 0,0 }), m_moveDuration(1.f)
    , m_moveT(0.f), m_isMoving(false), m_moveEase(nullptr)
    , m_scaleStart({ 1,1 }), m_scaleTarget({ 1,1 }), m_scaleDuration(1.f)
    , m_scaleT(0.f), m_isScaling(false), m_scaleEase(nullptr)
    , m_moveCallback(nullptr), m_scaleCallback(nullptr)
{
}

DOTweenCompo::~DOTweenCompo() {}

void DOTweenCompo::Init() { if (!m_owner) m_owner = GetOwner(); }

void DOTweenCompo::LateUpdate()
{
    if (m_isMoving) {
        m_moveT += fDT / m_moveDuration;
        if (m_moveT >= 1.f) m_moveT = 1.f;

        Vec2 pos = EaseLerp(m_moveStart, m_moveTarget, m_moveT, m_moveEase);
        m_owner->SetPos(pos);

        if (m_moveT >= 1.f)
        {
            m_isMoving = false;
            if (m_moveCallback) {
                m_moveCallback();
                m_moveCallback = nullptr;
            }
        }
    }

    if (m_isScaling) {
        m_scaleT += fDT / m_scaleDuration;
        if (m_scaleT >= 1.f) m_scaleT = 1.f;

        Vec2 size = EaseLerp(m_scaleStart, m_scaleTarget, m_scaleT, m_scaleEase);
        m_owner->SetSize(size);

        if (m_scaleT >= 1.f) {
            m_isScaling = false;
            if (m_scaleCallback)
            {
                m_scaleCallback();
                m_scaleCallback = nullptr;
            }
        }
    }

    if (m_isParabola)
    {
        m_paraT += fDT / m_paraDuration;
        if (m_paraT >= 1.f) m_paraT = 1.f;

        float t = m_paraT;
        Vec2 pos = EaseLerp(m_paraStartPos, m_paraTargetPos, t, m_paraEase);
        float arc = m_parabolaHeight * (1.f - (2.f * t - 1.f) * (2.f * t - 1.f));
        pos.y -= arc;

        m_owner->SetPos(pos);

        if (t >= 1.f)
        {
            m_isParabola = false;
            if (m_paraCallback) {
                m_paraCallback();
                m_paraCallback = nullptr;
            }
        }
    }
}

void DOTweenCompo::Render(HDC _hdc) {}
void DOTweenCompo::DOMove(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove(_target, _duration, _ease, _callback); }
void DOTweenCompo::DOMoveX(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove({ _target, m_owner->GetPos().y }, _duration, _ease, _callback); }
void DOTweenCompo::DOMoveY(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove({ m_owner->GetPos().x, _target }, _duration, _ease, _callback); }
void DOTweenCompo::DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove(m_owner->GetPos() + _target, _duration, _ease, _callback); }
void DOTweenCompo::DOLocalMoveX(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove({ m_owner->GetPos().x + _target, m_owner->GetPos().y }, _duration, _ease, _callback); }
void DOTweenCompo::DOLocalMoveY(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartMove({ m_owner->GetPos().x, m_owner->GetPos().y + _target }, _duration, _ease, _callback); }

void DOTweenCompo::DOScale(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartScale(_target, _duration, _ease, _callback); }
void DOTweenCompo::DOScaleX(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartScale({ _target, m_owner->GetSize().y }, _duration, _ease, _callback); }
void DOTweenCompo::DOScaleY(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartScale({ m_owner->GetSize().x, _target }, _duration, _ease, _callback); }
void DOTweenCompo::DOScale(float _target, float _duration, float(*_ease)(float), std::function<void()> _callback) { StartScale({ _target, _target }, _duration, _ease, _callback); }

void DOTweenCompo::DOParabola(Vec2 _target, float _height, float _duration, float(*_ease)(float), std::function<void()> _callback)
{
    if (!m_owner) m_owner = GetOwner();

    m_isParabola = true;
    m_parabolaHeight = _height;
    m_paraStartPos = m_owner->GetPos();
    m_paraTargetPos = _target;
    m_paraDuration = _duration;
    m_paraEase = _ease;
    m_paraCallback = _callback;
    m_paraT = 0.f;
}

void DOTweenCompo::StartMove(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback)
{
    if (!m_owner) m_owner = GetOwner();

    m_moveStart = m_owner->GetPos();
    m_moveTarget = _target;
    m_moveDuration = _duration;
    m_moveEase = _ease;
    m_moveT = 0.f;
    m_isMoving = true;
    m_moveCallback = _callback;
}

void DOTweenCompo::StartScale(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback)
{
    if (!m_owner) m_owner = GetOwner();

    m_scaleStart = m_owner->GetSize();
    m_scaleTarget = _target;
    m_scaleDuration = _duration;
    m_scaleEase = _ease;
    m_scaleT = 0.f;
    m_isScaling = true;
    m_scaleCallback = _callback;
}

void DOTweenCompo::KillAllTweens()
{
    m_isMoving = false;
    m_isScaling = false;
    m_isParabola = false;

    m_moveCallback = nullptr;
    m_scaleCallback = nullptr;
    m_paraCallback = nullptr;
}
