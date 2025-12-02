#pragma once
#include "Boss.h"
#include "Animator.h"

class PrismBoss :
    public Boss
{
public:
    PrismBoss();
    ~PrismBoss();

    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetShieldMode(bool _isShieldMode) { m_isShieldMode = _isShieldMode; }
public:
private:
    Texture* m_texture;
    Texture* m_blinkTexture;
    bool m_hasBlinked;
    bool m_isShieldMode;
    const std::wstring m_animName;
    const std::wstring m_blinkName;
};

