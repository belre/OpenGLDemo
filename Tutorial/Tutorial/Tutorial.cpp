// Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLint WIDTH = 800;
static const GLint HEIGHT = 600;


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
