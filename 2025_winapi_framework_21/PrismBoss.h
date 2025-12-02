#pragma once
#include "Boss.h"
#include "Animator.h"
#include "EntityHealth.h"

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
public:
private:
    EntityHealth* m_healthCompo;
    Texture* m_texture;
    Texture* m_blinkTexture;
    bool m_hasBlinked;
    bool m_isShieldMode;
    const std::wstring m_animName;
    const std::wstring m_blinkName;
    std::vector<PrismObject*> m_prismObjects;
};

