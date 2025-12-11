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
    void Update() override;
    void Render(HDC _hdc) override;
    virtual void Init(std::wstring _texture, float _damage);
    virtual void EnterCollision(Collider* _other) override;
public:
    void SetAngle(float _angle)
    {
        m_angle = _angle;
        m_isAngle = true;
    }
    void SetDir(Vec2 _dir)
    {
        m_dir = _dir;
        m_dir.Normalize();
        m_isAngle = false;
    }
    void SetSpeed(float _speed) { m_speed = _speed * 100; }
    float GetSpeed() { return m_speed; }
    float GetDamage() { return m_damage; }
    std::wstring GetTexture() { return m_textureName; }
protected:
    Texture* m_pTexture;
    float m_speed;
    float m_damage;
    float m_lifeTime;
private:
    std::wstring m_textureName;
    float m_angle;
    bool m_isAngle;
    Vec2 m_dir;
};

