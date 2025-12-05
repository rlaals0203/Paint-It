#pragma once
#include "BossPattern.h"
#include <queue>


class LaserObject;
class AroundLaserPattern :
    public BossPattern
{
public:
    AroundLaserPattern(BossController* _controller, int count);
    ~AroundLaserPattern();
public:
    void Update() override;
    void SetUsed() override;
private:
    void MakeLaser();

private:
    std::queue<LaserObject*> m_lasers;
    int m_countNormal;
    int m_count;
    float m_time;
    float m_delay;
    float m_deleteTime;
    float m_delete;
};

