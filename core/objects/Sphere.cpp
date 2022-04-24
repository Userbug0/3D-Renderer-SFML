#include "Sphere.h"
#include "../Settings.h"


Sphere::Sphere(float radius, size_t detailLevel)
    : m_Radius(radius)
{
    makeIcosaedr();

    for (size_t i = 0; i < detailLevel; ++i)
    {
        size_t numOfTri = GetNumOfTriangles();
        for (size_t j = 0; j < numOfTri; ++j)
        {
            detailTriangle(j);
        }
    }
}


void Sphere::detailTriangle(size_t index)
{
    Triangle tri = GetTriangle(index);

    Vector3 mid1 = 0.5 * (tri[0] + tri[1]);
    Vector3 mid2 = 0.5 * (tri[0] + tri[2]);
    Vector3 mid3 = 0.5 * (tri[1] + tri[2]);

    mid1 *= m_Radius / Vector3::Distance({ 0, 0, 0 }, mid1);
    mid2 *= m_Radius / Vector3::Distance({ 0, 0, 0 }, mid2);
    mid3 *= m_Radius / Vector3::Distance({ 0, 0, 0 }, mid3);
     
    AddTriangle({ mid1, mid3, mid2 });
    AddTriangle({ mid1, tri[1], mid3 });
    AddTriangle({ mid2, mid3, tri[2] });

    SetTriangle(index, {tri[0], mid1, mid2});
}


void Sphere::makeIcosaedr()
{
    Vector3 top = { 0, 0, m_Radius };

    float offsetz = m_Radius * (0.25f + std::sqrtf(5) / 20);

    float tmpRadius = std::sqrtf(m_Radius * m_Radius - offsetz * offsetz);

    float toRad = (float)M_PI / 180;
    float prevPointx = tmpRadius * cosf(36 * toRad);
    float prevPointy = tmpRadius * sinf(36 * toRad);
    float pointx, pointy;
    
    for (float angle = 360 / 5 + 36; angle <= 360 + 36; angle += 360 / 5)
    {
        pointx = tmpRadius * cosf(angle * toRad);
        pointy = tmpRadius * sinf(angle * toRad);

        AddTriangle({ {prevPointx, prevPointy, offsetz}, {pointx, pointy, offsetz}, top });

        prevPointx = pointx;
        prevPointy = pointy;
    }

    top = -top;
    prevPointx = tmpRadius, prevPointy = 0;

    for (float angle = 360 / 5; angle <= 360; angle += 360 / 5)
    {
        pointx = tmpRadius * cosf(angle * toRad);
        pointy = tmpRadius * sinf(angle * toRad);

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

