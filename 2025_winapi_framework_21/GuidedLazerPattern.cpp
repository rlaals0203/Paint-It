#include "pch.h"
#include "GuidedLazerPattern.h"
#include "PlayerFindManager.h"


GuidedLazerPattern::GuidedLazerPattern(BossController* _controller, int _count, float _duration)
	: BossPattern(m_Controller),
	m_time(0.f)
{
	m_duration = _duration;
	m_count = _count;
	m_target = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

GuidedLazerPattern::~GuidedLazerPattern()
{
}

void GuidedLazerPattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f)
	{
		m_time = m_duration;
		auto* lazer = new LazerObject();
		lazer->ShowLine({ 500.f, 500.f }, 1.f, false);
		m_lazers.push(lazer);
	}
}

void GuidedLazerPattern::SetUsed()
{
	m_deleteTime = 1.f;
	BossPattern::SetUsed();
}
