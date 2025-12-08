#include "pch.h"
#include "BlackHolePattern.h"
#include "DOTweenCompo.h"
#include "ProjectileManager.h"
#include "ImpulseManager.h"

BlackHolePattern::BlackHolePattern(BossController* _controller, int _count)
	: BossPattern(_controller)
{
	m_count = _count;
	m_delay = 0.04f;
}

BlackHolePattern::~BlackHolePattern()
{
}

void BlackHolePattern::Update()
{
	m_remainDelay -= fDT;
	if (m_remainDelay <= 0.f) {
		m_remainDelay = m_delay;

		Vec2 finalPos = GetRandomOutsidePos();
		auto* proj = GET_SINGLE(ProjectileManager)->SpawnProjectile(
			BlackHoleProjectile, 30.f, finalPos, 0.f, 0.f);
		auto* dotween = proj->AddComponent<DOTweenCompo>();
		dotween->DOMove({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 },
			2.f, EaseInQuart, [proj]() {proj->SetDead(); });

		m_currentCount--;
	}

	if (m_currentCount == 0)
		m_isUsed = true;
}

void BlackHolePattern::SetUsed()
{
	m_currentCount = m_count;
	GET_SINGLE(ImpulseManager)->ApplyImpulse(10.f, m_delay * m_count);
	BossPattern::SetUsed();
}

Vec2 BlackHolePattern::GetRandomOutsidePos()
{
	int side = Random::Range(0, 4);

	if (side == 0)
		return { Random::Range(0, WINDOW_WIDTH), -10.f };
	if (side == 1)
		return { Random::Range(0, WINDOW_WIDTH), WINDOW_HEIGHT + 10.f };
	if (side == 2)
		return { -10.f, Random::Range(0, WINDOW_HEIGHT) };
	return { WINDOW_WIDTH + 10.f, Random::Range(0, WINDOW_HEIGHT) };
}
