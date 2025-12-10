#pragma once
#include "BossPattern.h"
class BossController;

class DotBombPattern :
    public BossPattern
{
public:
    DotBombPattern(BossController* _controller, int count);
    virtual ~DotBombPattern();

public:
    virtual void Update() override;
    void SetUsed() override;

private:
    void MakeDot();

private:
    int m_baseCount;
    int m_count;
    int m_damage;

    float m_spawnTime;
    float m_timer;
    
    float m_destroyTime;
    float m_bombTime;
    float m_blinkTime;
    float m_damageTime;

    Vec2 m_dotSize;
    Vec2 m_bombSize;
};

