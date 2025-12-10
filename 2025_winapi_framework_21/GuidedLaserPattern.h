#pragma once
#include "BaseLazerPattern.h"
#include "LaserObject.h"
#include "Player.h"
#include <queue>

class GuidedLaserPattern :
    public BaseLazerPattern
{
public:
    GuidedLaserPattern(BossController* _controller, int _count, bool _isAwaken = false, float _delay = 0.07f, float _deleteTime = 0.5f);
    ~GuidedLaserPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
    void SetLaser();
private:
    float m_startDeleteTime;
    LaserObject* m_laser;
    Player* m_player;
};

