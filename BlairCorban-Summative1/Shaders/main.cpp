#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include <math.h>
#include <assert.h>
#include <iostream>

#include "glew.h"
#include "freeglut.h"
#include "ShaderHelper.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"
#include "Model.h"
#include "Camera.h"
#include "Utils.h"
#include "GameScene.h"
#include "stb_image.h"

#define BUTTON_UP 0
#define BUTTON_DOWN 1

#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

#define state ( (button_state== GLUT_DOWN) ? BUTTON_DOWN : BUTTON_UP )

GLuint g_iShaderProgram;
CGameScene& g_rGame = CGameScene::GetInstance();

GLfloat g_fYaw = 0.0f;
GLfloat g_fPitch = 0.0f;

GLfloat g_fLastX = WINDOW_WIDTH / 2.0;
GLfloat g_fLastY = WINDOW_HEIGHT / 2.0;

unsigned char keyState[260];
unsigned char mouseState[3];

CCamera* g_pMainCamera;

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
		case(GLUT_KEY_UP):
			{
				keyState[256] = BUTTON_DOWN;
				break;
			}
		case(GLUT_KEY_DOWN):
		{
			keyState[257] = BUTTON_DOWN;
			break;
		}
		case(GLUT_KEY_LEFT):
		{
			keyState[258] = BUTTON_DOWN;
			break;
		}
		case(GLUT_KEY_RIGHT):
		{
			keyState[259] = BUTTON_DOWN;
			break;
		}
		default:break;
	}
}


void SpecialInputUp(int key, int x, int y)
{
	switch (key)
	{
	case(GLUT_KEY_UP):
	{
		keyState[256] = BUTTON_UP;
		break;
	}
	case(GLUT_KEY_DOWN):
	{
		keyState[257] = BUTTON_UP;
		break;
	}
	case(GLUT_KEY_LEFT):
	{
		keyState[258] = BUTTON_UP;
		break;
	}
	case(GLUT_KEY_RIGHT):
	{
		keyState[259] = BUTTON_UP;
		break;
	}
	default:break;
	}
}

void ProcessInput()
{
	if (g_pMainCamera != nullptr)
	{
		if (keyState[(unsigned char)'w'] == BUTTON_DOWN || keyState[256] == BUTTON_DOWN) {
			g_pMainCamera->SetPosition(g_pMainCamera->GetCameraFront() * g_pMainCamera->GetCameraSpeed());
		}

		if (keyState[(unsigned char)'s'] == BUTTON_DOWN || keyState[257] == BUTTON_DOWN) {
			g_pMainCamera->SetPosition(-(g_pMainCamera->GetCameraFront() * g_pMainCamera->GetCameraSpeed()));
		}

		if (keyState[(unsigned char)'a'] == BUTTON_DOWN || keyState[258] == BUTTON_DOWN) {
			g_pMainCamera->SetPosition(-(glm::normalize(glm::cross(g_pMainCamera->GetCameraFront(), g_pMainCamera->GetCameraUp()))* g_pMainCamera->GetCameraSpeed()));
		}

		if (keyState[(unsigned char)'d'] == BUTTON_DOWN || keyState[259] == BUTTON_DOWN) {
			g_pMainCamera->SetPosition(glm::normalize(glm::cross(g_pMainCamera->GetCameraFront(), g_pMainCamera->GetCameraUp()))* g_pMainCamera->GetCameraSpeed());
		}

		if (keyState[27] == BUTTON_DOWN)
		{
			glutLeaveMainLoop();
			g_rGame.DestroyInstance();
		}

		if (keyState[(unsigned char)'r'] == BUTTON_DOWN || keyState[(unsigned char)'R'] == BUTTON_DOWN) {
			g_rGame.RestartScene();
			g_pMainCamera = g_rGame.GetCamera();
		}
	}
}
 
void Keyboard(unsigned char key, int x, int y) 
{
	keyState[tolower(key)] = BUTTON_DOWN;
}

void KeyboardUp(unsigned char key, int x, int y) 
{
	keyState[tolower(key)] = BUTTON_UP;
}

void Mouse(int button, int button_state, int x, int y) 
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{
			mouseState[MOUSE_LEFT] = state;
			break;
		}
		
		case GLUT_MIDDLE_BUTTON:
		{
			mouseState[MOUSE_MIDDLE] = state;
			break;
		}
		
		case GLUT_RIGHT_BUTTON:
		{
			mouseState[MOUSE_RIGHT] = state;
			break;
		}
	}
}

void Update()
{
	g_rGame.Update();
	ProcessInput();
	glutPostRedisplay();

}

void RenderSceneCB()
{
	g_rGame.RenderScene();
}

static void InitializeGlutCallBacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(Update);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInputUp);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT);
	glutCreateWindow("OpenGL");

	InitializeGlutCallBacks();

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Error: ," << glewGetErrorString(res);
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 1);

	ShaderHelper::compileAndLinkShaders("vertex_shader.glsl", "fragment_shader.glsl","geometry_shader.glsl", g_iShaderProgram);

	glActiveTexture(GL_TEXTURE0);

	if (!g_rGame.Initialise(&g_iShaderProgram))
	{
		std::cout << "Error intializing scene" << std::endl;
	}

	g_pMainCamera = g_rGame.GetCamera();
	
	glUseProgram(g_iShaderProgram);

	glutMainLoop();

	g_rGame.DestroyInstance();

	return 0;
}


