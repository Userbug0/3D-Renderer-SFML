#pragma once

#include <vector>
#include <initializer_list>

#include <SFML/Graphics.hpp>

#include "Vector3.h"


class Triangle;
class Mesh;


class Triangle
{
public:
	Triangle() = default;
	Triangle(const std::initializer_list<Vector3>& list);
	~Triangle() = default;

	void Draw(sf::RenderWindow* window);

	Vector3 operator[] (size_t index) const { return m_points[index]; } 
	Vector3& operator[] (size_t index) { return m_points[index]; } 
	
	// \return Normalized vector
	Vector3 GetNormal(); 

private:
	Vector3 m_points[3];
	sf::VertexArray m_toDraw;
};


class Mesh
{
public:
	Mesh() : m_size(0) {};
	Mesh(const std::initializer_list<Triangle>& list);
	~Mesh() = default;

	Triangle operator[] (size_t index) const { return m_array[index]; }
	Triangle& operator[] (size_t index) { return m_array[index]; } 

	auto begin() { return m_array.begin(); }
	auto end() { return m_array.end(); }

	size_t size() { return m_size; };

private:
	std::vector<Triangle> m_array;
	size_t m_size;
};

