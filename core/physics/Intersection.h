#pragma once


#include "../Vector3.h"


namespace Physics
{
	/// <param name="planeNormal">Must be normalized!</param>
	Vector3 LineIntersectsPlane(const Vector3& planePoint, const Vector3& planeNormal, 
								const Vector3& lineStart, const Vector3& lineEnd);

}
