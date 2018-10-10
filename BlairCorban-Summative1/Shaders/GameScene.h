#pragma once

#include <vector>

#include "glew.h"
#include "freeglut.h"

#include "Model.h"
#include "TessModel.h"
#include "Camera.h"
#include "Utils.h"

class CGameScene
{
public:
	~CGameScene();

	bool Initialise(GLuint* _program);
	void RenderScene();
	CCamera* GetCamera();
	void Update();

	void RestartScene();
	std::vector<CModel*> GetModels();

	static CGameScene& GetInstance();
	static void DestroyInstance();

protected:

private:
	CGameScene();

public:

protected:
	static CGameScene* s_pGame;

private:

	CCamera* m_pMainCamera;
	std::vector<CModel*> m_vecpModels;
	std::vector<TessModel*> m_vecpTerrain;
	GLuint* m_pProgram;
};

