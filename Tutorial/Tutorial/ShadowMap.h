#pragma once

#include <GL\glew.h>

class ShadowMap
{
public:
	ShadowMap();

	virtual bool Init(GLuint width, GLuint Height);

	virtual void Write();

	virtual void Read(GLenum texture_unit);

	GLuint GetShadowWidth()
	{
		return _shadowWidth;
	}

	GLuint GetShadowHeight()
	{
		return _shadowHeight;
	}

	virtual ~ShadowMap();

protected:
	GLuint _FBO, _shadowMap;
	GLuint _shadowWidth, _shadowHeight;

};

