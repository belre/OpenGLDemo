#pragma once

#include <string>
#include <GL/glew.h>




class Texture
{
public:
	Texture();
	Texture(std::string file_location);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	virtual ~Texture();

private:
	GLuint _texture_id;
	int _width, _height, _bit_depth;

	std::string _file_location;
};

