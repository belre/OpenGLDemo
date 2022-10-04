// Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLint WIDTH = 800;
static const GLint HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex Shader
static const char* vShader = "		      \n\
#version 330														\n\
																				\n\
layout (location = 0) in vec3 pos;			\n\
																				\n\
void main()															\n\
{																				\n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);		\n\
}";

static const char* fShader = "		      \n\
#version 330														\n\
																				\n\
out vec4 color;													\n\
																				\n\
void main()															\n\
{																				\n\
	color = vec4(1.0, 0.0, 0.0, 1.0);		  \n\
}";

void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}



int main()
{
	// Initialize GLFW
	if(!glfwInit()) 
	{
		std::cerr << "GLFW Init failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core Profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* main_window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
	if(!main_window) 
	{
		std::cerr << "GLFW window creation failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int buffer_width, buffer_height;
	glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

	// Set context for GLEW to use
	glfwMakeContextCurrent(main_window);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK) 
	{
		std::cerr << "GLEW Initialization failed" << std::endl;
		glfwDestroyWindow(main_window);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, buffer_width, buffer_height);

	// loop until window closed
	while(!glfwWindowShouldClose(main_window)) 
	{
		// Get and handle user input event
		glfwPollEvents();

		// Clear Window
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(main_window);
	}

	return 0;
}
