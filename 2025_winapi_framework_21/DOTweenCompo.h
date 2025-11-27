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

    void DOMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOMoveX(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOMoveY(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);

    void DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOLocalMoveX(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOLocalMoveY(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);

    void DOSize(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOScaleX(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOScaleY(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);
    void DOScale(float _target, float _duration, float(*_ease)(float) = EaseLinear, std::function<void()> _callback = nullptr);

    bool IsMoving() const { return m_isMoving; }
    bool IsScaling() const { return m_isScaling; }

private:
    void StartMove(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback = nullptr);
    void StartScale(Vec2 _target, float _duration, float(*_ease)(float), std::function<void()> _callback = nullptr);

private:
    Object* m_owner;

    Vec2 m_moveStart;
    Vec2 m_moveTarget;
    float m_moveDuration;
    float m_moveT;
    bool m_isMoving;
    float(*m_moveEase)(float);
    std::function<void()> m_moveCallback;

    Vec2 m_scaleStart;
    Vec2 m_scaleTarget;
    float m_scaleDuration;
    float m_scaleT;
    bool m_isScaling;
    float(*m_scaleEase)(float);
    std::function<void()> m_scaleCallback;
};