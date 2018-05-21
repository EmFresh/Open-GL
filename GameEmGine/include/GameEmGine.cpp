#include "GameEmGine.h"

void(*GameEmGine::_compileShaders)(), (*GameEmGine::_render)(), (*GameEmGine::_gameLoop)(), (*GameEmGine::_keyUp)(int, int), (*GameEmGine::_keyDown)(int, int);
Camera3D *GameEmGine::_mainCamera , **GameEmGine::_cameras;
GLSLCompiler *GameEmGine::_cameraShader;
WindowCreator *GameEmGine::_window;	//must be init in the constructor
Colour GameEmGine::_colour {123,123,123};
int GameEmGine::_numSprites;
std::map<int, Sprite *>* GameEmGine::_spriteArr = new std::map<int, Sprite *>;

GameEmGine::GameEmGine()
{}

GameEmGine::GameEmGine(std::string name, int monitor, int width, int height, int x, int y, bool fullScreen, bool visable)
{
	createWindow(name, width, height, x, y, monitor, fullScreen, visable);
}

GameEmGine::~GameEmGine()
{
	glfwTerminate();
}

void GameEmGine::createWindow(std::string name, int width, int height, int x, int y, int monitor, bool fullScreen, bool visable)
{
	glfwInit();
	//_window = new WindowCreator();

	printf("Try to create the window\n");
	_window = new WindowCreator(name, {(float)width,(float)height}, {(float)x,(float)y}, monitor, fullScreen, visable);
	glfwSetFramebufferSizeCallback(_window->getWindow(), changeViewport);
	glfwSetKeyCallback(_window->getWindow(), keyUpdate);
	
	_mainCamera = new Camera3D({(float)width,(float)height});

	_cameraShader = new GLSLCompiler;
	_cameraShader->compileShaders("Shaders/Colour Shading.vtsh", "Shaders/Colour Shading.fmsh");
	_cameraShader->linkShaders();

	printf("created the window\n");
	_fpsLimit = 30;
}

void GameEmGine::run()
{

	//vsync
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glClearColor((float)_colour.r / 255, (float)_colour.g / 255, (float)_colour.b / 255, (float)_colour.a / 255);//BG colour

	while(!glfwWindowShouldClose(_window->getWindow()))
	{
		glDepthFunc(GL_LEQUAL);
		update();
		glfwSwapBuffers(_window->getWindow());
		if(false)
		{
			calculateFPS();
			char str[20];
			sprintf_s(str, "fps: %.2f", _fps);
			glfwSetWindowTitle(_window->getWindow(), (_window->getTitle() + "--> " + str).c_str());
		}
	//	fpsLimiter();
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

WindowCreator* GameEmGine::getWindow()
{
	return _window;
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
		int delay = _fps-_fpsLimit ;
		float	currentTime = glfwGetTime(),now;
		printf("delayed\n");
		while(((now = glfwGetTime()) - currentTime) < delay);

	}
}

void GameEmGine::keyUpdate(GLFWwindow *, int key, int scancode, int action, int mods)
{
	if(action == GLFW_RELEASE) //more of a stroke since release is only called if a key is pressed then released
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
}

void GameEmGine::keyReleased(void key(int key, int mod))
{
	_keyUp = key;
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
	return _window->getScreenWidth();
}

int GameEmGine::getWindowHeight()
{
	return _window->getScreenHeight();
}

void GameEmGine::moveCameraBy(Coord3D pos)
{
	_mainCamera->moveBy(pos);
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

void GameEmGine::addCamera(Camera3D *cam)
{
	Camera3D **tmp = new Camera3D*[++_numCameras];
	memcpy(tmp, _cameras,sizeof(Camera3D*)*(_numCameras-1));
	tmp[_numCameras - 1] = cam;
	_cameras = tmp;
}

void GameEmGine::update()
{
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	 
	
	_mainCamera->update();	

	if(_render != nullptr)
		_render();
	for(int a = 0; a < _spriteArr->size(); a++)
	{
		//printf("Sprite #%d\n", a + 1);
		_spriteArr->find(a)->second->draw();
	}
//	_cameraShader->enable();
	glUniformMatrix4fv(_cameraShader->getUniformLocation("camera"), 1, GL_FALSE, &(_mainCamera->getCameraMatrix()[0][0]));
//	_cameraShader->disable();

	

	glfwPollEvents();//updates the event handelers
	if(_gameLoop != nullptr)
		_gameLoop();
}

void GameEmGine::changeViewport(GLFWwindow *, int w, int h)
{

	//printf("Width : %d\n"
	//	   "Height: %d\n\n", w, h);

	//_window->getScreenWidth(); //just for updating window width & height
	
	glViewport(0, 0, w, h);
	//glFrustum(0, w, 0, h, -h, h);//eye view
	//glOrtho(0, 1, 0, 1, 0, 1);//box view
}