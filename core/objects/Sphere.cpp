#include "Sphere.h"
#include "../Settings.h"



Sphere::Sphere(float radius)
    : m_Radius(radius)
{
    Vector3 top = {0, 0, m_Radius};

    float offsetz = top.z - m_Radius * (1 - 0.5f * (1 - 1 / std::sqrtf(5)));

    float tmpRadius = sqrtf(m_Radius * m_Radius - offsetz * offsetz);
    float prevPointx = tmpRadius, prevPointy = 0, pointx, pointy;

    for (float angle = 360 / 5 + 36; angle <= 360 + 36; angle += 360 / 5)
    {
        pointx = tmpRadius * cosf(angle * (float)M_PI / 180);
        pointy = tmpRadius * sinf(angle * (float)M_PI / 180);

        AddTriangle({ {prevPointx, prevPointy, offsetz}, {pointx, pointy, offsetz}, top });

        prevPointx = pointx;
        prevPointy = pointy;
    }

    top = -top;
    prevPointx = tmpRadius, prevPointy = 0, pointx, pointy;

    for (float angle = 360 / 5; angle <= 360; angle += 360 / 5)
    {
        pointx = tmpRadius * cosf(angle * (float)M_PI / 180);
        pointy = tmpRadius * sinf(angle * (float)M_PI / 180);

        AddTriangle({ {pointx, pointy, -offsetz}, {prevPointx, prevPointy, -offsetz}, top });

        prevPointx = pointx;
        prevPointy = pointy;
    }

    for (size_t i = 0; i < 5; ++i)
    {
        Triangle up = GetTriangle(i);
        Triangle down = GetTriangle(i + 5);
        AddTriangle({ up[0], down[1], down[0] });
        AddTriangle({ up[0], down[0], up[1] });
    }

}
