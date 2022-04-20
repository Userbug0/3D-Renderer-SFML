#include "Intersection.h"


Vector3 Physics::LineIntersectsPlane(const Vector3& planePoint, const Vector3& planeNormal, 
									 const Vector3& lineStart, const Vector3& lineEnd)
{
	float ad = Vector3::DotProduct(lineStart, planeNormal);
	float bd = Vector3::DotProduct(lineEnd, planeNormal);
	if (bd == ad)
		return Vector3::zero;

	float plane_d = Vector3::DotProduct(planeNormal, planePoint);
	float t = (plane_d - ad) / (bd - ad);

	return lineStart + (lineEnd - lineStart) * t;
}
