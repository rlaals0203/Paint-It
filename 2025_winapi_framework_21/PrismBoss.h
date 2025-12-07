#pragma once
#include "Boss.h"
#include "Animator.h"
#include "EntityHealth.h"
#include "SpriteObject.h"
#include "BossShield.h"

class PrismObject;
class PrismBoss :
    public Boss
{
public:
    PrismBoss();
    ~PrismBoss();

    void Update() override;
    void Render(HDC _hdc) override;
public:
    void AddPrism(PrismObject* _prism) { m_prismObjects.push_back(_prism); }
    void RemovePrism() { m_prismObjects.pop_back(); cout << "»èÁ¦"; }
    int GetPrismCount() { return m_prismObjects.size(); }
public:
    void SetShieldMode(bool _isShieldMode) { m_isShieldMode = _isShieldMode; }
private:
    void ActiveShield();
    void InActiveShield();
    void CheckAwaken();
    void Changing();
    void AddAwakenPattern();
private:
    EntityHealth* m_healthCompo;
    Texture* m_texture;
    Texture* m_shieldTexture;
    Texture* m_blinkTexture;
    BossShield* m_shield;
    bool m_isShieldMode;
    std::wstring m_awakenName;
    std::wstring m_changingName;
    std::vector<PrismObject*> m_prismObjects;

    bool m_awakenMode;
    bool m_isChanging;
    float m_changeTime = 2.f;

};

