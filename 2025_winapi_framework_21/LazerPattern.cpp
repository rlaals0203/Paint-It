#include "pch.h"
#include "LazerPattern.h"

LazerPattern::LazerPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime)
	: BaseLazerPattern(_controller, _count, _isAwaken, _delay, _deleteTime)
{
}

LazerPattern::~LazerPattern()
{

}

void LazerPattern::Update()
{
	BaseLazerPattern::Update();
}

void LazerPattern::SetUsed()
{
	float angle = 20;
	for (int i = 0; i < m_count; i++) {
		angle += 20.f;
		auto* lazer = new LaserObject();
		lazer->InitLaser({ WINDOW_WIDTH / 2, -50 }, angle, 0.15f, 0.5f);
		lazer->SetDamagePerTick(4, 0.1f);
		m_lasers.push(lazer);
	}

	m_deleteTime = 0.1f;
	m_remainDeleteTime = 1.f;
	BaseLazerPattern::SetUsed();
	m_remainCount = 0;
}
