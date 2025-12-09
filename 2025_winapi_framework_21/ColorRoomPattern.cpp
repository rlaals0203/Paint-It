#include "pch.h"
#include "ColorRoomPattern.h"
#include "LaserObject.h"
#include "DOTweenCompo.h"
#include "SceneManager.h"

ColorRoomPattern::ColorRoomPattern(BossController* _controller, int _count, float _delay)
	: BossPattern(_controller),
	m_lineWidth(20.f),
	m_faceWidth(110.f),
    m_threshold(50.f),
    m_countX(6),
    m_countY(4)
{
    m_count = _count;
    m_delay = _delay;
    m_dangerTime = m_delay;
}

ColorRoomPattern::~ColorRoomPattern()
{
}

void ColorRoomPattern::Update()
{
    m_currentDelay -= fDT;
    if (m_currentDelay <= 0.f) {
        SelectFace();
        m_currentDelay = m_delay;
        m_currentCount--;
    }

    if (m_currentCount == 0) {
        m_isUsed = true;
    }

    if (m_faceQueue.size() > 0) {
        m_dangerTime -= fDT;
        if (m_dangerTime <= 0.f) {
            auto face = m_faceQueue.front();
            m_faceQueue.pop();
            FillFace(face);
            m_dangerTime = m_delay;
        }
    }
}

void ColorRoomPattern::SetUsed()
{
    m_currentCount = m_count;
    m_currentDelay = m_delay;

    GenerateMondrian(0, 0.2, m_lineWidth);
    BossPattern::SetUsed();
}

void ColorRoomPattern::FillFace(Face _face)
{
    Vec2 pos = _face.center;
    float width = _face.width;
    float height = _face.height;

    auto* gizmo = m_gizmo.front();
    m_gizmo.pop();
    gizmo->SetDead();

    Object* obj = new Object();
    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(obj, Layer::EFFECT);
    obj->SetPos(pos);
    auto* dotween = obj->AddComponent<DOTweenCompo>();
    dotween->DOScale({width, height}, 0.2f, EaseInQuint);
}

void ColorRoomPattern::SelectFace()
{
    int idx = Random::Range(0, m_faces.size());
    auto it = m_faces.begin() + idx;
    auto face = *it;
    m_faces.erase(it);
    m_faceQueue.push(face);

    auto gizmo = new DangerGizmo();
    Vec2 size = { face.width - 25, face.height - 25 };
    gizmo->SetDangerGizmo(face.center, size, 0.f, m_delay);
    m_gizmo.push(gizmo);
}

void ColorRoomPattern::GenerateMondrian(float duration, float delay, float laserWidth)
{
    float xSize = WINDOW_WIDTH / m_countX;
    float ySize = WINDOW_HEIGHT / m_countY;

    for (int i = 0; i < m_countX; ++i)
    {
        float x = Random::Range(i * xSize + 50, (i + 1) * xSize - 50);
        m_horizontal.push_back(x);
        Vec2 start = { x, 0.f };
        Vec2 end = { x, (float)WINDOW_HEIGHT };

        auto* laser = new LaserObject();
        laser->SetWidth(3.f);
        laser->DisableCollider();
        laser->ConnectLaser(start, end, duration, delay);
    }

    for (int i = 0; i < m_countY; ++i)
    {
        float y = Random::Range(i * ySize + 25, (i + 1) * ySize - 25);
        m_vertical.push_back(y);
        Vec2 start = { 0.f, y };
        Vec2 end = { (float)WINDOW_WIDTH, y };

        auto* laser = new LaserObject();
        laser->SetWidth(3.f);
        laser->DisableCollider();
        laser->ConnectLaser(start, end, duration, delay);
    }

    std::sort(m_horizontal.begin(), m_horizontal.end());
    std::sort(m_vertical.begin(), m_vertical.end());

    m_faces = GetFaces();
}

std::vector<Face> ColorRoomPattern::GetFaces()
{
    std::vector<Face> faces;

    std::vector<float> xSize = m_horizontal;
    std::vector<float> ySize = m_vertical;

    ySize.insert(ySize.begin(), 0.f);
    ySize.push_back((float)WINDOW_HEIGHT);

    xSize.insert(xSize.begin(), 0.f);
    xSize.push_back((float)WINDOW_WIDTH);

    for (int y = 0; y < ySize.size() - 1; y++)
    {
        for (int x = 0; x < xSize.size() - 1; x++)
        {
            float top = ySize[y];
            float bottom = ySize[y + 1];
            float left = xSize[x];
            float right = xSize[x + 1];

            float w = right - left;
            float h = bottom - top;

            Vec2 center = { left + w * 0.5f, top + h * 0.5f };
            faces.push_back({ center, w, h });
        }
    }

    return faces;
}
