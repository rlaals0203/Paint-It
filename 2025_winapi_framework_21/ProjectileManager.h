#pragma once
#include"Projectile.h"

enum EProjectile
{
	Player,
	None
};

class ProjectileManager
{
	DECLARE_SINGLE(ProjectileManager);
public:
	void Init();
public:
	void RegisterProjectile(EProjectile _type, wstring _texture, float _speed, float _damage);
	void SpawnProjectile(EProjectile _type, float _size, Vec2 _pos, Vec2 _dir);
	void SpawnProjectile(EProjectile _type, float _size, Vec2 _pos, float _angle);
private:
std::unordered_map<EProjectile, Projectile*> m_projectiles;
};

