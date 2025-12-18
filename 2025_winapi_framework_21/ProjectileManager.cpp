#include "pch.h"
#include "SceneManager.h"
#include "ProjectileManager.h"

void ProjectileManager::Init()
{
    RegisterProjectile(PlayerProjectile, L"playerbullet", 10.f);
    RegisterProjectile(DrawProjectile, L"firebullet", 10.f);
    RegisterProjectile(Enemy, L"bullet", 7.f);
    RegisterProjectile(BlackHoleProjectile, L"yellowprojectile", 5.f);
    RegisterProjectile(BlackHoleProjectile2, L"yellowprojectile", 10.f);
    RegisterProjectile(PlayerRedBullet, L"playerredbullet", 20.f);
}

void ProjectileManager::Release()
{
    for (auto& pair : m_projectiles)
    {
        if (pair.second)
        {
            delete pair.second;
            pair.second = nullptr;
        }
    }
    m_projectiles.clear();
}

void ProjectileManager::RegisterProjectile(ProjectileType _type, wstring _texture, float _damage)
{
    auto proj = new Projectile();
    proj->Init(_texture, _damage);
    m_projectiles[_type] = proj;
}

Projectile* ProjectileManager::SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos,
    Vec2 _dir, float _speed, bool isPlayer)
{
    auto iter = m_projectiles.find(_type);
    if (iter != m_projectiles.end())
    {
        Projectile* proj = iter->second;

        Projectile* newProj = new Projectile();
        newProj->Init(proj->GetTexture(), proj->GetDamage());
        newProj->SetPos(_pos);
        newProj->SetSpeed(_speed);
        newProj->SetDir(_dir);
        newProj->SetSize({ _size, _size });

        Layer projLayer = isPlayer ? Layer::PLAYERPROJECTILE : Layer::ENEMYOBSTACLE;
        GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(newProj, projLayer);
        return newProj;
    }
    return nullptr;
}

Projectile* ProjectileManager::SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos,
    float _angle, float _speed, bool isPlayer)
{
    auto iter = m_projectiles.find(_type);
    if (iter != m_projectiles.end())
    {
        Projectile* proj = iter->second;

        Projectile* newProj = new Projectile();
        newProj->Init(proj->GetTexture(), proj->GetDamage());
        newProj->SetSpeed(_speed);
        newProj->SetPos(_pos);
        newProj->SetAngle(_angle);
        newProj->SetSize({ _size, _size });

        Layer projLayer = isPlayer ? Layer::PLAYERPROJECTILE : Layer::ENEMYOBSTACLE;
        GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(newProj, projLayer);
        return newProj;
    }
    return nullptr;
}