#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <map>
#include <string>
#include "Quaternion.h"
#include "Matrix.h"
#include "Logger.h"
#include "Sprite.h"
#include "GLSLCompiler.h"
//will get joystic input latter :>

class GameEngine
{
public:
	GameEngine(std::string name, int monitor = 0, int width = 200, int height = 100);
	~GameEngine();

	/*
	Runs the engine.
	does not exit loop until window is exited
	*/
	void run();

	/*
	Exists the game
	*/
	void exit();

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
	  intializes any shaders
	*/
	void shaderInit(void shaders());
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


	void addSprite(Sprite* sprite);	 	

	void removeSprite(int index); 	

	void removeSprite(Sprite* sprite);
	
	void fpsLimit(short limit);
	void vsync(bool enable);

private:

	void calculateFPS();
	void fpsLimiter();

	static void keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods);
	static void update();
	static void changeViewport(GLFWwindow * win, int w, int h);
	static void(*_compileShaders)(), (*_render)(), (*_gameLoop)(), (*_keyUp)(int, int), (*_keyDown)(int, int);
	static Colour _colour;
	static GLFWwindow* _window;
	//static GLFWmonitor* _monitor;
	static std::map<int, Sprite *>*_spriteArr;
	static int _numSprites;
	std::map<int, Sprite *>*_tmpSpriteArr = new std::map<int, Sprite *>;
	int _tmpNumSprites;
	int _width, _height;
	float _fps;
	short _fpsLimit;
//	bool _vSync;
	std::string _title;
};

