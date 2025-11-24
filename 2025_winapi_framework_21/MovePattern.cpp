#include "pch.h"
#include "MovePattern.h"
#include "BossController.h"
#include "Boss.h"

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
	m_boss->MoveTransPos(m_moveDir * (fDT * m_speed));
	m_startPos = m_boss->GetPos();
	m_moveDir = m_movePos - m_startPos;
	if (m_moveDir.Length() <= m_stopDistance)
	{
		m_isUsed = false;
	}
	else
	{
		m_moveDir.Normalize();
	}
}

void MovePattern::SetUsed()
{
	m_startPos = m_boss->GetPos();
	m_moveDir = m_movePos - m_startPos;
	m_moveDir.Normalize();
	BossPattern::SetUsed();
}
