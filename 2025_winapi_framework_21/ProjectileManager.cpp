#include "pch.h"
#include "SceneManager.h"
#include "ProjectileManager.h"

void ProjectileManager::Init()
{
	RegisterProjectile(PlayerProjectile, L"playerbullet", 20.f);
	RegisterProjectile(DrawProjectile, L"firebullet", 5.f);
	RegisterProjectile(Enemy, L"bullet", 1.f);
	RegisterProjectile(BlackHoleProjectile, L"yellowprojectile", 1.f);
}

/// <summary>
/// 투사체 등록 (타입, 텍스쳐 이름, 속도, 데미지)
/// </summary>
void ProjectileManager::RegisterProjectile(ProjectileType _type, wstring _texture, float _damage)
{
	auto proj = new Projectile();
	proj->Init(_texture, _damage);
	m_projectiles[_type] = proj;
}

/// <summary>
/// 투사체 소환 매서드 (타입, 크기, 위치, 방향, 플레이어 소유인가)
/// </summary>
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

/// <summary>
/// 투사체 소환 매서드 (타입, 크기, 위치, 각도, 플레이어 소유인가)
/// </summary>
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
