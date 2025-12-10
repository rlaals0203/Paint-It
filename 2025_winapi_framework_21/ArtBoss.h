#pragma once
#include "Boss.h"
#include "Animator.h"
#include "EntityHealth.h"
#include "ColorRoomPattern.h"

class ArtBoss :
    public Boss
{
public:
    ArtBoss();
    ~ArtBoss();

    void Update() override;
    void Render(HDC _hdc) override;
private:
    void HandlePhase();
public:
private:
    ColorRoomPattern* m_roomPattern;
    EntityHealth* m_healthCompo;
    Texture* m_texture;
    Texture* m_blinkTexture;
};

