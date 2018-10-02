#include <array>
#include "Model.h"

CModel::CModel(GLuint* _program)
	:
	m_rProgram(*(_program))
{
	m_iIndicesCount = 24;
	m_pfVertices = SetCubeVertices();
	m_piIndices = SetIndices(24);
}


CModel::~CModel()
{
	delete m_pfVertices;
	m_pfVertices = 0;

	delete m_piIndices;
	m_piIndices = 0;
}

void CModel::Initialize(bool stencil)
{
	CreateVAOWithVBOS();
	GetUniformLocations();
	isStencil = stencil;
}

void CModel::CreateVBOForAttributes()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (m_iIndicesCount * 6) * sizeof(GLfloat), m_pfVertices, GL_STATIC_DRAW);

	m_iPositionLocation = glGetAttribLocation(m_rProgram, "a_position");
	glVertexAttribPointer(m_iPositionLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(m_iPositionLocation);

	m_iColorLocation = glGetAttribLocation(m_rProgram, "a_color");
	glVertexAttribPointer(m_iColorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(3));
	glEnableVertexAttribArray(m_iColorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CModel::CreateVAOWithVBOS()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	CreateVBOForAttributes();
	CreateIndexBuffer();
	glBindVertexArray(0);
}

void CModel::CreateIndexBuffer()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_iIndicesCount, m_piIndices, GL_STATIC_DRAW);
}

void CModel::GetUniformLocations()
{
	m_iScaleLocation = glGetUniformLocation(m_rProgram, "gScale");
	assert(m_iScaleLocation != 0xFFFFFFFF);

	m_iRotateLocation = glGetUniformLocation(m_rProgram, "gRotate");
	assert(m_iRotateLocation != 0xFFFFFFFF);

	m_iTranslateLocation = glGetUniformLocation(m_rProgram, "gTranslate");
	assert(m_iTranslateLocation != 0xFFFFFFFF);

}

void CModel::Render(GLfloat currentTime)
{
	
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	
	
	
	glEnable(GL_CULL_FACE);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	m_fRotateAmount += 1.0f;
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_fRotateAmount), glm::vec3(1.0f, 1, 1.0f));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-5.0f));

	glUniformMatrix4fv(m_iScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(m_iRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(m_iTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));
	glUniform1i(glGetUniformLocation(m_rProgram, "gStencil"), 0);
	glUniform1f(glGetUniformLocation(m_rProgram, "gTime"), currentTime);

	glDrawElements(GL_QUADS, m_iIndicesCount, GL_UNSIGNED_INT, 0);

	DrawStencil(Translate, Rotate, Scale);
	
	glBindVertexArray(0);
	glDisable(GL_CULL_FACE);
}

void CModel::DrawStencil(glm::mat4 _translate, glm::mat4 _rotate, glm::mat4 _scale)
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0xFF); 

	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(1 + 0.5f, 1 + 0.5f, 1 + 0.5f));
	glm::vec3 stencilColor = glm::vec3(1.0f, 1.0f, 1.0f);

	glUniformMatrix4fv(m_iScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(m_iRotateLocation, 1, GL_FALSE, glm::value_ptr(_rotate));
	glUniformMatrix4fv(m_iTranslateLocation, 1, GL_FALSE, glm::value_ptr(_translate));

	glUniform3fv(glGetUniformLocation(m_rProgram, "gStencilColor"), 1, &stencilColor[0]);
	glUniform1i(glGetUniformLocation(m_rProgram, "gStencil"), 1);

	glDrawElements(GL_QUADS, m_iIndicesCount, GL_UNSIGNED_INT, 0);

	glStencilMask(0xFF);
	glDisable(GL_STENCIL_TEST);
}

