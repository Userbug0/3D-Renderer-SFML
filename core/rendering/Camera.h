#pragma once

#include "../Vector3.h"
#include "../Matrix4.h"


class Camera
{
public:
	Camera(const Vector3& position, const Vector3& direction = Vector3::forward);

	inline const Vector3& GetPosition()   const { return m_position; }
	inline const Vector3& GetDirection()  const { return m_direction; }

	inline void Move(const Vector3& offset)		 { m_position += offset; m_isUpdated = true; }
	inline void LookAt(const Vector3& direction) { m_direction = direction; m_isUpdated = true; }
	void LookAt(float offsetX, float offsetY);
	void LookAt(float offset);

	const Matrix4& GetViewMatrix();

private:
	void pointAt(const Vector3& target, const Vector3& up);

	bool m_isUpdated;
	float fYaw;
	Matrix4 m_viewMatrix;

	float m_rotationX;
	float m_rotationY;
	Vector3 m_position;
	Vector3 m_direction;
};
