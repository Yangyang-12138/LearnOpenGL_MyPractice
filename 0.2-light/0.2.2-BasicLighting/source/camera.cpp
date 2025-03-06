#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up,
	float yaw, float pitch)
	:Front(glm::vec3(0.0, 0.0, -1.0)),
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY),
	Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ,
	float upX, float upY, float upZ,
	float yaw, float pitch)
	:Front(glm::vec3(0.0, 0.0, -1.0)),
	MovementSpeed(SPEED),
	MouseSensitivity(SENSITIVITY),
	Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyBoard(Camera_Movement direction, float deltaTime)
{
	float veclocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		Position += Front * veclocity;
	}
	else if (direction == BACKWARD)
	{
		Position -= Front * veclocity;
	}
	else if (direction == LEFT)
	{
		Position -= Right * veclocity;
	}
	else if (direction == RIGHT)
	{
		Position += Right * veclocity;
	}
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 89.999)
		{
			Pitch = 89.999;
		}
		if (Pitch < -89.999)
		{
			Pitch = -89.999;
		}
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	Zoom -= (float)yOffset;
	if (Zoom < 0.001)
	{
		Zoom = 0.001;
	}
	if (Zoom > 89.999)
	{
		Zoom = 89.999;
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}