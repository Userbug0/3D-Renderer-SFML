#include <iostream>

#include "Vector3.hpp"
#include "Matrix.hpp"



int main()
{
	Matrix<float> mat = { {1, 2, 3, 4},
						  {5, 6, 7, 8},
						  {9, 10, 11, 12},
						  {13, 14, 15, 16} };
	Matrix4x4 mat4x4(5);
	std::cout << mat * mat4x4;

	return 0;
}