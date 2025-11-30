#include "pch.h"
#include "LazerPattern.h"

LazerPattern::LazerPattern(BossController* _controller, int _count)
	: BossPattern(m_Controller), m_count(_count)
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
	int random = rand() % 4;
	for (int i = 0; i < m_count; i++) {
		auto* lazer = new LazerObject();
		auto combo = combos[(i + random) % 4];
		lazer->ShowLine(0.4f, combo.first, combo.second);
		m_lineVec.push_back(lazer);
	}

	m_duration = 2.f;
	BossPattern::SetUsed();
}
