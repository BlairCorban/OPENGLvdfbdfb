#pragma once

#include <vector>

#include "glew.h"
#include "glm\glm.hpp"

#define BUFFER_OFFSET(i) ((GLvoid *)(i*sizeof(float)))
#define VALIDATE(a) if (!a) return (false)

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 800.0f

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;
};

static Vertex* SetCubeVertices()
{
	Vertex* vertices = new Vertex[24]
	{
		{{ 1.0f,  1.0f,  1.0f },{ 1.0f, 1.0f, 1 } },
		{{-1.0f,  1.0f,  1.0f },{ 0.0f, 0.0f, 0 } },
		{{-1.0f, -1.0f,  1.0f },{ 1.0f, 1.0f, 1 } },
		{{ 1.0f, -1.0f,  1.0f },{ 0.0f, 0.0f, 0 } },

		{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 0 } },
		{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1 } },
		{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0 } },
		{{-1.0f, -1.0f,  1.0f},{ 1.0f, 1.0f, 1 } },
		
		{{-1.0f,  1.0f, -1.0f },{ 1.0f, 1.0f, 1 } },
		{ { 1.0f,  1.0f, -1.0f },{ 0.0f, 0.0f, 0 } },
		{ { 1.0f, -1.0f, -1.0f },{ 1.0f, 1.0f, 1 } },
		{ { -1.0f, -1.0f, -1.0f },{ 0.0f, 0.0f, 0 } },
	
		{{1.0f,  1.0f, -1.0f},{ 0.0f, 0.0f, 0 } },
		{ { 1.0f,  1.0f,  1.0f },{ 1.0f, 1.0f, 1 } },
		{ { 1.0f, -1.0f,  1.0f },{ 0.0f, 0.0f, 0 } },
		{ { 1.0f, -1.0f, -1.0f },{ 1.0f, 1.0f, 1 } },
		
		{{ 1.0f,  1.0f, -1.0f },{ 1.0f, 1.0f, 1 } },
		{ { -1.0f,  1.0f, -1.0f },{ 0.0f, 0.0f, 0 } },
		{ { -1.0f,  1.0f,  1.0f },{ 1.0f, 1.0f, 1 } },
		{ { 1.0f,  1.0f,  1.0f },{ 0.0f, 0.0f, 0 } },
		
		{{-1.0f, -1.0f, -1.0f },{ 0.0f, 0.0f, 0 } },
		{ { 1.0f, -1.0f, -1.0f },{ 1.0f, 1.0f, 1 } },
		{ { 1.0f, -1.0f,  1.0f },{ 0.0f, 0.0f, 0 } },
		{ { -1.0f, -1.0f, 1.0f },{ 1.0f, 1.0f, 1 } },
	};

	return vertices;
}



static GLuint* SetIndices(int _iIndices)
{
	GLuint* indices = new GLuint[_iIndices];

	for (int i = 0; i < _iIndices; i++)
	{
		indices[i] = i;
	}

	return indices;
}
