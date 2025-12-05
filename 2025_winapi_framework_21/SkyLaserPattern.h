#pragma once
#include "BossPattern.h"
#include <queue>


class LaserObject;
class SkyLaserPattern :
    public BossPattern
{
public:
    SkyLaserPattern(BossController* _controller, int count);
    ~SkyLaserPattern();
public:
    void Update() override;
    void SetUsed() override;
private:
    void MakeLaser();

private:
    std::queue<LaserObject*> m_lasers;
    bool m_isGoRight;
    int m_countNormal;
    int m_count;
    float m_time;
    float m_delay;
    float m_deleteTime;
    float m_delete;
};

