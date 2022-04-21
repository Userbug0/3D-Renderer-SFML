#include "Transform.h"


Matrix4 Transform::GetTransformMatrix() const
{
	Matrix4 toReturn;

	float sinx = sinf(rotation.x);
	float siny = sinf(rotation.y);
	float sinz = sinf(rotation.z);

	float cosx = cosf(rotation.x);
	float cosy = cosf(rotation.y);
	float cosz = cosf(rotation.z);


	toReturn[0][0] = scaling.x*cosy*cosz;			   toReturn[0][1] = cosy * sinz;						  toReturn[0][2] = -siny;
	toReturn[1][0] = sinx * siny * cosz - cosx * sinz; toReturn[1][1] = scaling.y*(sinx*siny*sinz+cosx*cosz); toReturn[1][2] = sinx * cosy;
	toReturn[2][0] = cosx * siny * cosz + sinx * sinz; toReturn[2][1] = cosx * siny * sinz - sinx * cosz;	  toReturn[2][2] = scaling.z*cosx*cosy;
	toReturn[3][0] = translation.x;					   toReturn[3][1] = translation.y;						  toReturn[3][2] = translation.z;
	toReturn[3][3] = 1;

	return toReturn;
}
