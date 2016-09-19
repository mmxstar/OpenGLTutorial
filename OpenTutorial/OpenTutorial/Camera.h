#ifndef CAMERA_H
#define CAMERA_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum class CameraMovement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),
			GLfloat yaw = YAW,GLfloat pitch = PITCH);

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(GLfloat yoffset);

	//return zoom
	inline GLfloat getZoom() { return m_zoom; }
//private Metheds;
private:
	void updateCameraVectors();

private:
	glm::vec3 m_up;
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_yaw;
	GLfloat m_pitch;
	
	GLfloat m_moveSpeed;
	GLfloat m_mouseSensitivity;
	GLfloat m_zoom;
};
#endif // !CAMERA_H

