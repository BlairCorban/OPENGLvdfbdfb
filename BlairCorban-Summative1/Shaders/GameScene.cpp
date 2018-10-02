#include "GameScene.h"
#include "stb_image.h"
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

	if (m_pMainCamera != nullptr)
	{
		delete m_pMainCamera;
		m_pMainCamera = 0;
	}
}

bool CGameScene::Initialise(GLuint* _program)
{
	m_pProgram = _program;

	if(!m_pMainCamera)
		m_pMainCamera = new CCamera(m_pProgram);

	CreateTerrain("heightmap.RAW");



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

void CreateTerrain(const std::string& location)
{
	int Xpixels, Ypixels, channels;
	unsigned char* heightmapImage = stbi_load(location.c_str(), &Xpixels, &Ypixels, &channels, 0);



	/*std::vector<float> terrain = std::vector<float>(Xpixels * Ypixels);
	for (GLsizei r = 0; r < Ypixels; r++)
	{
		for (GLsizei c = 0; r < Xpixels; c++)
		{
			terrain[r * Xpixels * c] = heightmapImage[(r * Xpixels * c) * channels] / 255.0f;
		}
	}
	*/


}


