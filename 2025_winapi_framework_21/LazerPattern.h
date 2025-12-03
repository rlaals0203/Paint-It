#pragma once
#include "BossPattern.h"
#include "LaserObject.h"

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
    std::vector<LaserObject*> m_lineVec;
    int m_count;
    float m_duration;
};

