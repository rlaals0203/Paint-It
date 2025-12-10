#include "pch.h"
#include "BossController.h"
#include "BossModuleBase.h"

BossController::BossController()
	:m_boss(nullptr)
	,m_CurrentModule(nullptr)
{
}

BossController::~BossController()
{
	for (auto& item : m_ModuleMap) 
	{
		delete item.second;
	}
	m_ModuleMap.clear();
}

void BossController::SetBoss()
{
	Object* owner = GetOwner();
	if (owner)
	{
		m_boss = (Boss*)(owner);
	}
}

void BossController::Init()
{
}

void BossController::LateUpdate()
{
	if (m_CurrentModule != nullptr && m_CurrentModule->GetActive()) 
	{
		m_CurrentModule->UpdateModule();
	}
}

void BossController::Render(HDC _hdc)
{

}

BossModuleBase* BossController::GetModule(wstring _key)
{
	BossModuleBase* r = m_ModuleMap[_key];
	if (r)
	{
		return m_ModuleMap[_key];
	}
	else
	{
		cout << "Module is null";
		return nullptr;
	}
}

void BossController::AddModule(wstring _key, BossModuleBase* _module)
{
	m_ModuleMap.insert({ _key, _module });
}

void BossController::ChangeModule(wstring _key)
{
	if (m_CurrentModule != nullptr) 
	{
		m_CurrentModule->ExitModule();
	}
	m_CurrentModule = m_ModuleMap[_key];
	m_CurrentModule->EnterModule();
}

void BossController::ClearModule()
{
}

