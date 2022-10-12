#include "Texture.h"

#include <iostream>


Texture::Texture()
{
	Texture::Texture("");
}

Texture::Texture(std::string file_location)
{
	_texture_id = 0;
	_width = 0;
	_height = 0;
	_bit_depth = 0;
	_file_location = file_location;
}

void Texture::LoadTexture()
{
	unsigned char* tex_data = stbi_load(_file_location.c_str(), &_width, &_height, &_bit_depth, 0);

	if(!tex_data) 
	{
		std::cerr << "Failed to find:" << _file_location << std::endl;
		return;
	}

	glGenTextures(1, &_texture_id);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(tex_data);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_id);
}


void Texture::ClearTexture()
{
	glDeleteTextures(1, &_texture_id);
	_texture_id = 0;
	_width = 0;
	_height = 0;
	_bit_depth = 0;
	_file_location = "";
}


Texture::~Texture()
{
	ClearTexture();
}

