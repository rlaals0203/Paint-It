#include "pch.h"
#include "LineProjectilePattern.h"

LineProjectilePattern::LineProjectilePattern(BossController* _controller)
	: BossPattern(m_Controller)
{
}

LineProjectilePattern::~LineProjectilePattern()
{
}

void LineProjectilePattern::Update()
{
}

void LineProjectilePattern::SetUsed()
{
	BossPattern::SetUsed();

}
