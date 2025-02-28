#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0;
const float PITCH		= 0.0;
const float SPEED		= 2.5;
const float SENSITIVITY = 0.1;
const float ZOOM		= 45.0;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
		glm::vec3 up = glm::vec3(0.0, 1.0, 0.0),
		float yaw = YAW,
		float pitch = PITCH);
	Camera(float posX, float posY, float posZ,
		float upX, float upY, float upZ,
		float yaw, float pitch);
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:
	void updateCameraVectors();
};

#endif // !CAMERA_H
