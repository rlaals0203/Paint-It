#pragma once
#include "Component.h"
#include "Ease.h"
#include "Object.h"

class ScaleComponent : public Component
{
public:
    ScaleComponent();
    ~ScaleComponent();

    void Init() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

    void SetScaling(Vec2 _start, Vec2 _target, float _duration, float(*_ease)(float));

    void SetScaleX(float _s, float _e, float _duration, float(*_ease)(float))
    {
        SetScaling({ _s, m_owner->GetSize().y }, { _e, m_owner->GetSize().y }, _duration, _ease);
    }

    void SetScaleY(float _s, float _y, float _duration, float(*_ease)(float))
    {
        SetScaling({ m_owner->GetSize().x, _s }, { m_owner->GetSize().x, _y }, _duration, _ease);
    }

    void SetScale(float _s, float _e, float _duration, float(*_ease)(float))
    {
        SetScaling({ _s, _s }, { _e, _e }, _duration, _ease);
    }

private:
    Vec2 m_start;
    Vec2 m_target;
    Object* m_owner;
    float m_duration;
    float m_t;
    bool m_isScaling;
    float (*m_easeFunc)(float);
};