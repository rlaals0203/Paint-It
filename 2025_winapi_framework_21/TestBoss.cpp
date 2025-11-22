#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"

TestBoss::TestBoss()
{
	AddModule(new TestPattern(m_Controller));
}

TestBoss::~TestBoss()
{
}
