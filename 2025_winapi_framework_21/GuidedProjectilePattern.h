#pragma once
#include "BossPattern.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Boss.h"

class GuidedProjectilePattern : 
    public BossPattern
{
public:
    GuidedProjectilePattern(BossController* _controller, ProjectileType _type, 
        float _delay, int _count);
    ~GuidedProjectilePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    Boss* m_boss;
    Player* m_player;
    float m_delay;
    float m_count;
    float m_currentTime;
    bool m_canFire;
    ProjectileType m_type;
};

