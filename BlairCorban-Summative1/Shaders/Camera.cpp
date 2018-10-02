// This include 
#include "Camera.h"


CCamera::CCamera(GLuint* _program)
	:
	m_rProgram(*(_program))
{
	m_fAspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
	GetUniformLocation();
}


CCamera::~CCamera()
{
}

void CCamera::SetPosition(glm::vec3 _newPos)
{
	m_CameraPos += _newPos;
}

glm::vec3 CCamera::GetPosition()
{
	return m_CameraPos;
}

void CCamera::SetCameraFront(glm::vec3 _newFront)
{
	m_CameraFront = _newFront;
}

glm::vec3 CCamera::GetCameraFront()
{
	return m_CameraFront;
}

glm::vec3 CCamera::GetCameraUp()
{
	return m_CameraUp;
}

float CCamera::GetCameraSpeed()
{
	return m_fCameraSpeed;
}

void CCamera::GetUniformLocation()
{
	m_iViewLocation = glGetUniformLocation(m_rProgram, "gView");
	assert(m_iViewLocation != 0xFFFFFFFF);

	m_iPerspectiveLocation = glGetUniformLocation(m_rProgram, "gPerspective");
	assert(m_iPerspectiveLocation != 0xFFFFFFFF);
}

void CCamera::SendData()
{
	m_ViewMatrix = glm::lookAtRH(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
	m_PerspectiveMatrix = glm::perspectiveRH(glm::radians(30.0f), m_fAspectRatio, 1.0f, 100.0f);

	glUniformMatrix4fv(m_iViewLocation, 1, GL_FALSE, glm::value_ptr(m_ViewMatrix));
	glUniformMatrix4fv(m_iPerspectiveLocation, 1, GL_FALSE, glm::value_ptr(m_PerspectiveMatrix));

	glUniform3fv(glGetUniformLocation(m_rProgram, "gCameraPos"), 1, &m_CameraPos[0]);

}

glm::mat4 CCamera::GetViewMatrix()
{
	return m_ViewMatrix;
}

glm::mat4 CCamera::GetPerspectiveMatrix()
{
	return m_PerspectiveMatrix;
}