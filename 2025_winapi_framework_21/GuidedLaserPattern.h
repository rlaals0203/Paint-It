#pragma once
#include "BossPattern.h"
#include "LaserObject.h"
#include "Player.h"

class GuidedLaserPattern :
    public BossPattern
{
public:
    GuidedLaserPattern(BossController* _controller, int _count);
    ~GuidedLaserPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
    void SetLaser();
private:
    Player* m_player;
    std::stack<LaserObject*> m_lasers;
    int m_count;
    float m_time;
    float m_delay;
};

