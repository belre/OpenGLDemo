#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{


public:
	Window(GLint windowWidth, GLint windowHeight);
	Window() : Window(800, 600)
	{

	}

	int Initialize();

	GLint getBufferWidth() { return _bufferWidth; }
	GLint getBufferHeight() { return _bufferHeight;  }
	GLfloat getRecommendedAspect() { return (GLfloat)_bufferWidth / (GLfloat)_bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(_mainWindow); }

	bool* getKeys() { return _keys; }

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(_mainWindow); }

	virtual ~Window();


private:

	GLFWwindow* _mainWindow;
	GLint _width;
	GLint _height;
	GLint _bufferWidth;
	GLint _bufferHeight;

	bool _keys[1024];

	GLfloat _lastX;
	GLfloat _lastY;
	GLfloat _changeX;
	GLfloat _changeY;
	bool _mouseFirstMoved;

private:

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double posX, double posY);
};

