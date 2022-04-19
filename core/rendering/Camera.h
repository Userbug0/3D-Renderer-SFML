#pragma once

#include "../Vector3.h"


class Camera
{
public:
	Camera(const Vector3& position, const Vector3& direction = Vector3::forward);

	inline const Vector3& GetPosition() const { return m_position; }
	inline const Vector3& GetDirection() const { return m_direction; }

	inline void Move(const Vector3& offset) { m_position += offset; }

	void LookAt(const Vector3& direction);

private:
	Vector3 m_position;
	Vector3 m_direction;
};
