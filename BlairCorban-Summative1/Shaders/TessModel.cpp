#include <array>
#include "TessModel.h"

TessModel::TessModel(GLuint* _program, CCamera* camera)
	:
	m_rProgram(*(_program)), m_rCamera(*(camera))
{	
	//m_iIndicesCount = 24;
	//m_pfVertices = points;
	//m_piIndices = SetIndices(24);
}


TessModel::~TessModel()
{
	delete m_pfVertices;
	m_pfVertices = 0;

	delete m_piIndices;
	m_piIndices = 0;
}

void TessModel::Initialize(bool stencil)
{
	CreateVAOWithVBOS();
	GetUniformLocations();
	//isStencil = stencil;
}

void TessModel::CreateVBOForAttributes()
{
	glGenBuffers(1, &VBO); 
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glBindVertexArray(0);
}

void TessModel::CreateVAOWithVBOS()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	CreateVBOForAttributes();
	CreateIndexBuffer();
	glBindVertexArray(0);
}

void TessModel::CreateIndexBuffer()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_iIndicesCount, m_piIndices, GL_STATIC_DRAW);
}

void TessModel::GetUniformLocations()
{
	m_iScaleLocation = glGetUniformLocation(m_rProgram, "gScale");
	assert(m_iScaleLocation != 0xFFFFFFFF);

	m_iRotateLocation = glGetUniformLocation(m_rProgram, "gRotate");
	assert(m_iRotateLocation != 0xFFFFFFFF);

	m_iTranslateLocation = glGetUniformLocation(m_rProgram, "gTranslate");
	assert(m_iTranslateLocation != 0xFFFFFFFF);

}

void TessModel::Render(GLfloat currentTime)
{
	//printf("render terrain");
	glUseProgram(m_rProgram);
	glm::mat4 model; 
	glm::vec3 pos = glm::vec3(0, 0, -5);
	model = glm::translate(model, pos);
	glm::mat4 mvp = m_rCamera.GetPerspectiveMatrix() * m_rCamera.GetViewMatrix() * model;
	GLint mvLoc = glGetUniformLocation(m_rProgram, "mvp"); 
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvp));
	glBindVertexArray(VAO); 
	glDrawArrays(GL_PATCHES, 0, 4); 
	glBindVertexArray(0);

}

