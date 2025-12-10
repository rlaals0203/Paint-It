#pragma once
#include "BossPattern.h"
#include "LaserObject.h"
#include "SpriteObject.h"
#include <vector>
#include <queue>

class StringArtPattern : public BossPattern
{
public:
    StringArtPattern(BossController* _controller, float _laserDelay = 0.15f);
    ~StringArtPattern();

public:
    void Update() override;
    void SetUsed() override;

private:
    void ShowDangerGizmo();
    void SpawnPonds();
    void FireNextLaser();
    Vec2 GetPondPosition(int index);

private:
    std::vector<SpriteObject*> m_ponds;
    std::vector<Vec2> m_pondPositions;

    std::queue<LaserObject*> m_lasers;
    int m_currentLaserIndex;
    int m_totalLasers;

    float m_dangerDelay;
    float m_laserDelay;
    float m_pondToLaserDelay;
    float m_currentTime;
    float m_deleteTime;
    float m_remainDeleteTime;

    bool m_isDangerPhase;
    bool m_isPondSpawned;
    bool m_isWaitingForLaser;
    bool m_isLaserPhase;
    bool m_isCompleted;

    int m_pondCount;
    int m_topPondCount;
    int m_bottomPondCount;
    float m_topY;
    float m_bottomY;
    float m_startX;
    float m_spacingX;
};