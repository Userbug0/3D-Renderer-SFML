#pragma once

#include "Vector3.h"
#include "Matrix4.h"



class Transform
{
public:
	Matrix4 GetTransformMatrix() const;

	Vector3 scaling;
	Vector3 translation;
	Vector3 rotation;

};
