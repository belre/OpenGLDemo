
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
#include "StepData.h"
#include "UserPolygon.h"

static std::vector<Shader*> shaderLists;
static std::vector<UserPolygon*> polygonLists;

static GLfloat deltaTime = 0.0f;
static GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "./Shaders/user_shader.vert";

// Fragment Shader
static const char* fShader = "./Shaders/user_shader.frag";

static const char* stepPath = "./StepData/step_elements.csv";

static void CreateObjects(StepData& step_data)
{
	
	std::vector<glm::vec3> vertices = step_data.GetVertexPosition();

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);


	UserPolygon* polygon = new UserPolygon();
	polygon->Create(vertices, indices);
	polygonLists.push_back(polygon);



	/*
	

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshLists.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshLists.push_back(obj2);
	*/
}

static void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderLists.push_back(shader1);
}


int RunStepPractice()
{
	Window mainWindow(800, 600);
	mainWindow.Initialize();

	Camera camera(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 5.0f, 0.4f);

	StepData step_data;
	step_data.ReadFromTextData(stepPath);


	CreateObjects(step_data);
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;

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

		glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		polygonLists[0]->Render();

		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

