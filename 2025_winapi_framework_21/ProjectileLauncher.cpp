#include "pch.h"
#include "ProjectileLauncher.h"
#include "Object.h"
#include "Projectile.h"

ProjectileLauncher::ProjectileLauncher()
{
}

ProjectileLauncher::~ProjectileLauncher()
{
}

void ProjectileLauncher::CreateProjectile(Vec2 _pos)
{
	Vec2 mousePos = GET_MOUSEPOS;
	Vec2 baseDir = mousePos - _pos;
	baseDir.Normalize();

	for (int i = 0; i < 3; i++)
	{
		Projectile* proj = new Projectile;
		proj->SetPos(pos);
		proj->SetSize({ 20.f,20.f });
		proj->SetDir();

		GET_SINGLE(SceneManager)->GetCurScene()
			->AddObject(proj, Layer::PROJECTILE);
	}
}
