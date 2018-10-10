#pragma once

#include "Utils.h"
#include <string>
#include "glew.h"
#include "freeglut.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"
#include "Camera.h"


class TessModel
{
public:
	TessModel(GLuint* _program, CCamera* camera);
	~TessModel();

	void Initialize(bool stencil);

	void CreateVBOForAttributes();
	void CreateVAOWithVBOS();
	void CreateIndexBuffer();

	void GetUniformLocations();

	void Render(GLfloat currentTime);

private:
	float m_fRotateAmount = .0f;
	GLfloat points[12] = { -1.0f, -1.0f, 0.0f, 
		                  1.0f, -1.0f, 0.0f, 
		                  1.0f, 1.0f, 0.0f, 
		                 -1.0, 1.0, 0.0f };
	GLuint& m_rProgram;
	CCamera& m_rCamera;
	int m_iIndicesCount;

	Vertex* m_pfVertices;
	GLuint* m_piIndices;

	GLuint m_iScaleLocation, m_iRotateLocation, m_iTranslateLocation, m_iViewLocation, m_iSampler;
	GLuint VAO, VBO, m_iPositionLocation, m_iColorLocation, EBO;
	bool isStencil, m_bStencil;
};

