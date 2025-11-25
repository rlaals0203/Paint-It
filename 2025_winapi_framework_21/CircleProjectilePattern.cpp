#include "pch.h"
#include "CircleProjectilePattern.h"
#include "MovePattern.h"
#include "BossController.h"
#include "ProjectileManager.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"

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
	float angle = 360.f / (float)m_count;
	for (int i = 0; i < m_count; i++) {
		GET_SINGLE(ProjectileManager)->SpawnProjectile(
			m_type, 60.f, 
			m_Controller->GetOwner()->GetPos(), 
			angle * i);
	}

	auto* dangerGizmo = new DangerGizmo();
	dangerGizmo->SetDangerGizmo({ 500, 500 }, { 100, 100 }, 2.f);
	GET_SINGLE(ImpulseManager)->ApplyImpulse(22.5f, 0.4f);
}
