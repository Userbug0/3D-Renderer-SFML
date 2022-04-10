#include <iostream>

#include "core/Vector3.hpp"
#include "core/Matrix.hpp"


void test()
{
	Matrix<float> mat = { {1, 2, 3, 4},
					      {5, 6, 7, 8},
					      {9, 10, 11, 12},
					      {13, 14, 15, 16} };
	Matrix4x4 mat4x4 = (mat);
	mat4x4 -= 2;
	std::cout << mat4x4;
	std::cout << mat4x4 * mat;
	mat.resize(1, 3);

	Vector3 vec = mat;
	Vector3 other = { 0, 0, 0 };
	other *= 3;
	std::cout << Vector3::Distance(vec, other);
}


int main()
{
	try 
	{
		test();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
