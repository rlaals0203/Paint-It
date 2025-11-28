#include "pch.h"
#include "DrawProjectilePattern.h"

DrawProjectilePattern::DrawProjectilePattern(BossController* _controller, float _delay)
	: m_delay(_delay)
{
}

DrawProjectilePattern::~DrawProjectilePattern()
{
}

void DrawProjectilePattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f) {
		m_time = m_delay;

	}
}

void DrawProjectilePattern::SetUsed()
{
	m_time = m_delay;
	BossPattern::SetUsed();
}
