#include "pch.h"
#include "SceneManager.h"
#include "ProjectileManager.h"

void ProjectileManager::Init()
{
	RegisterProjectile(Player, L"bullet", 10.f, 5.f);
}


void ProjectileManager::RegisterProjectile(ProjectileType _type, wstring _texture, float _speed, float _damage)
{
	auto proj = new Projectile();
	proj->Init(_texture, _speed, _damage);
	m_projectiles[_type] = proj;
}

void ProjectileManager::SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos, 
	Vec2 _dir, bool isPlayer)
{
	auto iter = m_projectiles.find(_type);
	if (iter != m_projectiles.end())
	{
		Projectile* proj = iter->second;

		Projectile* newProj = new Projectile();
		newProj->Init(proj->GetTexture(), proj->GetSpeed(), proj->GetDamage());
		newProj->SetPos(_pos);
		newProj->SetDir(_dir);
		newProj->SetSize({ _size, _size });

		Layer projLayer = isPlayer ? Layer::PLAYERPROJECTILE : Layer::ENEMYPROJECTILE;
		GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(newProj, projLayer);
	}
}

void ProjectileManager::SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos, 
	float _angle, bool isPlayer)
{
	auto iter = m_projectiles.find(_type);
	if (iter != m_projectiles.end())
	{
		Projectile* proj = iter->second;

		Projectile* newProj = new Projectile();
		newProj->Init(proj->GetTexture(), proj->GetSpeed(), proj->GetDamage());
		newProj->SetPos(_pos);
		newProj->SetAngle(_angle);
		newProj->SetSize({ _size, _size });

		Layer projLayer = isPlayer ? Layer::PLAYERPROJECTILE : Layer::ENEMYPROJECTILE;
		GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(newProj, projLayer);
	}
}