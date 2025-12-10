#include "pch.h"
#include "BossModuleBase.h"
#include "Boss.h"
#include "BossController.h"

BossModuleBase::BossModuleBase(BossController* _controller)
 	: m_Active(false)
{
	m_Controller = _controller;
}

BossModuleBase::~BossModuleBase()
{
}

void BossModuleBase::EnterModule()
{
	m_Active = true;
}

void BossModuleBase::UpdateModule()
{

}

void BossModuleBase::ExitModule()
{
	m_Active = false;
}
