#pragma once
#include "UIText.h"

class EntityHealth;
class Texture;

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
    
public:
    void SetBarTexture(Texture* bar) { m_barTexture = bar; }
    void SetFillTexture(Texture* fill) { m_filledTexture = fill; }

private:
    Texture* m_barTexture;
    Texture* m_filledTexture;
    EntityHealth* bossHealthCompo;
};

