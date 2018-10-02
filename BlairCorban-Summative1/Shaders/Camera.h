#pragma once
#include "glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"

#include "utils.h"

class CCamera
{
public:
	CCamera(GLuint* _program);
	~CCamera();

	void SetPosition(glm::vec3 _newPos);
	glm::vec3 GetPosition();

	void SetCameraFront(glm::vec3 _newFront);

	glm::vec3 GetCameraFront();
	glm::vec3 GetCameraUp();

	float GetCameraSpeed();

	void GetUniformLocation();
	void SendData();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetPerspectiveMatrix();

private:

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_PerspectiveMatrix;

	float m_fAspectRatio;

	GLuint m_iViewLocation, m_iPerspectiveLocation;

	glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float m_fCameraSpeed = 0.1f;

	GLuint& m_rProgram;

};

