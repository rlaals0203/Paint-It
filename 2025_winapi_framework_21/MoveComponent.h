#pragma once
#include "Component.h"
#include "Object.h"
#include "Ease.h"
class MoveComponent : public Component
{
public:
	MoveComponent();
	~MoveComponent();
public:
	void Init() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
    void DOMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOMoveX(float _targetX, float _duration, float(*_ease)(float) = EaseLinear);
    void DOMoveY(float _targetY, float _duration, float(*_ease)(float) = EaseLinear);

    void DOLocalMove(Vec2 _target, float _duration, float(*_ease)(float) = EaseLinear);
    void DOLocalMoveX(float _targetX, float _duration, float(*_ease)(float) = EaseLinear);
    void DOLocalMoveY(float _targetY, float _duration, float(*_ease)(float) = EaseLinear);

    bool IsMoving() const { return m_isMoving; }
private:
    void StartMove(Vec2 _target, bool _local, float _duration, float(*_ease)(float));
private:
    Vec2 m_start;
    Vec2 m_target;
    bool m_localMove;
    Object* m_owner;
    float m_duration;
    float m_t;
    bool m_isMoving;
    float(*m_easeFunc)(float);
};
