#include "GameScene.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <iostream>
CGameScene* CGameScene::s_pGame = 0;

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
	while (!m_vecpModels.empty())
	{
		CModel* tempModel = m_vecpModels.back();
		m_vecpModels.pop_back();
		delete tempModel;
	}
	//while (!m_vecpTerrain.empty())
	//{
	//	TessModel* tempModel = m_vecpTerrain.back();
	//	m_vecpTerrain.pop_back();
	//	delete tempModel;
	//}

	if (m_pMainCamera != nullptr)
	{
		delete m_pMainCamera;
		m_pMainCamera = 0;
	}
}

//TessModel* CreateTerrain(const std::string& location)
//{
//
//	int w, h, channels;
//	unsigned char* image = stbi_load(location.c_str(), &w, &h, &channels, 0);
//	
//	//stbi_uc pixel = image[w * y + x];
//
//	std::vector<float> terrain = std::vector<float>(w * h);
//	std::vector<float>& heightMapData = terrain;
//	for (GLsizei r = 0; r < h; ++r)
//	{
//		for (GLsizei c = 0; c < w; ++c)
//		{
//			heightMapData[r * w + c] = image[(r * w + c) * channels] / 255.0f;
//		}
//
//	}
//
//	stbi_image_free(image);
//	/*for (GLsizei i = 0; i < heightMapData.size(); i++)
//	{
//		std::cout << heightMapData[i];
//	}*/
//	TessModel* meme;
//	
//
//	return meme;
//}


bool CGameScene::Initialise(GLuint* _program)
{
	m_pProgram = _program;

	if(!m_pMainCamera)
		m_pMainCamera = new CCamera(m_pProgram);

	TessModel* terrain = new TessModel(m_pProgram, m_pMainCamera);
	terrain->Initialize(TRUE);
	m_vecpTerrain.push_back(terrain);
	
	//CModel* bigcube = new CModel(m_pProgram);
	//bigcube->Initialize(TRUE);
	//m_vecpModels.push_back(bigcube);
	

	return true;
}

void CGameScene::RenderScene()
{
	glUseProgram(*m_pProgram);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat fCurrentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	fCurrentTime /= 1000;

	m_pMainCamera->SendData();

	glEnable(GL_SCISSOR_TEST);
	glScissor(0, WINDOW_HEIGHT / 8, WINDOW_WIDTH, (WINDOW_HEIGHT/4) * 3);
	

	for (unsigned int i = 0; i < m_vecpModels.size(); i++)
	{
		m_vecpModels[i]->Render(fCurrentTime);
	}
	for (unsigned int i = 0; i < m_vecpTerrain.size(); i++)
	{
		m_vecpTerrain[i]->Render(fCurrentTime);
	}

	glDisable(GL_SCISSOR_TEST);
	glutSwapBuffers();
}

CGameScene& CGameScene::GetInstance()
{

	if (s_pGame == 0)
	{
		s_pGame = new CGameScene();
	}

	return (*s_pGame);
	
}

void CGameScene::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CCamera* CGameScene::GetCamera()
{
	return m_pMainCamera;
}

void CGameScene::Update()
{
}

void CGameScene::RestartScene()
{
	while (!m_vecpModels.empty())
	{
		CModel* tempModel = m_vecpModels.back();
		m_vecpModels.pop_back();
		delete tempModel;
	}
	while (!m_vecpTerrain.empty())
	{
		TessModel* tempModel = m_vecpTerrain.back();
		m_vecpTerrain.pop_back();
		delete tempModel;
	}

	if (m_pMainCamera != nullptr)
	{
		delete m_pMainCamera;
		m_pMainCamera = 0;
	}

	Initialise(m_pProgram);
}

std::vector<CModel*> CGameScene::GetModels()
{
	return m_vecpModels;
}





