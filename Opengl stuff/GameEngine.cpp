#include "GameEngine.h"

void(*GameEngine::_render)(), (*GameEngine::_gameLoop)(), (*GameEngine::_keyUp)(int, int), (*GameEngine::_keyDown)(int, int);
GLFWwindow *GameEngine::_window;
GLFWmonitor *GameEngine::_monitor;
Quat GameEngine::_colour;

GameEngine::GameEngine(std::string name, int monitor, int width, int height)
{

	glfwInit();
	//shader initialization
	_colourProgram.compileShaders("Shaders/Colour Shading.vtsh", "Shaders/Colour Shading.fmsh");
	_colourProgram.addAtribute("vertPos");
	_colourProgram.linkShaders();

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_RESIZABLE, true);
	int monCount;
	glfwGetMonitors(&monCount);
	glViewport(0, 0, width, height);
	_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_window); //gives opengl the window it renders to  
	glfwSetFramebufferSizeCallback(_window, changeViewport);
	glfwSetKeyCallback(_window, keyUpdate);

	
}

GameEngine::~GameEngine()
{
	glfwTerminate();
}

void GameEngine::run()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(_colour.w, _colour.x, _colour.y, _colour.z);//BG colour
	while(!glfwWindowShouldClose(_window))
	{
		glDepthFunc(GL_LEQUAL);
		update();
	}
	glfwTerminate();
}

void GameEngine::keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods)
{
	if(action == GLFW_RELEASE) //more of a stroke since release is only called if a key is pressed
		_keyUp(key, mods);
	else
		_keyDown(key, mods);

}

void GameEngine::keyPressed(void key(int key, int mod))
{
	_keyDown = key;
	//glutKeyboardFunc((void(*)(unsigned char, int, int))key);//Letters only
	//glutSpecialFunc(key);//for non-Letter characters (i.e. "left arrow") 
}

void GameEngine::keyReleased(void key(int key, int mod))
{
	_keyUp = key;
	//glutKeyboardUpFunc((void(*)(unsigned char, int, int))key);//Letters only
	//glutSpecialUpFunc(key);//for non-Letter characters (i.e. "left arrow")
}

void GameEngine::renderUpdate(void update())
{
	_render = update;
}

void GameEngine::gameLoopUpdate(void update())
{
	_gameLoop = update;
}

void GameEngine::backgroundColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_colour = {r,g,b,a};
}

int GameEngine::getWindowWidth()
{
	int width;
	glfwGetWindowSize(_window, &width, nullptr);
	return width;
}

int GameEngine::getWindowHeight()
{
	int height;
	glfwGetWindowSize(_window, nullptr, &height);
	return height;
}

void GameEngine::update()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	_render();
	glfwSwapBuffers(_window);
	glfwPollEvents();//updates the event handelers
	_gameLoop();
}

void GameEngine::changeViewport(GLFWwindow *, int w, int h)
{
	glViewport(0, 0, w, h);
	glFrustum(-1, 1, -1, 1, -2, 10);//eye view
	//glOrtho(-1, 1, -1, 1, -2, 10);//box view
}