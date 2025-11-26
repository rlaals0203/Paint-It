#include "pch.h"
#include "GuidedProjectilePattern.h"
#include "BossController.h"
#include "ProjectileManager.h"
#include "PlayerFindManager.h"

GuidedProjectilePattern::GuidedProjectilePattern(BossController* _controller,
	ProjectileType _type, float _delay, int _count)
	: BossPattern(_controller)
	, m_type(_type), m_delay(_delay), m_count(_count)
	, m_player(nullptr)
{
	m_boss = m_Controller->GetBoss();
	m_originCount = _count;
}

GuidedProjectilePattern::~GuidedProjectilePattern()
{
}

void GuidedProjectilePattern::Update()
{
	m_currentTime -= fDT;
	if (m_currentTime < 0.f)
	{
		m_currentTime = m_delay;
		m_count--;
		Vec2 pos = m_Controller->GetOwner()->GetPos();
		Vec2 dir = m_player->GetPos() - pos;
		dir.Normalize();

		GET_SINGLE(ProjectileManager)->SpawnProjectile(
			m_type, 60.f, m_Controller->GetOwner()->GetPos(), dir, 15.f);
	}

	if (m_count == 0)
		m_isUsed = false;
}

void GuidedProjectilePattern::SetUsed()
{
	if(m_player == nullptr)
		m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	m_count = m_originCount;
	BossPattern::SetUsed();
}
