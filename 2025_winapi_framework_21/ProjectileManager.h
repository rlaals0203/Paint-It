#pragma once
#include "Projectile.h"

enum ProjectileType
{
    PlayerProjectile,
    DrawProjectile,
    Enemy,
    BlackHoleProjectile
};

class ProjectileManager
{
    DECLARE_SINGLE(ProjectileManager);
public:
    void Init();
    void Release();

    void RegisterProjectile(ProjectileType _type, wstring _texture, float _damage);
    Projectile* SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos,
        Vec2 _dir, float _speed, bool isPlayer = false);
    Projectile* SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos,
        float _angle, float _speed, bool isPlayer = false);

private:
    std::unordered_map<ProjectileType, Projectile*> m_projectiles;
};