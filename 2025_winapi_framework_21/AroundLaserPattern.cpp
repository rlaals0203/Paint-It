#include "pch.h"
#include "AroundLaserPattern.h"
#include "LaserObject.h"
#include "BossController.h"

AroundLaserPattern::AroundLaserPattern(BossController* _controller, int count)
	: BossPattern(_controller)
	, m_countNormal(count)
	, m_count(count)
	, m_delay(0.07f)
	, m_delete(0.14f)
{

}

AroundLaserPattern::~AroundLaserPattern()
{
}

void AroundLaserPattern::Update()
{
	m_time -= fDT;
	if (m_time <= 0.f && m_count > 0)
	{
		MakeLaser();
		m_time = m_delay;
		m_count--;
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

	if (m_count == 0 && m_lasers.size() == 0)
		m_isUsed = false;
}

void AroundLaserPattern::SetUsed()
{
	m_time = m_delay;
	m_deleteTime = 1.f;
	m_count = m_countNormal;
	BossPattern::SetUsed();
}

void AroundLaserPattern::MakeLaser()
{
	LaserObject* laser = new LaserObject();

	Vector2 pos = m_Controller->GetOwner()->GetPos();

	float angle = (360 / m_countNormal) * m_count;

	laser->SetWidth(20.f);
	laser->InitLaser(pos, angle, 0.25f, 0.2f);
	m_lasers.push(laser);
}
