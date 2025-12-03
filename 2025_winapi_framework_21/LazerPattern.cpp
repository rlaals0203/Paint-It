#include "pch.h"
#include "LazerPattern.h"

LazerPattern::LazerPattern(BossController* _controller, int _count)
	: BossPattern(_controller), m_count(_count)
{
}

LazerPattern::~LazerPattern()
{
}

void LazerPattern::Update()
{
	m_duration -= fDT;
	if (m_duration < 0.f)
	{
		for (auto line : m_lineVec)
		{
			line->HideLine();
		}

		m_lineVec.clear();
		m_isUsed = false;
	}
}

void LazerPattern::SetUsed()
{
	float angle = 20;
	for (int i = 0; i < 6; i++) {
		angle += 20.f;
		auto* lazer = new LazerObject();
		lazer->ShowLine({ WINDOW_WIDTH / 2, -50 }, angle, 0.2f);
		m_lineVec.push_back(lazer);
	}

	m_duration = 2.f;
	BossPattern::SetUsed();
}
