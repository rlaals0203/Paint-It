#pragma once
#include "BossPattern.h"
#include "ProjectileManager.h"
class Boss;
class CircleProjectilePattern :
    public BossPattern
{
public:
    CircleProjectilePattern(BossController* _controller, ProjectileType _type, 
        int _count);
    ~CircleProjectilePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
protected:
    Boss* m_boss;
    ProjectileType m_type;
    int m_count;
};

