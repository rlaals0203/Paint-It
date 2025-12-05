#include "pch.h"
#include "SkyLaserPattern.h"
#include "LaserObject.h"
#include "BossController.h"

SkyLaserPattern::SkyLaserPattern(BossController* _controller, int _count)
	: BossPattern(_controller)
	, m_countNormal(_count - 1)
	, m_count(_count - 1)
	, m_delay(0.34f)
	, m_delete(0.28f)
{
}

SkyLaserPattern::~SkyLaserPattern()
{
}

void SkyLaserPattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f && m_count >= 0)
	{
		MakeLaser();
		m_time = m_delay;
		m_count--;
		if (m_lasers.size() == 1 && m_count >= 0 && m_deleteTime <= 0.f)
		{
			m_deleteTime = m_delete;
		}
	}

	if (m_lasers.size() > 0)
	{
		m_deleteTime -= fDT;
		if (m_deleteTime <= 0.f) {
			auto* laser = m_lasers.front();
			m_lasers.pop();
			laser->HideLine();
			m_deleteTime = m_delete;
		}
	}

	if (m_count == -1 && m_lasers.size() == 0)
		m_isUsed = false;
}

void SkyLaserPattern::SetUsed()
{
	m_isGoRight = rand() % 2 == 0;
	m_time = m_delay;
	m_deleteTime = m_delete;
	m_count = m_countNormal;
	BossPattern::SetUsed();
}

void SkyLaserPattern::MakeLaser()
{
	LaserObject* laser = new LaserObject();
	Vector2 pos;

	if (m_isGoRight)
	{
		pos = { (WINDOW_WIDTH / m_countNormal) * (m_countNormal - m_count) , 0 };
	}
	else
	{
		pos = {(WINDOW_WIDTH / m_countNormal) * m_count , 0};
	}



	laser->SetWidth(WINDOW_WIDTH / m_countNormal);
	laser->InitLaser(pos, 90, 0.05f, 0.2f);
	m_lasers.push(laser);
}
