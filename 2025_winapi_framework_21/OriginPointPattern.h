#pragma once
#include "BossPattern.h"
class OriginPointPattern :
    public BossPattern
{
public:
    OriginPointPattern(BossController* _controller ,int count);
    ~OriginPointPattern();

public:
    void Update() override;
    void SetUsed() override;

private:
    int m_baseCount;
    int m_count;
    int m_damage;

    float m_aniNextTime;

    float m_reductionTime;
    float m_waitingTime;
    float m_spawnTime;
};