#pragma once

#include <vector>
#include <initializer_list>

#include <SFML/Graphics.hpp>

#include "../Vector3.h"


class Triangle
{
public:
	Triangle() = default;
	Triangle(const std::initializer_list<Vector3>& list);
	~Triangle() = default;

	void Draw(sf::RenderWindow* window);

	Vector3 operator[] (size_t index) const { return m_points[index]; } 
	Vector3& operator[] (size_t index) { return m_points[index]; } 
	
	sf::Color GetVertexColor(size_t i);
	void SetVertexColor(size_t i, const sf::Color& color);
	// \return Normalized vector
	Vector3 GetNormal() const; 

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

	inline Triangle operator[] (size_t index) const { return m_array[index]; }
	inline Triangle& operator[] (size_t index) { return m_array[index]; } 

	inline void AddTriangle(const Triangle& tri) { m_array.push_back(tri); ++m_size; }

	inline auto begin() { return m_array.begin(); }
	inline auto end() { return m_array.end(); }

	inline size_t size() const { return m_size; };
	inline void clear() { m_array.clear(); m_size = 0; }

private:
	std::vector<Triangle> m_array;
	size_t m_size;
};

