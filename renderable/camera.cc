#include "renderable/camera.h"

#include <iostream>

Camera::Camera() :
	Position(glm::vec3( 0.0f, 0.0f, 3.0f )),
	WorldUp(glm::vec3( 0.0f, 1.0f, 0.0f )),
	Front(glm::vec3( 0.0f, 0.0f, -1.0f )),
	MovementSpeed(4.5f),
	MouseSensitivity(0.1f),
	Zoom(45.0f),
	Yaw(-90.0f),
	Pitch(0.0f)
{
	updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
	Position(position),
	WorldUp(up),
	Front(glm::vec3( 0.0f, 0.0f, -1.0f )),
	MovementSpeed(2.5f),
	MouseSensitivity(0.1f),
	Zoom(45.0f),
	Yaw(yaw),
	Pitch(pitch)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(Movement camMov, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (camMov == Movement::FORWARD) {
		Position += Front * velocity;
	}
	if (camMov == Movement::BACKWARD) {
		Position -= Front * velocity;
	}
	if (camMov == Movement::LEFT) {
		Position -= Right * velocity;
	}
	if (camMov == Movement::RIGHT) {
		Position += Right * velocity;
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw	+= xoffset;
	Pitch += yoffset;

	/* Check if the pitch is out of bounds */
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	/* Update after move */
	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f and Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	/* Calculate new front */
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	/* Calculate new Right and Up */
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up		= glm::normalize(glm::cross(Right, Front));
}
