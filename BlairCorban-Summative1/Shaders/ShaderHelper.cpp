#include <iostream>
#include <fstream>
#include <conio.h>

#include "ShaderHelper.h"

ShaderHelper::ShaderHelper() {

}

std::string ShaderHelper::readShaderFileFromResource(const char* pFileName) {
	std::string outFile;
	try {
		std::ifstream f(pFileName);
		std::string line;
		while (std::getline(f, line)) {
			outFile.append(line);
			outFile.append("\n");
		}
		f.close();
	}
	catch (std::ifstream::failure e) {
		_getch();
		std::cerr << "Exception opening/reading/closing file\n";
	}
	return outFile;
}

GLuint ShaderHelper::compileVertexShader(const char* shaderCode) {
	return compileShader(GL_VERTEX_SHADER, shaderCode);
}

GLuint ShaderHelper::compileFragmentShader(const char* shaderCode) {
	return compileShader(GL_FRAGMENT_SHADER, shaderCode);
}

GLuint ShaderHelper::compileGeometryShader(const char* shaderCode) {
	return compileShader(GL_GEOMETRY_SHADER, shaderCode);
}

GLuint ShaderHelper::compileTessContShader(const char* shaderCode) {
	return compileShader(GL_TESS_CONTROL_SHADER, shaderCode);
}

GLuint ShaderHelper::compileTessEvalShader(const char* shaderCode) {
	return compileShader(GL_TESS_EVALUATION_SHADER, shaderCode);
}


GLuint ShaderHelper::compileShader(GLenum ShaderType, const char* shaderCode) {
	const  GLuint shaderObjectId = glCreateShader(ShaderType);
	if (shaderObjectId == 0) {
		std::cout << "Error creating shader type " << ShaderType << std::endl;
		_getch();

		exit(0);
	}
	const GLchar* p[1];
	p[0] = shaderCode;
	GLint Lengths[1];
	Lengths[0] = strlen(shaderCode);

	glShaderSource(shaderObjectId, 1, p, Lengths);
	glCompileShader(shaderObjectId);
	GLint compileStatus;
	glGetShaderiv(shaderObjectId, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderObjectId, 1024, NULL, InfoLog);
		std::cout << "Error compiling shader type" << ShaderType << std::endl << InfoLog << std::endl;
		_getch();

		exit(1);
	}

	return shaderObjectId;
}

//GLuint ShaderHelper::linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId, GLuint tessContShaderId, GLuint tessEvalShaderId) {
GLuint ShaderHelper::linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId) {
	GLint linkStatus = 0;
	GLchar ErrorLog[1024] = { 0 };
	const GLuint programObjectId = glCreateProgram();

	if (programObjectId == 0) {
		std::cout << "Error creating shader program " << std::endl;
		_getch();

		exit(1);
	}

	glAttachShader(programObjectId, vertexShaderId);
	glAttachShader(programObjectId, fragmentShaderId);
	//glAttachShader(programObjectId, tessContShaderId);
	//glAttachShader(programObjectId, tessEvalShaderId);

	glLinkProgram(programObjectId);

	glGetProgramiv(programObjectId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		glGetProgramInfoLog(programObjectId, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error linking shader program: " << std::endl << ErrorLog << std::endl;
		_getch();

		exit(1);
	}
	return programObjectId;
}

GLint ShaderHelper::validateProgram(GLuint programObjectId) {
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glValidateProgram(programObjectId);
	glGetProgramiv(programObjectId, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(programObjectId, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Invalid shader program: " << std::endl << ErrorLog;
		_getch();

		exit(1);
	}
	return Success;
}

//void ShaderHelper::compileAndLinkShaders(std::string vertex_shader, std::string fragment_shader,std::string geometry_shader, std::string tesscont_shader, std::string tesseval_shader, GLuint& program) {
void ShaderHelper::compileAndLinkShaders(std::string vertex_shader, std::string fragment_shader,std::string geometry_shader, GLuint& program) {
	std::string vertexShaderSource = ShaderHelper::readShaderFileFromResource(vertex_shader.c_str());
	std::string fragmentShaderSource = ShaderHelper::readShaderFileFromResource(fragment_shader.c_str());
	std::string geometryShaderSource = ShaderHelper::readShaderFileFromResource(geometry_shader.c_str());
	//std::string tesscontShaderSource = ShaderHelper::readShaderFileFromResource(tesscont_shader.c_str());
	//std::string tessevalShaderSource = ShaderHelper::readShaderFileFromResource(tesseval_shader.c_str());
	GLuint vertexShader = ShaderHelper::compileVertexShader(vertexShaderSource.c_str());
	GLuint fragmentShader = ShaderHelper::compileFragmentShader(fragmentShaderSource.c_str());
	GLuint geometryShader = ShaderHelper::compileGeometryShader(geometryShaderSource.c_str());
	//GLuint tesscontShader = ShaderHelper::compileTessContShader(tesscontShaderSource.c_str());
	//GLuint tessevalShader = ShaderHelper::compileTessEvalShader(tessevalShaderSource.c_str());
	//program = ShaderHelper::linkProgram(vertexShader, fragmentShader, tesscontShader, tessevalShader);
	program = ShaderHelper::linkProgram(vertexShader, fragmentShader);
	ShaderHelper::validateProgram(program);
}
