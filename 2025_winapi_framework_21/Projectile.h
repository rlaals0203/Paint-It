#pragma once
#include "Object.h"
#include "ResourceManager.h"

class Texture;
class Projectile :
    public Object
{
public:
    Projectile();
    ~Projectile();
    void Init(wstring _texture, float _speed, float _damage)
    {
        m_textureName = _texture;
        m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
        m_speed = _speed;
        m_damage = _damage;
    }
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetAngle(float _f)
    {
        m_angle = _f;
        m_isAngle = true;
    }
    void SetDir(Vec2 _dir)
    {
        m_dir = _dir;
        m_dir.Normalize();
        m_isAngle = false;
    }
    float GetSpeed() { return m_speed; }
    float GetDamage() { return m_damage; }
    wstring GetTexture() { return m_textureName; }
private:
    Texture* m_pTexture;
    wstring m_textureName;
    float m_angle;
    float m_speed;
    float m_damage;
    bool m_isAngle;
    Vec2 m_dir;
};

