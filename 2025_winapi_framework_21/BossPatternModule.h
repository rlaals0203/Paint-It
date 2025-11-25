#pragma once
#include "BossModuleBase.h"
//#include "BossController.h"

class BossController;
class BossPattern;
class BossPatternModule :
    public BossModuleBase
{
public:
    BossPatternModule(BossController* _controller);
    virtual ~BossPatternModule();

public:
    virtual void EnterModule() override;
    virtual void UpdateModule() override;
    virtual void ExitModule() override;

public:
    void PatternReset();

public:
    void AddPattern(BossPattern* _addPattern);

private:
    void SelectPattern();
    void ShufflePattern();

private:
    vector<BossPattern*> m_Patterns;
    BossPattern* m_CurrentPattern;

    vector<int> m_Orders;
    int m_PatternIndex;
};

