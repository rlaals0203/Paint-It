#include "pch.h"
#include "BurstSkill.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Animator.h"
#include "Collider.h"

BurstSkill::BurstSkill()
    : m_animator(nullptr)
    , m_burstTexture(nullptr)
    , m_radius(150.f)
    , m_duration(0.5f)
    , m_timer(0.f)
    , m_hasTriggered(false)
{
}

BurstSkill::~BurstSkill()
{
}

void BurstSkill::Init(Vec2 _playerPos, float _radius, float _duration)
{
    SetPos(_playerPos);
    m_radius = _radius;
    m_duration = _duration;
    m_timer = 0.f;
    m_hasTriggered = false;

    m_burstTexture = GET_SINGLE(ResourceManager)->GetTexture(L"burstSlash");
    m_animator = AddComponent<Animator>();

    m_burstAnim = L"burstSlash";

    m_animator->CreateAnimation(
        m_burstAnim, m_burstTexture,
        { 0.f, 0.f },
        { 128.f, 128.f },
        { 128.f, 0.f },
        8,
        m_duration / 8.f);

    m_animator->Play(m_burstAnim, PlayMode::Once);

    SetSize({ m_radius * 2.f, m_radius * 2.f });
}

void BurstSkill::Update()
{
    Object::Update();
    m_timer += fDT;

    if (!m_hasTriggered && m_timer >= m_duration * 0.3f)
    {
        DestroyProjectilesInRange();
        m_hasTriggered = true;
    }

    if (m_timer >= m_duration)
    {
        SetDead();
    }
}

void BurstSkill::Render(HDC _hdc)
{
    ComponentRender(_hdc);
}

void BurstSkill::DestroyProjectilesInRange()
{
    Vec2 center = GetPos();
    const std::shared_ptr<Scene>& curScene = GET_SINGLE(SceneManager)->GetCurScene();

    // ENEMYOBSTACLE 레이어의 모든 오브젝트 가져오기 (적 투사체)
    const vector<Object*>& projectiles = curScene->GetLayerObjects(Layer::ENEMYOBSTACLE);

    for (size_t i = 0; i < projectiles.size(); ++i)
    {
        Object* obj = projectiles[i];
        if (obj->GetIsDead()) continue;

        Collider* col = obj->GetComponent<Collider>();
        if (col != nullptr)
        {
            Vec2 projPos = obj->GetPos();
            float dx = projPos.x - center.x;
            float dy = projPos.y - center.y;
            float dist = sqrtf(dx * dx + dy * dy);

            float innerRadius = m_radius * 0.3f;
            float outerRadius = m_radius;

            if (dist >= innerRadius && dist <= outerRadius)
            {
                obj->SetDead();
            }
        }
    }
}