#pragma once
#include "Component.h"
#include "Object.h"
#include "Ease.h"

class DOTweenCompo : public Component
{
public:
    DOTweenCompo();
    ~DOTweenCompo();

    void Init() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

    void DOMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOMoveX(float _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOMoveY(float _target, float _duration, float(*_ease)(float) = EaseLinear);

    void DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOLocalMoveX(float _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOLocalMoveY(float _target, float _duration, float(*_ease)(float) = EaseLinear);

    void DOSize(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOScaleX(float _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOScaleY(float _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOScale(float _target, float _duration, float(*_ease)(float) = EaseLinear);

    bool IsMoving() const { return m_isMoving; }
    bool IsScaling() const { return m_isScaling; }

private:
    void StartMove(Vec2 _target, float _duration, float(*_ease)(float));
    void StartScale(Vec2 _target, float _duration, float(*_ease)(float));

private:
    Object* m_owner;

    Vec2 m_moveStart;
    Vec2 m_moveTarget;
    float m_moveDuration;
    float m_moveT;
    bool m_isMoving;
    float(*m_moveEase)(float);

    Vec2 m_scaleStart;
    Vec2 m_scaleTarget;
    float m_scaleDuration;
    float m_scaleT;
    bool m_isScaling;
    float(*m_scaleEase)(float);
};