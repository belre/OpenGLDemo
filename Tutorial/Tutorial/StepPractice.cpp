
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

	auto loops = step_data.GetClosedLoop();
	for(auto iter_loop = loops.begin(); iter_loop != loops.end() ; iter_loop++) 
	{
		std::vector<StepVertex> vertice_nodes;
		std::vector<unsigned int> indices;

		auto edges = iter_loop->GetEdges();

		std::vector<int> vertex_list;

		for(auto iter_edge = edges.begin(); iter_edge != edges.end(); iter_edge++) 
		{
			auto start_id = iter_edge->GetStartVertex().GetNodeId();
			auto end_id = iter_edge->GetEndVertex().GetNodeId();

			if(std::find(vertex_list.begin(), vertex_list.end(), start_id) == std::end(vertex_list) ) 
			{
				vertex_list.push_back(start_id);
			}

			if (std::find(vertex_list.begin(), vertex_list.end(), end_id) == std::end(vertex_list))
			{
				vertex_list.push_back(end_id);
			}
		}

		// register vertexes
		for(auto iter_v = vertex_list.begin(); iter_v != vertex_list.end(); iter_v++ ) 
		{
			auto node = step_data.GetVertex(*iter_v);
			vertice_nodes.push_back(node);
		}

		for(auto iter_edge = edges.begin() ; iter_edge != edges.end(); iter_edge++) 
		{
			auto start_node = iter_edge->GetStartVertex();
			auto end_node = iter_edge->GetEndVertex();

			auto iter_node_start = std::find_if(vertice_nodes.begin(), vertice_nodes.end(), 
				[start_node](StepVertex node) {				return node.GetNodeId() == start_node.GetNodeId();});

			auto iter_node_end = std::find_if(vertice_nodes.begin(), vertice_nodes.end(),
				[end_node](StepVertex node) {				return node.GetNodeId() == end_node.GetNodeId(); });

			// Register Indices
			if(iter_node_start != std::end(vertice_nodes) && iter_node_end != std::end(vertice_nodes)) 
			{
				int start_pos = std::distance(vertice_nodes.begin(), iter_node_start);
				int end_pos = std::distance(vertice_nodes.begin(), iter_node_end);

				indices.push_back(start_pos);
				indices.push_back(end_pos);
			}
		}

		std::vector<glm::vec3> vertices;

		// convert vertices nodes
		for (auto iter_v = vertice_nodes.begin(); iter_v != vertice_nodes.end(); iter_v++)
		{
			vertices.push_back(iter_v->GetPosition());
		}


		UserPolygon* polygon = new UserPolygon();
		polygon->Create(vertices, indices);
		polygonLists.push_back(polygon);
	}

}

static void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderLists.push_back(shader1);
}


int RunStepPractice()
{
	Window mainWindow(600, 600);
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


	/*
	glm::mat4 projection = glm::perspective(45.0f,
		(GLfloat)mainWindow.getRecommendedAspect(),
		0.1f, 100.0f);
*/
	glm::mat4 projection  = glm::ortho(-30.0f, 30.f, 30.0f, -30.0f, -100.0f, 100.0f);

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

		for(auto iter = polygonLists.begin() ; iter != polygonLists.end(); iter++)
		{
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			(*iter)->Render();
		}


		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

