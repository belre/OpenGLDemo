// Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GlCommon.h"
#include "GlProgramSource.h"

#include <iostream>
#include <stdlib.h>

#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

static const GLint WIDTH = 800;
static const GLint HEIGHT = 600;

static GLuint VAO, VBO, shader, uniformXMove;

static bool direction = true;
static float triOffset = 0.0f;
static float triMaxOffset = 0.7f;
static float triIncrement = 0.0005f;

// Vertex Shader
static const char* vShader = "		      \n\
#version 330														\n\
																				\n\
layout (location = 0) in vec3 pos;			\n\
																				\n\
uniform float xMove;										\n\
																				\n\
void main()															\n\
{																				\n\
	gl_Position = vec4(0.4 * pos.x + xMove, 0.4 * pos.y , pos.z , 1.0);		\n\
}";

// Fragment Shader
static const char* fShader = "		      \n\
#version 330														\n\
																				\n\
out vec4 color;													\n\
																				\n\
void main()															\n\
{																				\n\
	color = vec4(1.0, 0.0, 0.0, 1.0);		  \n\
}";

static void AddShader(GLuint the_program, const char* shader_code, GLenum shader_type)
{
	GLuint the_shader = glCreateShader(shader_type);

	const GLchar* the_code[1];
	the_code[0] = shader_code;

	GLint code_length[1];
	code_length[0] = strlen(shader_code);

	glShaderSource(the_shader, 1, the_code, code_length);
	glCompileShader(the_shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(the_shader, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error compiling the " << shader_type << " shader:'" << eLog << "'" << std::endl;
		return;
	}

	glAttachShader(the_program, the_shader);
}

static void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		std::cerr << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error linking program:" << eLog << std::endl;
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error validating program:" << eLog << std::endl;
		return;
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");

}



static void CreateObjects()
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



int RunXMovingTriangle()
{
	// Initialize GLFW
	if (!glfwInit())
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
	if (!main_window)
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

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialization failed" << std::endl;
		glfwDestroyWindow(main_window);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, buffer_width, buffer_height);

	CreateObjects();
	CompileShaders();

	// loop until window closed
	while (!glfwWindowShouldClose(main_window))
	{
		// Get and handle user input event
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glUniform1f(uniformXMove, triOffset);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(main_window);
	}

	return 0;
}
