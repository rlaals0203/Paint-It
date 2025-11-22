#pragma once
#include"Projectile.h"

enum ProjectileType
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
	void RegisterProjectile(ProjectileType _type, wstring _texture, float _speed, float _damage);
	void SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos, Vec2 _dir);
	void SpawnProjectile(ProjectileType _type, float _size, Vec2 _pos, float _angle);
private:
std::unordered_map<ProjectileType, Projectile*> m_projectiles;
};

