#include "pch.h"
#include "RotateRender.h"

void RotateRender::RotateRectRender(HDC hdc, Vec2 pos, Vec2 size, float angleRad)
{
    Vec2 half = size * 0.5f;

    Vec2 p[4] =
    {
        {-half.x, -half.y},
        { half.x, -half.y},
        { half.x,  half.y},
        {-half.x,  half.y}
    };

    for (int i = 0; i < 4; i++)
        p[i] = p[i].Rotate(p[i], angleRad) + pos;

    POINT pts[4] =
    {
        { (LONG)p[0].x, (LONG)p[0].y },
        { (LONG)p[1].x, (LONG)p[1].y },
        { (LONG)p[2].x, (LONG)p[2].y },
        { (LONG)p[3].x, (LONG)p[3].y }
    };

    Polygon(hdc, pts, 4);
}
