#pragma once

#include <cmath>

#include "Utils.h"
#include "glew.h"
#include "freeglut.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"


class CModel
{
public:
	CModel(GLuint* _program);
	~CModel();

	void Initialize(bool stencil);

	void CreateVBOForAttributes();
	void CreateVAOWithVBOS();
	void CreateIndexBuffer();

	void GetUniformLocations();

	void Render(GLfloat currentTime);
	void DrawStencil(glm::mat4 _translate, glm::mat4 _rotate, glm::mat4 _scale);

private:
	float m_fRotateAmount = .0f;

	GLuint& m_rProgram;
	int m_iIndicesCount;

	Vertex* m_pfVertices;
	GLuint* m_piIndices;

	GLuint m_iScaleLocation, m_iRotateLocation, m_iTranslateLocation, m_iViewLocation, m_iSampler;
	GLuint VAO, VBO, m_iPositionLocation, m_iColorLocation, EBO;
	bool isStencil, m_bStencil;
};

