#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>

class UserPolygon
{
public:
	UserPolygon();
	virtual ~UserPolygon();

	void Create(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
	void Render();
	void Clear();

private:
	GLuint VAO, VBO, IBO;
	GLsizei _indexCount;
	GLsizei _number_vertices;
};

