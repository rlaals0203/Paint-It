#pragma once
#include "Object.h"
#include "HealPack.h"
class HealPackSpawner :
    public Object
{
public:
    HealPackSpawner();
    ~HealPackSpawner();
public:
    void Update() override;
private:
    void SpawnHealPack();
private:
    float m_delay;
    float m_currentTime;
};

