#include "Camera.h"


Camera::Camera(const Vector3& position, const Vector3& direction)
	: m_position(position), m_direction(direction), fYaw(0), m_isUpdated(true)
{

}


void Camera::LookAt(float offset)
{
	fYaw += offset;
	m_direction = { -sinf(fYaw), 0, cosf(fYaw) };
	m_isUpdated = true;
}


const Matrix4& Camera::GetViewMatrix()
{
	if (m_isUpdated == true)
	{
		Vector3 target = m_position + m_direction;
		pointAt(target, Vector3::down);
		m_viewMatrix.QuickInverse();
		m_isUpdated = false;
	}

	return m_viewMatrix;
}


void Camera::pointAt(const Vector3& target, const Vector3& up)
{
	Vector3 newForward = (target - m_position);
	newForward.Normalize();
	Vector3 newUp = up - newForward * Vector3::DotProduct(up, newForward);
	newUp.Normalize();

	Vector3 newRight = Vector3::CrossProduct(newUp, newForward);

	m_viewMatrix[0][0] = newRight.x;	m_viewMatrix[0][1] = newRight.y;	m_viewMatrix[0][2] = newRight.z;	m_viewMatrix[0][3] = 0.0f;
	m_viewMatrix[1][0] = newUp.x;		m_viewMatrix[1][1] = newUp.y;		m_viewMatrix[1][2] = newUp.z;		m_viewMatrix[1][3] = 0.0f;
	m_viewMatrix[2][0] = newForward.x;	m_viewMatrix[2][1] = newForward.y;	m_viewMatrix[2][2] = newForward.z;	m_viewMatrix[2][3] = 0.0f;
	m_viewMatrix[3][0] = m_position.x;	m_viewMatrix[3][1] = m_position.y;	m_viewMatrix[3][2] = m_position.z;	m_viewMatrix[3][3] = 1.0f;
}
