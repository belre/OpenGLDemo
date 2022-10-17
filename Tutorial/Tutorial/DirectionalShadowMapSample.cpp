

#include <corecrt_math_defines.h>

#include "GlCommon.h"
#include "GlProgramSource.h"

#include <iostream>
#include <vector>
#include <math.h>

#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "CommonValue.h"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Texture.h"
#include "PointLight.h"
#include "Material.h"

#include <assimp\Importer.hpp>

#include "Model.h"

static std::vector<Mesh*> meshLists;
static std::vector<Shader*> shaderLists;

static Texture* brickTexture;
static Texture* dirtTexture;
static Texture* plainTexture;

static DirectionalLight* mainLight;
static PointLight pointLights[MAX_POINT_LIGHTS];
static SpotLight spotLights[MAX_SPOT_LIGHTS];

static Material* shinyMaterial;
static Material* dullMaterial;

static Model* blackhawk;
static Model* xwing;


static GLfloat deltaTime = 0.0f;
static GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "./Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "./Shaders/shader.frag";

static void CalcAverageNormals(unsigned int* indices, unsigned int indices_count,
	GLfloat* vertices, unsigned int vertices_count,
	unsigned int v_length, unsigned int normal_offset)
{
	for (size_t i = 0; i < vertices_count / v_length; i++)
	{
		unsigned int n_offset = i * v_length + normal_offset;
		vertices[n_offset] = 0.0f;
		vertices[n_offset + 1] = 0.0f;
		vertices[n_offset + 2] = 0.0f;
	}

	for (size_t i = 0; i < indices_count; i += 3)
	{
		unsigned int in0 = indices[i] * v_length;
		unsigned int in1 = indices[i + 1] * v_length;
		unsigned int in2 = indices[i + 2] * v_length;

		glm::vec3 v1(vertices[in1] - vertices[in0],
			vertices[in1 + 1] - vertices[in0 + 1],
			vertices[in1 + 2] - vertices[in0 + 2]);
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

	for (size_t i = 0; i < vertices_count / v_length; i++)
	{
		unsigned int n_offset = i * v_length + normal_offset;
		glm::vec3 vec(vertices[n_offset], vertices[n_offset + 1], vertices[n_offset + 2]);
		vec = glm::normalize(vec);
		vertices[n_offset] = vec.x;
		vertices[n_offset + 1] = vec.y;
		vertices[n_offset + 2] = vec.z;
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
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, -0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
	};

	unsigned int floor_indices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floor_vertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	CalcAverageNormals(indices, 12, vertices, 8 * 4, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 8 * 4, 12);
	meshLists.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 8 * 4, 12);
	meshLists.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floor_vertices, floor_indices, 8 * 4, 6);
	meshLists.push_back(obj3);
}

static void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderLists.push_back(shader1);
}


int RunDirectionalShadowSample()
{
	Window mainWindow = Window();
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();
	Camera camera(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-60.0f, 0.0f, 5.0f, 0.4f);

	brickTexture = new Texture("Textures/brick.png");
	brickTexture->LoadTextureAlpha();
	dirtTexture = new Texture("Textures/dirt.png");
	dirtTexture->LoadTextureAlpha();
	plainTexture = new Texture("Textures/plain.png");
	plainTexture->LoadTextureAlpha();

	shinyMaterial = new Material(4.0f, 256);
	dullMaterial = new Material(0.3f, 4);



	xwing = new Model();
	xwing->LoadModel("./Models/x-wing.obj");


	blackhawk = new Model();
	blackhawk->LoadModel("./Models/uh60.obj");


	mainLight = new DirectionalLight(
		1.0f, 1.0f, 1.0f, 0.5f, 0.4f,
		0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
		0.0f, 0.1f,
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
		0.0f, 0.1f,
		-4.0f, 2.0f, 0.0f,
		0.3f, 0.1f, 0.1f);
	pointLightCount++;

	pointLightCount = 0;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(
		1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	spotLights[1] = SpotLight(
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.5f, 0.0f,
		-100.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformEyePosition = 0;

	GLuint uniformSpecularIntensity = 0;
	GLuint uniformShininess = 0;

	glm::mat4 projection = glm::perspective(45.0f,
		(GLfloat)mainWindow.getRecommendedAspect(),
		0.1f, 100.0f);

	Assimp::Importer importer;

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
		uniformEyePosition = shaderLists[0]->GetEyePositionLocation();
		uniformSpecularIntensity = shaderLists[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderLists[0]->GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderLists[0]->SetDirectionalLight(mainLight);
		shaderLists[0]->SetPointLights(pointLights, pointLightCount);
		shaderLists[0]->SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture->UseTexture();
		shinyMaterial->UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshLists[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		dullMaterial->UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshLists[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		shinyMaterial->UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshLists[2]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial->UseMaterial(uniformSpecularIntensity, uniformShininess);
		xwing->RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.0f, 0.0f));
		model = glm::rotate(model, -90.0f * (float)M_PI / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial->UseMaterial(uniformSpecularIntensity, uniformShininess);
		blackhawk->RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}


	return 0;
}

