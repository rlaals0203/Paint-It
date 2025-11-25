#pragma once
#include <cmath>

inline float EaseLinear(float t)
{
    return t;
}

inline float EaseInQuad(float t)
{
    return t * t;
}

inline float EaseOutQuad(float t)
{
    return 1 - (1 - t) * (1 - t);
}

inline float EaseInOutQuad(float t)
{
    return t < 0.5f ? 2 * t * t : 1 - powf(-2 * t + 2, 2) * 0.5f;
}

inline float EaseInCubic(float t)
{
    return t * t * t;
}

inline float EaseOutCubic(float t)
{
    return 1 - powf(1 - t, 3);
}

inline float EaseInOutCubic(float t)
{
    return t < 0.5f ? 4 * t * t * t
        : 1 - powf(-2 * t + 2, 3) * 0.5f;
}

inline float EaseInQuart(float t)
{
    return t * t * t * t;
}

inline float EaseOutQuart(float t)
{
    return 1 - powf(1 - t, 4);
}

inline float EaseInOutQuart(float t)
{
    return t < 0.5f ? 8 * t * t * t * t
        : 1 - powf(-2 * t + 2, 4) * 0.5f;
}

inline float EaseInQuint(float t)
{
    return t * t * t * t * t;
}

inline float EaseOutQuint(float t)
{
    return 1 - powf(1 - t, 5);
}

inline float EaseInOutQuint(float t)
{
    return t < 0.5f ? 16 * t * t * t * t * t
        : 1 - powf(-2 * t + 2, 5) * 0.5f;
}

inline float EaseInSine(float t)
{
    return 1 - cosf((t * 3.1415926535f) * 0.5f);
}

inline float EaseOutSine(float t)
{
    return sinf((t * 3.1415926535f) * 0.5f);
}

inline float EaseInOutSine(float t)
{
    return -(cosf(3.1415926535f * t) - 1) * 0.5f;
}

inline float EaseInExpo(float t)
{
    return t == 0 ? 0 : powf(2, 10 * (t - 1));
}

inline float EaseOutExpo(float t)
{
    return t == 1 ? 1 : 1 - powf(2, -10 * t);
}

inline float EaseInOutExpo(float t)
{
    if (t == 0) return 0;
    if (t == 1) return 1;
    return t < 0.5f
        ? powf(2, 20 * t - 10) * 0.5f
        : (2 - powf(2, -20 * t + 10)) * 0.5f;
}

inline float EaseInBack(float t)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;
    return c3 * t * t * t - c1 * t * t;
}

inline float EaseOutBack(float t)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;
    return 1 + c3 * powf(t - 1, 3) + c1 * powf(t - 1, 2);
}

inline float EaseInOutBack(float t)
{
    const float c1 = 1.70158f;
    const float c2 = c1 * 1.525f;

    return t < 0.5f
        ? (powf(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) * 0.5f
        : (powf(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) * 0.5f;
}

inline float EaseInElastic(float t)
{
    if (t == 0) return 0;
    if (t == 1) return 1;

    return -powf(2, 10 * t - 10) *
        sinf((t * 10 - 10.75f) * (2 * 3.1415926535f / 3));
}

inline float EaseOutElastic(float t)
{
    if (t == 0) return 0;
    if (t == 1) return 1;

    return powf(2, -10 * t) *
        sinf((t * 10 - 0.75f) * (2 * 3.1415926535f / 3)) + 1;
}

inline float EaseInOutElastic(float t)
{
    if (t == 0) return 0;
    if (t == 1) return 1;

    if (t < 0.5f)
    {
        return -(powf(2, 20 * t - 10) *
            sinf((20 * t - 11.125f) * (2 * 3.1415926535f / 4.5f))) * 0.5f;
    }
    else
    {
        return (powf(2, -20 * t + 10) *
            sinf((20 * t - 11.125f) * (2 * 3.1415926535f / 4.5f))) * 0.5f + 1;
    }
}


template<typename Vec>
inline Vec EaseLerp(const Vec& start, const Vec& end, float t, float(*easeFunc)(float))
{
    float e = easeFunc(t);
    return start + (end - start) * e;
}