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

    void SetSize(Vec2 _target, float _duration, float(*_ease)(float));

    void DOScaleX(float _end, float _duration, float(*_ease)(float))
    {
        SetSize({ _end, m_owner->GetSize().y }, _duration, _ease);
    }

    void DOScaleY(float _end, float _duration, float(*_ease)(float))
    {
        SetSize({ m_owner->GetSize().x, _end }, _duration, _ease);
    }

    void DOScale(float _end, float _duration, float(*_ease)(float))
    {
        SetSize({ _end, _end }, _duration, _ease);
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