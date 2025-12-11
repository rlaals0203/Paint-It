#include "pch.h"
#include "GuidedLaserPattern.h"
#include "PlayerFindManager.h"

GuidedLaserPattern::GuidedLaserPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime) 
	: BaseLazerPattern(_controller, _count, _isAwaken, _delay, _deleteTime), 
	m_player(nullptr)
{
	m_startDeleteTime = _deleteTime;
	SetDeleteTime(_delay);
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

GuidedLaserPattern::~GuidedLaserPattern()
{
}

void GuidedLaserPattern::Update()
{
	BaseLazerPattern::Update();

	m_remainTime -= fDT;
	if (m_remainTime <= 0.f && m_remainCount > 0)
	{
		SetLaser();
		m_remainTime = m_delay;
		m_remainCount--;
	}
}

void GuidedLaserPattern::SetUsed()
{
	BaseLazerPattern::SetUsed();
	m_remainDeleteTime = m_startDeleteTime;
}

void GuidedLaserPattern::SetLaser()
{
	if(m_player == nullptr)
		m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	LaserObject* laser = new LaserObject();
	laser->SetDamagePerTick(1, 0.1f);
	float offset = Random::Range(-200, 200);
	Vec2 spawnPos = { m_player->GetPos().x + offset, -25.f };
	Vec2 dir = m_player->GetPos() - spawnPos;
	dir.Normalize();

	float angleRad = atan2(dir.y, dir.x);
	float angle = angleRad * 180.f / PI;

	laser->SetWidth(15.f);
	laser->SetColor(m_penType, m_brushType);
	laser->InitLaser(spawnPos, angle, 0.15f, 0.3f);
	m_lasers.push(laser);
}
