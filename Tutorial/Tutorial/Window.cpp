#include "Window.h"

Window::Window()
{
	_width = 800;
	_height = 600;

	for(size_t i = 0; i < 1024; i++) 
	{
		_keys[i] = false;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	_width = windowWidth;
	_height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
	{
		_keys[i] = false;
	}
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
	glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(_mainWindow);

	createCallbacks();

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
	glViewport(0, 0, _bufferWidth, _bufferHeight);

	glfwSetWindowUserPointer(_mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(_mainWindow, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(key >= 0 && key < 1024) 
	{
		if(action == GLFW_PRESS) 
		{
			the_window->_keys[key] = true;
			std::cout << "Pressed:" << key << std::endl;
		}
		else if(action == GLFW_RELEASE) 
		{
			the_window->_keys[key] = false;
			std::cout << "Released:" << key << std::endl;
		}
	}
}


Window::~Window() {
	glfwDestroyWindow(_mainWindow);
	glfwTerminate();
}

