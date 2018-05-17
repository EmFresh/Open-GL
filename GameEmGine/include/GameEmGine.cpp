#include "GameEmGine.h"

void(*GameEmGine::_compileShaders)(), (*GameEmGine::_render)(), (*GameEmGine::_gameLoop)(), (*GameEmGine::_keyUp)(int, int), (*GameEmGine::_keyDown)(int, int);
GLFWwindow *GameEmGine::_window;
//GLFWmonitor *GameEngine::_monitor;
Colour GameEmGine::_colour {123,123,123};
int GameEmGine::_numSprites;
std::map<int, Sprite *>* GameEmGine::_spriteArr = new std::map<int, Sprite *>;

GameEmGine::GameEmGine(std::string name, int monitor, int width, int height)
{
	glfwInit();			

	glfwDefaultWindowHints();
	//glfwWindowHint(GLFW_RESIZABLE, true);
	int monCount;
	glfwGetMonitors(&monCount);
	glViewport(0, 0, width, height);
	_window = glfwCreateWindow(width, height, (_title = name).c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(_window); //gives opengl the window it renders to  
	glfwSetFramebufferSizeCallback(_window, changeViewport);
	glfwSetKeyCallback(_window, keyUpdate);

	_fpsLimit = 60;
}

GameEmGine::~GameEmGine()
{
	glfwTerminate();
}

void GameEmGine::run()
{

	//vsync
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glClearColor((float)_colour.r * 255, (float)_colour.g * 255, (float)_colour.b * 255, (float)_colour.a * 255);//BG colour

	while(!glfwWindowShouldClose(_window))
	{
		glDepthFunc(GL_LEQUAL);
		update();
		if(0)
		{
			calculateFPS();
			char str[20];
			sprintf_s(str, "fps: %.2f", _fps);
			glfwSetWindowTitle(_window, (_title + "--> " + str).c_str());
		}
		//fpsLimiter();
	}
	glfwTerminate();
}

void GameEmGine::exit()
{
	glfwTerminate();
}

void GameEmGine::fpsLimit(short limit)
{
	_fpsLimit = limit;
}

void GameEmGine::vsync(bool enable)
{
	glfwSwapInterval(enable);
}

void GameEmGine::calculateFPS()
{
	static const int SAMPLE = 15;
	static short count;
	static float frameTimes[SAMPLE];

	frameTimes[count++] = 1 / glfwGetTime();
	if(count == SAMPLE)
	{
		count = 0;
		_fps = 0;
		for(auto &a : frameTimes)
			_fps += a;
		_fps /= SAMPLE;
	}

	glfwSetTime(0);
}

void GameEmGine::fpsLimiter()
{
	if(_fps > _fpsLimit)
	{
		int delay = _fpsLimit - _fps;
		float	currentTime = glfwGetTime();
		printf("delayed\n");
		while(glfwGetTime() - currentTime < delay);

	}
}

void GameEmGine::keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods)
{
	if(action == GLFW_RELEASE) //more of a stroke since release is only called if a key is pressed
	{
		if(_keyUp != nullptr)
			_keyUp(key, mods);
	} else
	{
		if(_keyUp != nullptr)
			_keyDown(key, mods);
	}
}

void GameEmGine::keyPressed(void key(int key, int mod))
{
	_keyDown = key;
	//glutKeyboardFunc((void(*)(unsigned char, int, int))key);//Letters only
	//glutSpecialFunc(key);//for non-Letter characters (i.e. "left arrow") 
}

void GameEmGine::keyReleased(void key(int key, int mod))
{
	_keyUp = key;
	//glutKeyboardUpFunc((void(*)(unsigned char, int, int))key);//Letters only
	//glutSpecialUpFunc(key);//for non-Letter characters (i.e. "left arrow")
}

void GameEmGine::renderUpdate(void update())
{
	_render = update;
}

void GameEmGine::shaderInit(void shaders())
{
	shaders();
}

void GameEmGine::gameLoopUpdate(void update())
{
	_gameLoop = update;
}

void GameEmGine::backgroundColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_colour = {GLubyte(r * 255),GLubyte(g * 255),GLubyte(b * 255),GLubyte(a * 255)};
}

int GameEmGine::getWindowWidth()
{
	int width;
	glfwGetWindowSize(_window, &width, nullptr);
	return width;
}

int GameEmGine::getWindowHeight()
{
	int height;
	glfwGetWindowSize(_window, nullptr, &height);
	return height;
}

void GameEmGine::addSprite(Sprite * sprite)
{
	if(!_tmpSpriteArr->insert({_tmpNumSprites++,sprite}).second)
		_tmpNumSprites--,
		printf("This sprite is already her!!\n\n");

	_spriteArr = _tmpSpriteArr;
	_numSprites = _tmpNumSprites;
}

void GameEmGine::removeSprite(int index)
{
	if(_tmpSpriteArr->erase(index))
		_tmpNumSprites--,
		printf("This sprite has been removed!!\n\n");
}

void GameEmGine::removeSprite(Sprite * sprite)
{
	for(int a = 0; a < _tmpNumSprites; a++)
		if(_tmpSpriteArr[0][a] == sprite)
			_tmpSpriteArr->erase(a),
			_tmpNumSprites--,
			printf("This sprite has been removed!!\n\n");
}

void GameEmGine::update()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	if(_render != nullptr)
		_render();
	for(int a = 0; a < _spriteArr->size(); a++)
	{
		//printf("Sprite #%d\n", a + 1);
		_spriteArr->find(a)->second->draw();
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();//updates the event handelers
	if(_gameLoop != nullptr)
		_gameLoop();
}

void GameEmGine::changeViewport(GLFWwindow *, int w, int h)
{

	//printf("Width : %d\n"
	//	   "Height: %d\n\n", w, h);

	glViewport(0, 0, w, h);
	//glFrustum(0, w, 0, h, -h, h);//eye view
	//glOrtho(-1, 1, -1, 1, -2, 10);//box view
}