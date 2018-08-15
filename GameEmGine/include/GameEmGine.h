#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <vector>
#include <string>
#include "Logger.h"
//#include "EmGineAudioPlayer.h"
//#include "Sprite.h"
#include "GLSLCompiler.h"
#include "WindowCreator.h"
#include "Camera2D.h"
#include "Model.h"
#include "SpriteBatch.h"
#include "ModelBatch.h"
#include "InputManager.h"
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
	void createNewWindow(std::string name, int width, int height, int x = 0, int y = 0, int monitor = 0, bool fullScreen = false, bool visable = true);
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


	void moveCameraPositionBy(Coord3D pos);
	void setCameraPosition(Coord3D pos);
	void moveCameraAngleBy(float angle, Coord3D direction);
	void setCameraAngle(float angle, Coord3D direction);

	void addModel(Model* model);
	
	void addModelBatch(const char *model);

	void addSprite(SpriteInfo* sprite);

	void removeSprite(int index);

	void removeSprite(SpriteInfo* sprite);

	void addCamera(Camera3D* camera);


	void setFPSLimit(short limit);
	short getFPSLimit();

	void vsync(bool enable);

	WindowCreator * getWindow();

	/*Controller input*/

	int controllersConnected();

	bool isControllerConnected(int index);

	Xinput& getController(int index);


private:
	void shaderInit();
	void calculateFPS();
	void fpsLimiter();
	
	static void update();
	static void changeViewport(GLFWwindow * win, int w, int h);
	static void(*m_compileShaders)(), (*m_render)(), (*m_gameLoop)();
	static WindowCreator *m_window;
	static ColourRGBA m_colour;
	static Camera3D *m_mainCamera;
	static std::vector<Camera3D*> m_cameras;
	static GLSLCompiler *m_cameraShader, *m_modelShader;
	static ModelBatch* m_modelBatch;
	static SpriteBatch* m_spriteBatch;
	static InputManager *m_inputManager;
	static std::vector<Model*> m_models;
	static std::vector<SpriteInfo*> m_sprites;

	static float m_fps;
	static short m_fpsLimit;
};

