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
    void Init(wstring _texture, float _damage);
    void Update() override;
    void Render(HDC _hdc) override;
    virtual void EnterCollision(Collider* _other)override;
    virtual void ExitCollision(Collider* _other)override;
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
    void SetSpeed(float _speed) { m_speed = _speed; }
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

