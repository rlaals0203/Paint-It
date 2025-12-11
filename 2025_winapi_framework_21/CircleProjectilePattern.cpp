#include "pch.h"
#include "CircleProjectilePattern.h"
#include "MovePattern.h"
#include "BossController.h"
#include "ProjectileManager.h"
#include "ImpulseManager.h"
#include "TorchObject.h"
#include "SceneManager.h"
#include "Scene.h"

CircleProjectilePattern::CircleProjectilePattern(BossController* _controller,
    ProjectileType _type, int _count) :
    BossPattern(_controller), m_count(_count)
{
    m_boss = m_Controller->GetBoss();
}

CircleProjectilePattern::~CircleProjectilePattern()
{
}

void CircleProjectilePattern::Update()
{
}

void CircleProjectilePattern::SetUsed()
{
    Vec2 torch1Pos = { 100, -50 };
    Vec2 torch2pos = { WINDOW_WIDTH - 100, -50 };
    auto* torch1 = new TorchObject(m_count, torch1Pos, 1.5f);
    auto* torch2 = new TorchObject(m_count, torch2pos);

    Scene* scene = GET_SINGLE(SceneManager)->GetCurScene().get();
    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(torch1, Layer::ENEMYOBSTACLE);
    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(torch2, Layer::ENEMYOBSTACLE);

    m_isUsed = false;
}