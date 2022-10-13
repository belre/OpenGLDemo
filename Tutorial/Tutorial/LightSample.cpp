

#include "GlCommon.h"
#include "GlProgramSource.h"

#include <iostream>
#include <vector>

#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

static std::vector<Mesh*> meshLists;
static std::vector<Shader*> shaderLists;

static Texture* brickTexture;
static Texture* dirtTexture;

static Light* mainLight;

static GLfloat deltaTime = 0.0f;
static GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "./Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "./Shaders/shader.frag";

void CalcAverageNormals(unsigned int* indices, unsigned int indices_count, 
	GLfloat* vertices, unsigned int vertices_count,
	unsigned int v_length, unsigned int normal_offset)
{
	for(size_t i = 0 ; i < indices_count; i += 3 ) 
	{
		unsigned int in0 = indices[i] * v_length;
		unsigned int in1 = indices[i+1] * v_length;
		unsigned int in2 = indices[i+2] * v_length;

		glm::vec3 v1(	vertices[in1] - vertices[in0],
									vertices[in1+1] - vertices[in0+1], 
									vertices[in1+2] - vertices[in0+2]);
		glm::vec3 v2(vertices[in2] - vertices[in0],
			vertices[in2 + 1] - vertices[in0 + 1],
			vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		in0 += normal_offset;
		in1 += normal_offset;
		in2 += normal_offset;
		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for(size_t i = 0; i < vertices_count / v_length; i++ ) 
	{
		unsigned int n_offset = i * v_length + normal_offset;
		glm::vec3 vec(vertices[n_offset], vertices[n_offset + 1], vertices[n_offset + 2]);
		vec = glm::normalize(vec);
		vertices[n_offset] = vec.x;
		vertices[n_offset+1] = vec.y;
		vertices[n_offset+2] = vec.z;
	}
}

static void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		// x, y, z, u, v, nx, ny, nz
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
	};

	CalcAverageNormals(indices, 12, vertices, 12, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 8 * 4, 12);
	meshLists.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 8 * 4, 12);
	meshLists.push_back(obj2);
}

static void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderLists.push_back(shader1);
}


int RunLightSample()
{
	Window mainWindow(800, 600);
	mainWindow.Initialize();

	Camera camera(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 5.0f, 0.4f);

	brickTexture = new Texture("Textures/brick.png");
	brickTexture->LoadTexture();
	dirtTexture = new Texture("Textures/dirt.png");
	dirtTexture->LoadTexture();

	mainLight = new Light(
		1.0f, 1.0f, 1.0f, 0.2f, 
		2.0f, -1.0f, -2.0f, 1.0f);
	
	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformAmbientIntensity = 0;
	GLuint uniformAmbientColor = 0;
	GLuint uniformDirection = 0;
	GLuint uniformDiffuseIntensity = 0;

	glm::mat4 projection = glm::perspective(45.0f,
		(GLfloat)mainWindow.getRecommendedAspect(),
		0.1f, 100.0f);

	// loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();			// SDL_GetPerformanceCounter();
		deltaTime = now - lastTime;				// (now - lastTime) * 1000 / SDL_GetPerformanceFrequency()
		lastTime = now;

		// Get and handle user input event
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderLists[0]->UseShader();
		uniformModel = shaderLists[0]->GetModelLocation();
		uniformProjection = shaderLists[0]->GetProjectionLocation();
		uniformView = shaderLists[0]->GetViewLocation();
		uniformAmbientColor = shaderLists[0]->GetAmbientColorLocation();
		uniformAmbientIntensity = shaderLists[0]->GetAmbientIntensityLocation();
		uniformDirection = shaderLists[0]->GetDirectionLocation();
		uniformDiffuseIntensity = shaderLists[0]->GetDiffuseIntensityLocation();

		mainLight->UseLight(uniformAmbientIntensity, uniformAmbientColor, 
			uniformDiffuseIntensity, uniformDirection);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		brickTexture->UseTexture();
		meshLists[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		meshLists[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

