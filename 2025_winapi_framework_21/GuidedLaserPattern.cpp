#include "pch.h"
#include "GuidedLaserPattern.h"
#include "PlayerFindManager.h"

GuidedLaserPattern::GuidedLaserPattern(BossController* _controller, int _count)
	: BossPattern(_controller), m_count(_count), m_delay(0.07f), m_player(nullptr)
{
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

GuidedLaserPattern::~GuidedLaserPattern()
{
}

void GuidedLaserPattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f && m_count > 0)
	{
		SetLaser();
		m_time = m_delay;
		m_count--;
	}

	if (m_lasers.size() > 0)
	{
		m_deleteTime -= fDT;
		if (m_deleteTime <= 0.f) {
			auto* laser = m_lasers.front();
			m_lasers.pop();
			laser->HideLine();
			m_deleteTime = m_delay;
		}
	}

	if (m_count == 0 && m_lasers.size() == 0)
		m_isUsed = false;
}

void GuidedLaserPattern::SetUsed()
{
	m_time = m_delay;
	m_deleteTime = 0.5f;
	m_count = 10;
	BossPattern::SetUsed();
}

void GuidedLaserPattern::SetLaser()
{
	if(m_player == nullptr)
		m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	LaserObject* laser = new LaserObject();
	float offset = Random::Range(-200, 200);
	Vec2 spawnPos = { m_player->GetPos().x + offset, -25.f };
	Vec2 dir = m_player->GetPos() - spawnPos;
	dir.Normalize();

	float angleRad = atan2(dir.y, dir.x);
	float angle = angleRad * 180.f / PI;
	laser->SetWidth(15.f);
	laser->InitLaser(spawnPos, angle, 0.15f, 0.3f);
	m_lasers.push(laser);
}
