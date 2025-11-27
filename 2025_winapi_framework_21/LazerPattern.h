#pragma once
#include "BossPattern.h"
#include "BossPattern.h"
#include "LazerObject.h"

class LazerPattern :
    public BossPattern
{
public:
    LazerPattern(BossController* _controller, int _count);
    ~LazerPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    std::vector<LazerObject*> m_lineVec;
    int m_count;
    float m_duration;

    std::pair<bool, bool> combos[4] = {
    {true, false},
    {false, true},
    {true, true},
    {false, false}
    };
};

