#include "PhysicEngine.h"


void PhysicEngine::Update(const sf::Time& elapsedTime, Cube* cube)
{
	Vector3 rotation = cube->getRotation();
	for (int i = 0; i < cube->NumOfTrinagles(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			RotatePoint(cube->getTriangle(i)[j], rotation);
		}
	}
}


void PhysicEngine::RotatePoint(Vector3& point, const Vector3& rotation)
{
	Vector3 relative = Vector3(-0.5f, -0.5f, 1) + Vector3(0.5, 0.5, 0.5);
	Vector3 original = point - relative;

	point.x = original.x * (cosf(rotation.z) * cosf(rotation.y)) +
			  original.y * (cosf(rotation.z) * sinf(rotation.y) * sinf(rotation.x) - sinf(rotation.z) * cosf(rotation.x)) +
			  original.z * (cosf(rotation.z) * sinf(rotation.y) * cosf(rotation.x) + sinf(rotation.z) * sinf(rotation.x));

	point.y = original.x * (sinf(rotation.z) * cosf(rotation.y)) +
			  original.y * (sinf(rotation.z) * sinf(rotation.y) * sinf(rotation.x) + cosf(rotation.z) * cosf(rotation.x)) +
		      original.z * (sinf(rotation.z) * sinf(rotation.y) * cosf(rotation.x) - cosf(rotation.z) * sinf(rotation.x));

	point.z = original.x * (-sinf(rotation.y)) +
			  original.y * (cosf(rotation.y) * sinf(rotation.x)) +
			  original.z * (cosf(rotation.y) * cosf(rotation.x));

	point += relative;
}

