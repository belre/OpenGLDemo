#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>


class Shader
{
public:
	Shader();
	virtual ~Shader();

	void CreateFromString(const char* vertex_code, const char* fragment_code);

	GLuint GetProjectionLocation();

	GLuint GetModelLocation();

	void UseShader();

	void ClearShader();

private:
	GLuint _shaderId, _uniformProjection, _uniformModel;

	void CompileShader(const char* vertex_code, const char* fragment_code);

	void AddShader(GLuint the_program, const char* shader_code, GLenum shader_type);
};

