#pragma once
#include <GL/glew.h>

class UserPolygon
{
public:
	UserPolygon();
	virtual ~UserPolygon();

	void Create();
	void Render();
	void Clear();

private:
	GLuint VAO, VBO, IBO;
	GLsizei _indexCount;
};

