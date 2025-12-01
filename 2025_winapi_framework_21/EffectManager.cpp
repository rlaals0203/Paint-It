#include "pch.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

void EffectManager::Init()
{
    RegisterEffect(EffectType::TestPlayer, L"jiwooFront",
        GET_SINGLE(ResourceManager)->GetTexture(L"jiwoo")
        , { 0.f,150.f }, { 50.f,50.f }, { 50.f,0.f }, 5, 1.f);

    RegisterEffect(EffectType::SmashSmoke, L"SmashSmoke", 
        GET_SINGLE(ResourceManager)->GetTexture(L"smashsmoke")
        , {0.f, 0.f} , { 64.f, 64.f }, { 64.f ,0.f }, 8, 0.125f);

    RegisterEffect(EffectType::FireExplosion, L"FireExplosion",
        GET_SINGLE(ResourceManager)->GetTexture(L"fireexplosion")
        , { 0.f, 0.f }, { 32.f, 32.f }, { 32.f ,0.f }, 8, 0.1f);
}

void EffectManager::RegisterEffect(EffectType type, wstring animName, Texture* tex,
    Vec2 lt, Vec2 slice, Vec2 step, UINT frameCount, float duration)
{
    EffectData data;
    data.animName = animName;
    data.tex = tex;
    data.lt = lt;
    data.slice = slice;
    data.step = step;
    data.frameCount = frameCount;
    data.frameDuration = duration;
    assert(data.tex && "Effect texture is null!");
    m_effects[type] = data;
}

void EffectManager::PlayEffect(EffectType _type, Vec2 _pos, Vec2 _size,
    float _duration, bool _loop)
{
    Effect* eff = new Effect();

    auto& data = m_effects[_type];
    eff->SetPos(_pos);
    eff->SetSize(_size);
    eff->Init(data, _duration, _loop);
    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(eff, Layer::EFFECT);
}
