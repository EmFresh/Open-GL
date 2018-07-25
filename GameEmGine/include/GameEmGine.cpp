#include "GameEmGine.h"
#include "AudioPlayer.h"

#pragma region Static Variables

void(*GameEmGine::m_compileShaders)(), (*GameEmGine::m_render)(), (*GameEmGine::m_gameLoop)();
Camera3D *GameEmGine::m_mainCamera, **GameEmGine::m_cameras;
GLSLCompiler *GameEmGine::m_cameraShader;
InputManager *GameEmGine::_inputManager;
WindowCreator *GameEmGine::_window;	//must be init in the constructor
ColourRGBA GameEmGine::m_colour {123,123,123};
SpriteBatch *GameEmGine::m_spriteBatch;
SpriteInfo** GameEmGine::_sprites = new SpriteInfo*[0];
unsigned int GameEmGine::_numCameras, GameEmGine::_numSprites;
#pragma endregion

//std::map<int, Sprite *>* GameEmGine::_spriteArr = new std::map<int, Sprite *>;

GameEmGine::GameEmGine()
{}

GameEmGine::GameEmGine(std::string name, int width, int height, int x, int y, int monitor, bool fullScreen, bool visable)
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
	_inputManager = new InputManager;
	m_mainCamera = new Camera3D({(float)width,(float)height,500});

	shaderInit();

	m_spriteBatch = new SpriteBatch;
	m_spriteBatch->init();

	printf("created the window\n");
	_fpsLimit = 30;



}

void GameEmGine::run()
{

	//vsync
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glClearColor((float)m_colour.r / 255, (float)m_colour.g / 255, (float)m_colour.b / 255, (float)m_colour.a / 255);//BG colour

	glm::mat4 proj = glm::perspective(45.f, (float)_window->getScreenWidth() / _window->getScreenHeight(), 1.f, 1000.f);

	while(!glfwWindowShouldClose(_window->getWindow()))//update loop
	{
		glDepthFunc(GL_LEQUAL);
		update();
		glfwSwapBuffers(_window->getWindow());
		if(true)
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

void GameEmGine::shaderInit()
{
	m_cameraShader = new GLSLCompiler;
	m_cameraShader->compileShaders("Shaders/Texture.vtsh", "Shaders/Texture.fmsh");
	m_cameraShader->linkShaders();
}
					  /*
					  
					  */
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
		int delay = _fps - _fpsLimit;
		float	currentTime = glfwGetTime(), now;
		printf("delayed\n");
		while(((now = glfwGetTime()) - currentTime) < delay);
	}
}


void GameEmGine::keyPressed(void key(int key, int mod))
{
	_inputManager->keyPressedCallback(key);
}

void GameEmGine::keyReleased(void key(int key, int mod))
{
	_inputManager->keyReleasedCallback(key);
}

void GameEmGine::renderUpdate(void update())
{
	m_render = update;
}

void GameEmGine::shaderInit(void shaders())
{
	shaders();
}

void GameEmGine::gameLoopUpdate(void update())
{
	m_gameLoop = update;
}

void GameEmGine::backgroundColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_colour = {GLubyte(r * 255),GLubyte(g * 255),GLubyte(b * 255),GLubyte(a * 255)};
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
	m_mainCamera->moveBy(pos);
}

void GameEmGine::addSprite(SpriteInfo* sprite)
{
	_sprites = (SpriteInfo**)realloc(_sprites, sizeof(SpriteInfo*)*++_numSprites);
	_sprites[_numSprites - 1] = sprite;

//	if(!_tmpSpriteArr->insert({_tmpNumSprites++,sprite}).second)
//		_tmpNumSprites--,
//		printf("This sprite is already her!!\n\n");
//
//	_spriteArr = _tmpSpriteArr;
//	_numSprites = _tmpNumSprites;
}

void GameEmGine::removeSprite(int index)
{
	if(index < _numSprites)
	{
		memmove(_sprites + index, _sprites + index + 1, sizeof(SpriteInfo*)*(_numSprites - 1 - index));
		delete _sprites[--_numSprites];
	}
//	if(_tmpSpriteArr->erase(index))
//		_tmpNumSprites--,
//		printf("This sprite has been removed!!\n\n");
}

void GameEmGine::removeSprite(SpriteInfo * sprite)
{
//	for(int a = 0; a < _tmpNumSprites; a++)
//		if(_tmpSpriteArr[0][a] == sprite)
//			_tmpSpriteArr->erase(a),
//			_tmpNumSprites--,
//			printf("This sprite has been removed!!\n\n");
}

void GameEmGine::addCamera(Camera3D *cam)
{
	//Camera3D **tmp = new Camera3D*[++_numCameras];
	//memcpy(tmp, m_cameras, sizeof(Camera3D*)*(_numCameras - 1));
	//delete[] m_cameras;  //may cause error
	realloc(m_cameras, sizeof(Camera3D*)*++_numCameras);
	m_cameras[_numCameras - 1] = cam;
	//m_cameras = tmp;
}

void GameEmGine::update()
{
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_mainCamera->update();
	if(m_render != nullptr)
		m_render();


	m_spriteBatch->begin();
	for(int a = 0; a < _numSprites; a++)
	{
		m_cameraShader->enable();
		m_spriteBatch->draw(&_sprites[a]->objectInfo, _sprites[a]->depth, _sprites[a]->texture);
		if(a + 1 < _numSprites)
			a++,
			m_spriteBatch->draw(&_sprites[a]->objectInfo, _sprites[a]->depth, _sprites[a]->texture);
	}
	glUniformMatrix4fv(m_cameraShader->getUniformLocation("camera"), 1, GL_FALSE, &(m_mainCamera->getCameraMatrix()[0][0]));
	glUniformMatrix4fv(m_cameraShader->getUniformLocation("object"), 1, GL_FALSE, &(m_mainCamera->getObjectMatrix()[0][0]));

	m_spriteBatch->end();
	m_spriteBatch->render();

	glfwPollEvents();//updates the event handelers

	if(m_gameLoop != nullptr)
		m_gameLoop();
}

void GameEmGine::changeViewport(GLFWwindow *, int w, int h)
{

	//printf("Width : %d\n"
	//	   "Height: %d\n\n", w, h);

	//_window->getScreenWidth(); //just for updating window width & height

	glViewport(0, 0, w, h);
	glFrustum(0, w, 0, h, 0, h);//eye view
	//glOrtho(0, 1, 0, 1, 0, 1);//box view
}