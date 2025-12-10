#pragma once
#include "BossPattern.h"
#include "DangerGizmo.h"
#include "ColorObject.h"

struct Face
{
    Vec2 center;
    float width;
    float height;
};

class ColorRoomPattern :
    public BossPattern
{
public:
    ColorRoomPattern(BossController* _controller, float _delay);
    ~ColorRoomPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    void GenerateMondrian(float duration, float delay, float laserWidth);
    std::vector<Face>GetFaces();
    void FillFace(Face _face);
    void SelectFace();
    void RemoveFace();
    void FillSection();
    void RemoveSection();
private:
    float m_lineWidth;
    float m_faceWidth;
    float m_threshold;
    int m_countX;
    int m_countY;

    int m_count;
    float m_delay;
    float m_currentDelay;
    float m_dangerTime;

    bool m_isDeleteMode;
    float m_deleteTime;

    std::stack<ColorObject*> m_colorStack;
    std::queue<Face> m_faceQueue;
    std::queue<DangerGizmo*> m_gizmo;
    std::vector<Face> m_faces;
    std::vector<float> m_horizontal;
    std::vector<float> m_vertical;

    PenType m_penTypes[6]{ PenType::RED, PenType::YELLOW, PenType::BLUE, PenType::WHITE, PenType::WHITE, PenType::BLACK };
    BrushType m_brushTypes[6]{ BrushType::RED, BrushType::YELLOW, BrushType::BLUE, BrushType::WHITE, BrushType::WHITE, BrushType::BLACK };
};

