#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_moveSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_moveSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessKeyboard(CameraMovement direction,GLfloat deltaTime)
{
	GLfloat velocity = m_moveSpeed * deltaTime;
	if (direction == CameraMovement::FORWARD)
		m_position += m_front * velocity;
	if (direction == CameraMovement::BACKWARD)
		m_position -= m_front * velocity;
	if (direction == CameraMovement::LEFT)
		m_position -= m_right * velocity;
	if (direction == CameraMovement::RIGHT)
		m_position += m_right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset,GLfloat yoffset,GLboolean constrainPitch)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch -= yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	if (m_zoom >= 1.0f&&m_zoom <= 45.0f) {
		m_zoom -= yoffset;
	}
	if (m_zoom < 1.0f) {
		m_zoom = 1.0f;
	}
	if (m_zoom > 45.0f) {
		m_zoom = 45.0f;
	}

}
void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));

}