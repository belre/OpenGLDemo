#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>

#include "CommonValue.h"
#include "DirectionalLight.h"
#include "PointLight.h"


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


	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);

private:
	int _pointLightCount;

	GLuint _shaderId, _uniformProjection, _uniformModel, _uniformView;
	GLuint _uniformEyePosition;
	GLuint _uniformSpecularIntensity, _uniformShininess;

	struct
	{
		GLuint _uniformColor;
		GLuint _uniformAmbientIntensity;
		GLuint _uniformDiffuseIntensity;

		GLuint _uniformDirectionalLight;
	} _uniformDirectionalLight;

	GLuint _uniformPointLightCount;

	struct
	{
		GLuint _uniformColor;
		GLuint _uniformAmbientIntensity;
		GLuint _uniformDiffuseIntensity;

		GLuint _uniformPosition;
		GLuint _uniformCoefConstant;
		GLuint _uniformCoefLinear;
		GLuint _uniformCoefExponent;
	} _uniformPointLight[MAX_POINT_LIGHTS];

	void CompileShader(const char* vertex_code, const char* fragment_code);

	void AddShader(GLuint the_program, const char* shader_code, GLenum shader_type);
};

