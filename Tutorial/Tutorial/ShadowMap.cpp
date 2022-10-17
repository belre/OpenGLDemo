#include "ShadowMap.h"

#include <iostream>


ShadowMap::ShadowMap()
{
	_FBO = 0;
	_shadowMap = 0;
}

bool ShadowMap::Init(GLuint width, GLuint height)
{
	_shadowWidth = width;
	_shadowHeight = height;

	glGenFramebuffers(1, &_FBO);

	glGenTextures(1, &_shadowMap);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _shadowWidth, _shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE) 
	{
		std::cerr << "Frame buffer Error: " << status << std::endl;
		return false;
	}

	return true;
}

void ShadowMap::Write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
}


void ShadowMap::Read(GLenum texture_unit)
{
	glActiveTexture(texture_unit);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
}


ShadowMap::~ShadowMap()
{
	if(_FBO) 
	{
		glDeleteFramebuffers(1, &_FBO);
	}

	if(_shadowMap) 
	{
		glDeleteTextures(1, &_shadowMap);
	}
}
