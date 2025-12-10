#pragma once
#include "Boss.h"
#include "Animator.h"
class FireBoss :
    public Boss
{
public:
    FireBoss();
    ~FireBoss();
    void Update() override;
    void Render(HDC _hdc) override;
private:
    void HandleDaad();
private:
    Texture* m_texture;
    Texture* m_blinkTexture;
    std::wstring _animName;
    bool m_hasBlinked;
    const std::wstring m_animName;
    const std::wstring m_blinkName;
};

