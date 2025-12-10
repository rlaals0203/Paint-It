#include "pch.h"
#include "ColorRoomPattern.h"
#include "DOTweenCompo.h"
#include "SceneManager.h"
#include "Object.h"

ColorRoomPattern::ColorRoomPattern(BossController* _controller, float _delay)
    : BossPattern(_controller),
    m_lineWidth(20.f),
    m_faceWidth(110.f),
    m_threshold(50.f),
    m_countX(8),
    m_countY(5),
    m_isDeleteMode(false),
    m_isCompleted(false)
{
    m_delay = _delay;
    m_dangerTime = m_delay;
    m_deleteTime = 2.f;
    m_count = (m_countX + 1) * (m_countY + 1);
}

ColorRoomPattern::~ColorRoomPattern() { }

void ColorRoomPattern::Update()
{
    if (m_isCompleted) return;

    if (m_isDeleteMode)
    {
        RemoveSection();
        if (m_colorStack.size() == 0) {
            for (auto* laser : m_lasers)
                laser->HideLine();
            m_isCompleted = true;
        }
    }
    else
        FillSection();

    if (m_count <= 0)
        m_isDeleteMode = true;
}

void ColorRoomPattern::SetUsed()
{
    m_currentDelay = m_delay;

    GenerateMondrian(0, 0, m_lineWidth);
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

    int idx = Random::Range(0, 6);

    ColorObject* obj = new ColorObject(m_penTypes[idx], m_brushTypes[idx]);
    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(obj, Layer::BACKDAMAGEABLE);
    obj->SetPos(pos);
    m_colorStack.push(obj);

    auto* dotween = obj->AddComponent<DOTweenCompo>();
    dotween->DOScale({width - m_lineWidth / 2, height - m_lineWidth  / 2}, 0.2f, EaseInQuint);
    m_count--;
}

void ColorRoomPattern::SelectFace()
{
    if (m_faces.empty())
        return;

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

void ColorRoomPattern::RemoveFace()
{
    if (m_colorStack.size() == 0) return;
    auto* colorObj = m_colorStack.top();
    m_colorStack.pop();
    auto* dotween = colorObj->GetComponent<DOTweenCompo>();
    dotween->DOScale({ 0, 0 }, 0.3f, EaseInBack, [=]() {colorObj->SetDead(); });
}

void ColorRoomPattern::FillSection()
{
    if (m_count <= 0) return;

    m_currentDelay -= fDT;
    if (m_currentDelay <= 0.f) {
        for (int i = 0; i < 3; i++)
            SelectFace();

        m_currentDelay = m_delay;
    }

    if (m_faceQueue.size() >= 3)
    {
        m_dangerTime -= fDT;
        if (m_dangerTime <= 0.f) {
            for (int i = 0; i < 3; i++) {
                auto face = m_faceQueue.front();
                m_faceQueue.pop();
                FillFace(face);
            }

            m_dangerTime = m_delay;
        }
    }
}

void ColorRoomPattern::RemoveSection()
{
    m_deleteTime -= fDT;
    if (m_deleteTime <= 0.f) {
        m_deleteTime = 1.f;

        for (int i = 0; i < 3; i++)
            RemoveFace();
    }
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
        laser->SetColor(PenType::BLACK, BrushType::BLACK);
        laser->SetWidth(3.f);
        laser->DisableCollider();
        laser->ConnectLaser(start, end, duration, delay);
        m_lasers.push_back(laser);
    }

    for (int i = 0; i < m_countY; ++i)
    {
        float y = Random::Range(i * ySize + 25, (i + 1) * ySize - 25);
        m_vertical.push_back(y);
        Vec2 start = { 0.f, y };
        Vec2 end = { (float)WINDOW_WIDTH, y };

        auto* laser = new LaserObject();
        laser->SetWidth(3.f);
        laser->SetColor(PenType::BLACK, BrushType::BLACK);
        laser->DisableCollider();
        laser->ConnectLaser(start, end, duration, delay);
        m_lasers.push_back(laser);
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

    for (int y = 0; y < ySize.size() - 1; y++) {
        for (int x = 0; x < xSize.size() - 1; x++) {
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
