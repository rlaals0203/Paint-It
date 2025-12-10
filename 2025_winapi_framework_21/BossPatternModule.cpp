#include "pch.h"
#include "BossPatternModule.h"
#include "BossController.h"
#include "BossPattern.h"

BossPatternModule::BossPatternModule(BossController* _controller)
    : BossModuleBase(_controller),
    m_CurrentPattern(nullptr),
    m_PatternIndex(0),
    m_isMoveTurn(false)
{
}

BossPatternModule:: ~BossPatternModule()
{
    BossReset();
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
        m_isMoveTurn = !m_isMoveTurn;
        m_Controller->ChangeModule(L"IdleModule");
        return;
    }
    m_CurrentPattern->Update();
}

void BossPatternModule::ExitModule()
{
    BossModuleBase::ExitModule();
}

void BossPatternModule::BossReset()
{
    for (int i = 0; i < m_Patterns.size(); i++)
    {
        delete m_Patterns[i];
    }
    m_Patterns.clear();

    for (int i = 0; i < m_movePatterns.size(); i++)
    {
        delete m_movePatterns[i];
    }
    m_movePatterns.clear();

    m_Orders.clear();
}

void BossPatternModule::AddPattern(BossPattern* _addPattern)
{
    m_Patterns.push_back(_addPattern);
    ShufflePattern();
}

void BossPatternModule::AddMovePattern(MovePattern* p)
{
    m_movePatterns.push_back(p);
}

void BossPatternModule::ClearPattern()
{
    for (int i = 0; i < m_Patterns.size(); i++)
    {
        delete m_Patterns[i];
    }
    m_Patterns.clear();
}

void BossPatternModule::SelectPattern()
{
    if (m_isMoveTurn && m_movePatterns.size() > 0)
    {
        int idx = rand() % m_movePatterns.size();
        m_CurrentPattern = m_movePatterns[idx];
        m_CurrentPattern->SetUsed();
        return;
    }

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