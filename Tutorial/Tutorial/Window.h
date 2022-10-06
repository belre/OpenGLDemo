#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{


public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLint getBufferWidth() { return _bufferWidth; }
	GLint getBufferHeight() { return _bufferHeight;  }
	GLfloat getRecommendedAspect() { return (GLfloat)_bufferWidth / (GLfloat)_bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(_mainWindow); }

	void swapBuffers() { glfwSwapBuffers(_mainWindow); }

	
	virtual ~Window();


private:

	GLFWwindow* _mainWindow;
	GLint _width;
	GLint _height;


	GLint _bufferWidth;
	GLint _bufferHeight;

	bool _keys[1024];

private:

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

};

