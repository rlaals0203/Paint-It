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
	void SetMove(Vec2 start, Vec2 target, float duration, 
		float(*_ease)(float) = EaseLinear);
	bool IsMoving() const { return m_isMoving; }
private:
	Vec2 m_start;
	Vec2 m_target;
	Object* m_owner;
	float m_duration;
	float m_t;
	bool  m_isMoving;
	float(*m_easeFunc)(float);
};

