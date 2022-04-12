#pragma once

#include <vector>
#include <initializer_list>

#include "Vector3.h"


class Triangle;
class Mesh;


class Triangle
{
public:
	Triangle() = default;
	Triangle(const std::initializer_list<Vector3>& list);
	~Triangle() = default;

	Vector3 operator[] (size_t index) const { return m_points[index]; } 
	Vector3& operator[] (size_t index) { return m_points[index]; } 

private:
	Vector3 m_points[3];
};


class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::initializer_list<Triangle>& list);
	~Mesh() = default;

	Triangle operator[] (size_t index) const { return m_array[index]; }
	Triangle& operator[] (size_t index) { return m_array[index]; } 

	size_t size() { return m_size; };

private:
	std::vector<Triangle> m_array;
	size_t m_size;
};

