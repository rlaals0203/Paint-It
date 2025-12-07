#pragma once
#include "Boss.h"
#include "Animator.h"
#include "EntityHealth.h"

class ArtBoss :
    public Boss
{
public:
    ArtBoss();
    ~ArtBoss();

    void Update() override;
    void Render(HDC _hdc) override;
public:
private:
    EntityHealth* m_healthCompo;
    Texture* m_texture;
    Texture* m_blinkTexture;
};

