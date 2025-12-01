#pragma once
#include "UIElement.h"

class EntityHealth;

class UIBossHP :
    public UIElement
{
public:
    UIBossHP();
    ~UIBossHP();

public:
    void Render(HDC _hdc) override;

public:
    void SetHealthCompo(EntityHealth* HealthCompo) { bossHealthCompo = HealthCompo; }
    

private:
    EntityHealth* bossHealthCompo;
};

