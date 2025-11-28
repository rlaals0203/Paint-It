#include "pch.h"
#include "MovePattern.h"
#include "BossController.h"
#include "Boss.h"
#include "Ease.h"
#include "LazerObject.h"

MovePattern::MovePattern(BossController* _controller
	, Vec2 _movePos, float _speed, float _stopDistance)
	:BossPattern(_controller)
	,m_movePos(_movePos)
	, m_startPos({0,0})
	, m_speed(_speed)
	, m_dotween(nullptr)
{
	m_boss = m_Controller->GetBoss();
}

MovePattern::~MovePattern()
{
}

void MovePattern::Update()
{
	if (!m_dotween->IsMoving())
	{
		m_isUsed = false;
	}
}

void MovePattern::SetUsed()
{
	if (m_dotween == nullptr)
		m_dotween = m_boss->GetComponent<DOTweenCompo>();

	m_dotween->DOMove(m_movePos, m_duration, EaseOutCubic);
	BossPattern::SetUsed();
}
