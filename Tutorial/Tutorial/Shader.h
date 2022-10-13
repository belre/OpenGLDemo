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
	void CreateFromFiles(const char* vertex_location, const char* fragment_location);

	const std::string ReadFile(const char* file_location);

	GLuint GetProjectionLocation();

	GLuint GetModelLocation();

	GLuint GetViewLocation();

	GLuint GetAmbientIntensityLocation();

	GLuint GetAmbientColorLocation();

	GLuint GetDiffuseIntensityLocation();

	GLuint GetDirectionLocation();

	GLuint GetEyePositionLocation();

	GLuint GetSpecularIntensityLocation();

	GLuint GetShininessLocation();

	void UseShader();

	void ClearShader();

private:
	GLuint _shaderId, _uniformProjection, _uniformModel, _uniformView;
	GLuint _uniformAmbientIntensity, _uniformAmbientColor;
	GLuint _uniformDiffuseIntensity, _uniformDirection;

	GLuint _uniformEyePosition;
	GLuint _uniformSpecularIntensity, _uniformShininess;

	void CompileShader(const char* vertex_code, const char* fragment_code);

	void AddShader(GLuint the_program, const char* shader_code, GLenum shader_type);
};

