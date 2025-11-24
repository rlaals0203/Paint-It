#include "pch.h"
#include "MovePatttern.h"
#include "BossController.h"
#include "Boss.h"

MovePatttern::MovePatttern(BossController* _controller
	, Vec2 _movePos, float _speed, float _stopDistance)
	:BossPattern(_controller)
	,m_movePos(_movePos)
	, m_startPos({0,0})
	,m_speed(_speed)
	, m_stopDistance(_stopDistance)
{
	m_boss = m_Controller->GetBoss();
}

MovePatttern::~MovePatttern()
{
}

void MovePatttern::Update()
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

void MovePatttern::SetUsed()
{
	m_startPos = m_boss->GetPos();
	m_moveDir = m_movePos - m_startPos;
	m_moveDir.Normalize();
	BossPattern::SetUsed();
}
