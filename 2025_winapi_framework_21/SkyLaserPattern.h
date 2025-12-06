#pragma once
#include "BaseLazerPattern.h"

class LaserObject;
class SkyLaserPattern :
    public BaseLazerPattern
{
public:
    SkyLaserPattern(BossController* _controller, int _count, bool _isAwaken = false, float _delay = 0.34f, float _deleteTime = 0.28f);
    ~SkyLaserPattern();
public:
    void Update() override;
    void SetUsed() override;
private:
    void MakeLaser();

private:
    bool m_isGoRight;
};

