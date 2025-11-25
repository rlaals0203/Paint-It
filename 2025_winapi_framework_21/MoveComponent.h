#pragma once
#include "Component.h"
#include "Object.h"
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
	void SetMove(Vec2 start, Vec2 target, float duration);
	bool IsMoving() const { return m_isMoving; }
private:
	Vec2 m_start;
	Vec2 m_target;
	Object* m_owner;
	float m_duration;
	float m_t;
	bool  m_isMoving;
};

