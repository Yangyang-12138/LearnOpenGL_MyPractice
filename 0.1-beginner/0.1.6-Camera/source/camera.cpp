#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	:Front(glm::vec3(0.0, 0.0, -1.0)), 
	MovementSpeed(SPEED), 
	MouseSensitivity(SENSITIVITY), 
	Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVertors();
};

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
	updateCameraVertors();
};

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break;
	case BACKWARD:
		Position -= Front * velocity;
		break;
	case LEFT:
		Position -= Right * velocity;
		break;
	case RIGHT:
		Position += Right * velocity;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;


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
	updateCameraVertors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 0.001)
	{
		Zoom = 0.001;
	}
	if (Zoom > 89.9990)
	{
		Zoom = 89.999;
	}
}

void Camera::updateCameraVertors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}