#include "pch.h"
#include "GuidedLaserPattern.h"
#include "PlayerFindManager.h"

GuidedLaserPattern::GuidedLaserPattern(BossController* _controller, int _count)
	: BossPattern(_controller), m_count(_count), m_delay(0.2f), m_player(nullptr)
{
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

GuidedLaserPattern::~GuidedLaserPattern()
{
}

void GuidedLaserPattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f)
	{
		SetLaser();
		m_time = m_delay;
		m_count--;

		if (m_count == 0)
			m_isUsed = false;
	}
}

void GuidedLaserPattern::SetUsed()
{
	m_time = m_delay;
	BossPattern::SetUsed();
}

void GuidedLaserPattern::SetLaser()
{
	if(m_player == nullptr)
		m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	LaserObject* laser = new LaserObject();
	float offset = rand() % (2 * 50 + 1) - 50;
	Vec2 spawnPos = { m_player->GetPos().x + offset, -25.f };
	Vec2 dir = m_player->GetPos() - spawnPos;
	dir.Normalize();

	float angle = atan2(dir.y, dir.x);
	laser->ShowLine(spawnPos, angle + 90.f, 0.1f);
}
