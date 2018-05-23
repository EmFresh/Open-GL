#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include "Logger.h"
#include "Sprite.h"
#include "GLSLCompiler.h"
#include "WindowCreator.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
//will get joystic input latter :>

class GameEmGine
{
public:
	GameEmGine();
	GameEmGine(std::string name, int width, int height, int x = 0, int y = 0, int monitor = 0, bool fullScreen = false, bool visable = true);
	~GameEmGine();


	/*
	Creates a new window
	*/
	void createWindow(std::string name, int width, int height, int x = 0, int y = 0, int monitor = 0, bool fullScreen = false, bool visable = true);
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
	static int getWindowWidth();
   /*
   Gets window height in pixles
   */
	static int getWindowHeight();


	void moveCameraBy(Coord3D pos);


	void addSprite(Sprite* sprite);

	void removeSprite(int index);

	void removeSprite(Sprite* sprite);

	void addCamera(Camera3D*);


	void fpsLimit(short limit);

	void vsync(bool enable);

	WindowCreator * getWindow();

private:
	void shaderInit();
	void calculateFPS();
	void fpsLimiter();

	static WindowCreator *_window;
	static void keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods);
	static void update();
	static void changeViewport(GLFWwindow * win, int w, int h);
	static void(*_compileShaders)(), (*_render)(), (*_gameLoop)(), (*_keyUp)(int, int), (*_keyDown)(int, int);
	static Colour _colour;
	static std::map<int, Sprite *>*_spriteArr;
	static int _numSprites;
	static Camera3D *_mainCamera, **_cameras;
	static GLSLCompiler *_cameraShader;
	//std::map<int, Sprite *>*_tmpSpriteArr = new std::map<int, Sprite *>;
	static SpriteBatch* _spriteBatch;
	int _tmpNumSprites, _numCameras;
	float _fps;
	short _fpsLimit;
//	bool _vSync;

};

