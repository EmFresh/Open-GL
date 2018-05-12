#pragma once
#include "GLSL_Compiler.h"
#include <GLFW\glfw3.h>
#include <string>
#include "Quaternion.h"
#include "Matrix.h"
#include "Logger.h"
//will get joystic input :>

class GameEngine
{
public:
	GameEngine(std::string name, int monitor = 0, int width = 200, int height = 100);
	~GameEngine();

	void run();

	/*
	Callback for whenever any key is pressed
	*/
	void keyPressed(void key(int key, int mod));
	/*
	Callback for whenever any key is released
	*/
	void keyReleased(void key(int key, int mod));
	/*
	What the game must render each update
	*/
	void renderUpdate(void update());
	/*
	 What the game must do each update
	*/
	void gameLoopUpdate(void update());
	/*
	Set background colour
	*/
	void backgroundColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	/*
	Gets window width in pixles
	*/
	int getWindowWidth();
	/*
	Gets window height in pixles
	*/
	int getWindowHeight();

private:
	static void keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods);
	static void update();
	static void changeViewport(GLFWwindow * win, int w, int h);
	static void(*_render)(), (*_gameLoop)(), (*_keyUp)(int, int), (*_keyDown)(int, int);
	static Quat _colour;
	int _width, _height;
	static GLFWwindow* _window;
	static GLFWmonitor* _monitor;
	GLSL_Compiler _colourProgram;
};

