#include "pch.h"
#include "OriginPointPattern.h"
#include "Animator.h"
#include "OriginPoint.h"
#include "SceneManager.h"
#include "ProjectileManager.h"

OriginPointPattern::OriginPointPattern(BossController* _controller, int count)
	: BossPattern(_controller)
	, m_baseCount(count)
	, m_count(count)
	, m_damage(5)
	, m_reductionTime(1.25f)
	, m_waitingTime(0.35f)
	, m_spawnTime(0.05f)
{
	m_aniNextTime = m_reductionTime / 4;
}

OriginPointPattern::~OriginPointPattern()
{
}

void OriginPointPattern::Update()
{
	m_reductionTime -= fDT;
	if (m_reductionTime > 0)
	{
		return;
	}

	m_waitingTime -= fDT;
	if (m_waitingTime > 0)
	{
		return;
	}

	m_spawnTime -= fDT;
	if (m_spawnTime > 0)
	{
		return;
	}

	m_spawnTime = 0.001f;
	float angle = ((float)(rand() % 3600)) / 10;
	GET_SINGLE(ProjectileManager)->SpawnProjectile(
		BlackHoleProjectile , 100.f, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 },
		angle, 10.f);
	m_count--;
	if (m_count <= 0)
		m_isUsed = false;
}

void OriginPointPattern::SetUsed()
{
	m_count = m_baseCount;
	m_reductionTime = 1.5;
	m_waitingTime = 0.55f;
	m_spawnTime = 0.05f;
	OriginPoint* origin = new OriginPoint(m_aniNextTime,m_waitingTime, m_reductionTime);
	origin->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	origin->SetSize({ 4, 4 });
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(origin, Layer::ENEMYOBSTACLE);
	BossPattern::SetUsed();
}
