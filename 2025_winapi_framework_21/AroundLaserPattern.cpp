#include "pch.h"
#include "AroundLaserPattern.h"
#include "LaserObject.h"
#include "BossController.h"

AroundLaserPattern::AroundLaserPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime)
	: BaseLazerPattern(_controller, _count, _isAwaken, _delay, _deleteTime)
{
	SetDeleteTime(0.14f);
}

AroundLaserPattern::~AroundLaserPattern() { }

void AroundLaserPattern::Update()
{
	m_remainTime -= fDT;
	if (m_remainTime <= 0.f && m_remainCount > 0) {
		MakeLaser();
		m_remainTime = m_delay;
		m_remainCount--;
	}

	BaseLazerPattern::Update();
}

void AroundLaserPattern::SetUsed()
{
	BaseLazerPattern::SetUsed();
	m_remainDeleteTime = 1.f;
}

void AroundLaserPattern::MakeLaser()
{
	LaserObject* laser = new LaserObject();

	Vector2 pos = m_Controller->GetOwner()->GetPos();
	float angle = (360 / m_count) * m_remainCount;
	laser->SetWidth(20.f);
	laser->SetColor(m_penType, m_brushType);
	laser->InitLaser(pos, angle, 0.25f, 0.2f);
	m_lasers.push(laser);
}
