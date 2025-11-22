#include "pch.h"
#include "BossPatternModule.h"
#include "BossController.h"
#include "BossPattern.h"

BossPatternModule::BossPatternModule(BossController* _controller)
	: BossModuleBase(_controller)
	, m_CurrentPattern(nullptr)
	, m_PatternIndex(0)
{
}

BossPatternModule::~BossPatternModule()
{
	for (int i = 0; i < m_Patterns.size(); i++) 
	{
		delete m_Patterns[i];
	}
	m_Patterns.clear();
}

void BossPatternModule::EnterModule()
{
	SelectPattern();
	BossModuleBase::EnterModule();
}

void BossPatternModule::UpdateModule()
{
	if (!m_CurrentPattern->IsUsed()) 
	{
		m_Controller->ChangeModule(L"IdleModule");
		return;
	}
	m_CurrentPattern->Update();
}

void BossPatternModule::ExitModule()
{
	BossModuleBase::ExitModule();
}

void BossPatternModule::AddPattern(BossPattern* _addPattern)
{
	m_Patterns.push_back(_addPattern);
	ShufflePattern();
}

void BossPatternModule::SelectPattern()
{
	if (m_PatternIndex >= m_Patterns.size())
	{
		ShufflePattern();
	}
	m_CurrentPattern = m_Patterns[m_Orders[m_PatternIndex++]];
	m_CurrentPattern->SetUsed();
}

void BossPatternModule::ShufflePattern()
{
	m_Orders.resize(m_Patterns.size(), 0);
	for (int i = 0; i < m_Orders.size(); i++) {
		m_Orders[i] = i;
	}

	int sour, dest, temp;
	for (int i = 0; i < 100; i++) {
		sour = rand() % m_Patterns.size();
		dest = rand() % m_Patterns.size();

		temp = m_Orders[sour];
		m_Orders[sour] = m_Orders[dest];
		m_Orders[dest] = temp;
	}

	m_PatternIndex = 0;
}
