#include "pch.h"
#include "BossPattern.h"

BossPattern::BossPattern(BossController* _controller)
	: m_Controller(_controller)
	, m_isUsed(false)
{
}

BossPattern::~BossPattern()
{
}
