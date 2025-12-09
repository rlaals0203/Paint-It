#pragma once
#include "LaserObject.h"
#include <time.h>

struct MondrianSection
{
    float x_left;
    float x_right;
    float y_top;
    float y_bottom;

    Vec2 center;
    Vec2 size;

    void CalculateMetrics()
    {
        float W = x_right - x_left;
        float H = y_bottom - y_top;
        size = { W, H };
        center = { (x_left + x_right) / 2.f, (y_top + y_bottom) / 2.f };
    }

    void ActivateLasers(float duration, float delay, float width) const
    {
        (new LaserObject())->ConnectLaser({ x_left, y_top }, { x_right, y_top }, duration, delay);
        (new LaserObject())->ConnectLaser({ x_left, y_bottom }, { x_right, y_bottom }, duration, delay);
        (new LaserObject())->ConnectLaser({ x_left, y_top }, { x_left, y_bottom }, duration, delay);
        (new LaserObject())->ConnectLaser({ x_right, y_top }, { x_right, y_bottom }, duration, delay);
    }
};

class MondrianGenerator
{
private:
    std::vector<MondrianSection> m_sections;
    const float MIN_SIZE = 80.f;

    float GetRandomFloat(float min, float max)
    {
        float random_ratio = (float)rand() / RAND_MAX;
        return min + random_ratio * (max - min);
    }

public:
    MondrianGenerator()
    {
        std::srand(std::time(nullptr));
    }

    const std::vector<MondrianSection>& GetSections() const { return m_sections; }

    void Generate(float startX, float startY, float endX, float endY, int depth = 0, int maxDepth = 4)
    {
        if (depth >= maxDepth || (endX - startX < MIN_SIZE * 2 && endY - startY < MIN_SIZE * 2))
        {
            MondrianSection section = { startX, endX, startY, endY };
            section.CalculateMetrics();
            m_sections.push_back(section);
            return;
        }

        float width = endX - startX;
        float height = endY - startY;

        bool shouldSplitVertically = (width > height * 1.2f);
        bool shouldSplitHorizontally = (height > width * 1.2f);
        int splitDir;

        if (shouldSplitVertically) splitDir = 0; // 수직 분할 (X축)
        else if (shouldSplitHorizontally) splitDir = 1; // 수평 분할 (Y축)
        else splitDir = rand() % 2; // 무작위

        if (splitDir == 0 && width >= MIN_SIZE * 2)
        {
            float minSplitX = startX + MIN_SIZE;
            float maxSplitX = endX - MIN_SIZE;

            float splitX = GetRandomFloat(minSplitX, maxSplitX);

            Generate(startX, startY, splitX, endY, depth + 1, maxDepth);
            Generate(splitX, startY, endX, endY, depth + 1, maxDepth);
        }
        else if (splitDir == 1 && height >= MIN_SIZE * 2)
        {
            float minSplitY = startY + MIN_SIZE;
            float maxSplitY = endY - MIN_SIZE;

            float splitY = GetRandomFloat(minSplitY, maxSplitY);

            Generate(startX, startY, endX, splitY, depth + 1, maxDepth);
            Generate(startX, splitY, endX, endY, depth + 1, maxDepth);
        }
        else
        {
            MondrianSection section = { startX, endX, startY, endY };
            section.CalculateMetrics();
            m_sections.push_back(section);
        }
    }

    void ActivateAllLasers(float duration, float delay, float laserWidth)
    {
        for (const auto& section : m_sections)
        {
            section.ActivateLasers(duration, delay, laserWidth);
        }
    }
};