#pragma once
#include "UIText.h"

class EntityHealth;

class UIBossHP :
    public UIText
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

