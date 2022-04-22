#pragma once

#include "GameObject.h"


class Sphere: public GameObject
{
public:
	Sphere(float radius, size_t detailLevel = 1);

	float GetRadius() const { return m_Radius; }

private:
	void detailTriangle(size_t index);
	void makeIcosaedr();

	float m_Radius;
};
