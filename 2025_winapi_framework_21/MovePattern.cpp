#include "pch.h"
#include "MovePattern.h"
#include "BossController.h"
#include "Boss.h"
#include "Ease.h"

MovePattern::MovePattern(BossController* _controller
	, Vec2 _movePos, float _speed, float _stopDistance)
	:BossPattern(_controller)
	,m_movePos(_movePos)
	, m_startPos({0,0})
	,m_speed(_speed)
	, m_stopDistance(_stopDistance)
{
	m_boss = m_Controller->GetBoss();
}

MovePattern::~MovePattern()
{
}

void MovePattern::Update()
{
	m_t += fDT / m_duration;
	if (m_t > 1.0f) m_t = 1.0f;

	Vec2 pos = EaseLerp(m_startPos, m_movePos, m_t, EaseOutCubic);
	m_boss->SetPos(pos);

	if (m_t >= 1.0f)
	{
		m_isUsed = false;
		m_t = 0.f;
	}
}

void MovePattern::SetUsed()
{
	m_startPos = m_boss->GetPos();
	m_moveDir = m_movePos - m_startPos;
	m_moveDir.Normalize();
	BossPattern::SetUsed();
}
