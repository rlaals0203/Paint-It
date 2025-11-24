#include "pch.h"
#include "CircleProjectilePattern.h"
#include "MovePattern.h"
#include "BossController.h"
#include "ProjectileManager.h"

CircleProjectilePattern::CircleProjectilePattern(BossController* _controller,
	ProjectileType _type, int _count) : BossPattern(_controller),
	m_type(_type), m_count(_count)
{ 
	m_boss = m_Controller->GetBoss();
}

CircleProjectilePattern::~CircleProjectilePattern()
{
}

void CircleProjectilePattern::Update()
{
}

void CircleProjectilePattern::SetUsed()
{
	float angle = 360 / m_count;
	for (int i = 0; i < m_count; i++) {
		GET_SINGLE(ProjectileManager)->SpawnProjectile(
			m_type, 20.f, 
			m_Controller->GetOwner()->GetPos(), 
			angle * i);
	}
}
