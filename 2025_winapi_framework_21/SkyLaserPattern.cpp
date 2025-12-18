#include "pch.h"
#include "SkyLaserPattern.h"
#include "LaserObject.h"
#include "BossController.h"

SkyLaserPattern::SkyLaserPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime)
	: BaseLazerPattern(_controller, _count, _isAwaken, _delay, _deleteTime) {
	m_deleteTime = _deleteTime;
}

SkyLaserPattern::~SkyLaserPattern() { }

void SkyLaserPattern::Update()
{
	m_remainTime -= fDT;
	if (m_remainTime <= 0.f && m_remainCount >= 0)
	{
		MakeLaser();
		m_remainTime = m_delay;
		m_remainCount--;
		if (m_lasers.size() == 1 && m_remainCount >= 0 && m_remainDeleteTime <= 0.f)
		{
			m_remainDeleteTime = m_deleteTime;
		}
	}

	BaseLazerPattern::Update();
}

void SkyLaserPattern::SetUsed()
{
	m_isGoRight = rand() % 2 == 0;
	BaseLazerPattern::SetUsed();
	m_remainCount = m_count + 1;
}

void SkyLaserPattern::MakeLaser()
{
	LaserObject* laser = new LaserObject();
	Vector2 pos;

	if (m_isGoRight)
		pos = { (WINDOW_WIDTH / m_count) * (m_count - (m_remainCount - 1)) , 0 };
	else
		pos = {(WINDOW_WIDTH / m_count) * (m_remainCount - 1) , 0};

	laser->SetWidth(WINDOW_WIDTH / m_count);
	laser->SetColor(m_penType, m_brushType);
	laser->InitLaser(pos, 90, 0.05f, 0.2f);
	laser->SetDamagePerTick(5, 0.1f);
	m_lasers.push(laser);
}
