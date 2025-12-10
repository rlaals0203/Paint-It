#include "pch.h"
#include "StringArtPattern.h"
#include "BossController.h"
#include "DangerGizmo.h"
#include "SceneManager.h"
#include "ImpulseManager.h"
#include "ResourceManager.h"

StringArtPattern::StringArtPattern(BossController* _controller, float _laserDelay)
    : BossPattern(_controller),
    m_dangerDelay(1.0f),
    m_laserDelay(_laserDelay),
    m_pondToLaserDelay(0.7f),
    m_currentTime(0.f),
    m_deleteTime(0.3f),
    m_remainDeleteTime(0.f),
    m_isDangerPhase(true),
    m_isPondSpawned(false),
    m_isWaitingForLaser(false),
    m_isLaserPhase(false),
    m_isCompleted(false),
    m_currentLaserIndex(0),
    m_pondCount(19),
    m_topPondCount(9),
    m_bottomPondCount(10),
    m_totalLasers(18)
{
    m_topY = WINDOW_HEIGHT * 0.05f;
    m_bottomY = WINDOW_HEIGHT * 0.85f;
    m_startX = WINDOW_WIDTH * 0.05f;
    m_spacingX = (WINDOW_WIDTH * 0.90f) / 9.f;
}

StringArtPattern::~StringArtPattern()
{
}

void StringArtPattern::Update()
{
    if (m_isCompleted)
    {
        if (m_lasers.size() > 0)
        {
            m_remainDeleteTime -= fDT;
            if (m_remainDeleteTime <= 0.f)
            {
                auto* laser = m_lasers.front();
                m_lasers.pop();
                laser->HideLine();
                m_remainDeleteTime = m_deleteTime;
            }
        }
        else
        {
            for (auto* pond : m_ponds)
            {
                if (pond)
                    pond->SetDead();
            }
            m_ponds.clear();
            m_isUsed = false;
        }
        return;
    }

    m_currentTime -= fDT;

    if (m_isDangerPhase)
    {
        if (m_currentTime <= 0.f)
        {
            m_isDangerPhase = false;
            SpawnPonds();
            m_isWaitingForLaser = true;
            m_currentTime = m_pondToLaserDelay;
        }
        return;
    }

    if (m_isWaitingForLaser)
    {
        if (m_currentTime <= 0.f)
        {
            m_isWaitingForLaser = false;
            m_isLaserPhase = true;
            m_currentTime = m_laserDelay;
        }
        return;
    }

    if (m_isLaserPhase)
    {
        if (m_currentTime <= 0.f && m_currentLaserIndex < m_totalLasers)
        {
            FireNextLaser();
            m_currentLaserIndex++;
            m_currentTime = m_laserDelay;

            if (m_currentLaserIndex >= m_totalLasers)
            {
                m_isCompleted = true;
                m_remainDeleteTime = 0.5f;
            }
        }
    }
}

void StringArtPattern::SetUsed()
{
    m_currentTime = m_dangerDelay;
    m_currentLaserIndex = 0;
    m_isDangerPhase = true;
    m_isPondSpawned = false;
    m_isWaitingForLaser = false;
    m_isLaserPhase = false;
    m_isCompleted = false;

    m_pondPositions.clear();
    for (int i = 0; i < m_pondCount; i++)
    {
        m_pondPositions.push_back(GetPondPosition(i));
    }

    ShowDangerGizmo();
    BossPattern::SetUsed();
}

Vec2 StringArtPattern::GetPondPosition(int index)
{
    bool isBottom = (index % 2 == 0);
    float y = isBottom ? m_bottomY : m_topY;

    float x;
    if (isBottom)
    {
        int bottomIndex = index / 2;
        x = m_startX + bottomIndex * m_spacingX;
    }
    else
    {
        int topIndex = index / 2;
        x = m_startX + (topIndex + 0.5f) * m_spacingX;
    }

    return Vec2(x, y);
}

void StringArtPattern::ShowDangerGizmo()
{
    float gizmoHeight = 80.f;

    Vec2 topCenter = { WINDOW_WIDTH * 0.5f, m_topY };
    auto* topGizmo = new DangerGizmo();
    topGizmo->SetDangerGizmo(topCenter, { (float)WINDOW_WIDTH, gizmoHeight }, 0.f, m_dangerDelay);

    Vec2 bottomCenter = { WINDOW_WIDTH * 0.5f, m_bottomY };
    auto* bottomGizmo = new DangerGizmo();
    bottomGizmo->SetDangerGizmo(bottomCenter, { (float)WINDOW_WIDTH, gizmoHeight }, 0.f, m_dangerDelay);
}

void StringArtPattern::SpawnPonds()
{
    GET_SINGLE(ImpulseManager)->ApplyImpulse(10.f, 0.3f);
    GET_SINGLE(ResourceManager)->Play(L"smash");

    for (int i = 0; i < m_pondCount; i++)
    {
        auto* pond = new SpriteObject(L"pond", Layer::DEFAULT, true);
        pond->SetPos(m_pondPositions[i]);
        pond->SetSize({ 64.f, 64.f });
        m_ponds.push_back(pond);
    }

    m_isPondSpawned = true;
}

void StringArtPattern::FireNextLaser()
{
    int fromIndex = m_currentLaserIndex;
    int toIndex = m_currentLaserIndex + 1;

    Vec2 startPos = m_pondPositions[fromIndex];
    Vec2 endPos = m_pondPositions[toIndex];

    GET_SINGLE(ImpulseManager)->ApplyImpulse(5.f, 0.15f);

    LaserObject* laser = new LaserObject();
    laser->SetWidth(12.f);
    laser->SetColor(PenType::YELLOW, BrushType::YELLOW);
    laser->SetDamagePerTick(1.f, 0.1f);
    laser->ConnectLaser(startPos, endPos, 0.05f, 0.f);

    m_lasers.push(laser);
}