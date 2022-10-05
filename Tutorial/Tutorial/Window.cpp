#include "Window.h"

Window::Window()
{
	_width = 800;
	_height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	_width = windowWidth;
	_height = windowHeight;
}

int Window::Initialize()
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

	_mainWindow = glfwCreateWindow(_width, _height, "Test Window", nullptr, nullptr);
	if (!_mainWindow)
	{
		std::cerr << "GLFW window creation failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int buffer_width, buffer_height;
	glfwGetFramebufferSize(_mainWindow, &buffer_width, &buffer_height);

	// Set context for GLEW to use
	glfwMakeContextCurrent(_mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialization failed" << std::endl;
		glfwDestroyWindow(_mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, buffer_width, buffer_height);
}


Window::~Window() {
	glfwDestroyWindow(_mainWindow);
	glfwTerminate();
}

