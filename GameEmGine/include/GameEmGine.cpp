#include "GameEmGine.h"
#include "EmGineAudioPlayer.h"

#pragma region Static Variables
void(*GameEmGine::m_compileShaders)(), (*GameEmGine::m_render)(), (*GameEmGine::m_gameLoop)();
Camera3D *GameEmGine::m_mainCamera;
std::vector<Camera3D *>GameEmGine::m_cameras;
GLSLCompiler *GameEmGine::m_cameraShader, *GameEmGine::m_modelShader;
InputManager *GameEmGine::m_inputManager;
WindowCreator *GameEmGine::m_window;	//must be init in the constructor
ColourRGBA GameEmGine::m_colour{123,123,123};
ModelBatch *GameEmGine::m_modelBatch;
SpriteBatch *GameEmGine::m_spriteBatch;
std::vector<Model*> GameEmGine::m_models;
std::vector<SpriteInfo*> GameEmGine::m_sprites;

float GameEmGine::m_fps;
short GameEmGine::m_fpsLimit;
#pragma endregion

GameEmGine::GameEmGine()
{}

GameEmGine::GameEmGine(std::string name, int width, int height, int x, int y, int monitor, bool fullScreen, bool visable)
{
	createNewWindow(name, width, height, x, y, monitor, fullScreen, visable);
}

GameEmGine::~GameEmGine()
{
	glfwTerminate();
}

void GameEmGine::createNewWindow(std::string name, int width, int height, int x, int y, int monitor, bool fullScreen, bool visable)
{
	glfwInit();//initilize GLFW before ANYTHING

	printf("Trying to create the window\n");
	m_window = new WindowCreator(name, {(float) width,(float) height}, {(float) x,(float) y}, monitor, fullScreen, visable);
	glfwSetFramebufferSizeCallback(m_window->getWindow(), changeViewport);
	m_inputManager = new InputManager;
	m_mainCamera = new Camera3D({(float) width,(float) height,500});

	shaderInit();

	m_spriteBatch = new SpriteBatch;
	m_modelBatch = new ModelBatch;
	//m_spriteBatch->init();

	printf("created the window\n");
	m_fpsLimit = 20;
	//EmGineAudioPlayer::init();
}

void GameEmGine::run()
{


	//glfwSwapInterval(1);//vsync

	glEnable(GL_DEPTH_TEST);
	glClearColor((float) m_colour.r / 255, (float) m_colour.g / 255, (float) m_colour.b / 255, (float) m_colour.a / 255);//BG colour

	glm::mat4 proj = glm::perspective(45.f, (float) m_window->getScreenWidth() / m_window->getScreenHeight(), 1.f, 1000.f);

	while(!glfwWindowShouldClose(m_window->getWindow()))//update loop
	{
		//EmGineAudioPlayer::update();

		if(true)//fps calculation
		{
			calculateFPS();
			char str[20];
			sprintf_s(str, "fps: %.2f", m_fps);
			glfwSetWindowTitle(m_window->getWindow(), (m_window->getTitle() + "--> " + str).c_str());
		}
		glDepthFunc(GL_LEQUAL);
		InputManager::controllerUpdate();
		update();
		glfwSwapBuffers(m_window->getWindow());
		glFlush();
		fpsLimiter();
	}
	glfwTerminate();
}

void GameEmGine::exit()
{
	glfwTerminate();
}

void GameEmGine::setFPSLimit(short limit)
{
	m_fpsLimit = limit;
}

short GameEmGine::getFPSLimit()
{
	return m_fpsLimit;
}

void GameEmGine::vsync(bool enable)
{
	glfwSwapInterval(enable);
}

int GameEmGine::controllersConnected()
{
	return m_inputManager->controllersConnected();
}

bool GameEmGine::isControllerConnected(int index)
{
	return m_inputManager->isControllerConnected(index);
}

Xinput& GameEmGine::getController(int index)
{
	return m_inputManager->getController(index);
}

WindowCreator* GameEmGine::getWindow()
{
	return m_window;
}

void GameEmGine::shaderInit()
{
	m_cameraShader = new GLSLCompiler;
	m_cameraShader->create("Shaders/Texture.vtsh", "Shaders/Texture.fmsh");
	m_modelShader = new GLSLCompiler;
	m_modelShader->create("Shaders/Model.vtsh", "Shaders/Model.fmsh");
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
		m_fps = 0;
		for(auto &a : frameTimes)
			m_fps += a;
		m_fps /= SAMPLE;
	}

	glfwSetTime(0);
}

void GameEmGine::fpsLimiter()
{
	static bool enter = false;
	static clock_t frameStart;

	if(enter)
		if(m_fpsLimit > 0)
			while((CLOCKS_PER_SEC / m_fpsLimit) > (clock() - frameStart));

	frameStart = clock();

	enter = true;
}

void GameEmGine::keyPressed(void key(int key, int mod))
{
	m_inputManager->keyPressedCallback(key);
}

void GameEmGine::keyReleased(void key(int key, int mod))
{
	m_inputManager->keyReleasedCallback(key);
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
	return m_window->getScreenWidth();
}

int GameEmGine::getWindowHeight()
{
	return m_window->getScreenHeight();
}

void GameEmGine::moveCameraPositionBy(Coord3D pos)
{
	m_mainCamera->movePositionBy(pos);
}

void GameEmGine::setCameraPosition(Coord3D pos)
{
	m_mainCamera->setPosition(pos);
}

void GameEmGine::moveCameraAngleBy(float angle, Coord3D direction)
{
	m_mainCamera->moveAngleBy(angle, direction);
}

void GameEmGine::setCameraAngle(float angle, Coord3D direction)
{
	m_mainCamera->setAngle(angle, direction);
}

void GameEmGine::addModel(Model* model)
{
	//m_models = (Model**) realloc(m_models, sizeof(Model*)*++m_numModels);
	//m_models[m_numModels - 1] = model;

	m_models.push_back(model);
}

void GameEmGine::addModelBatch(const char * model)
{
	m_modelBatch->draw(model);
	m_modelBatch->end();
}

void GameEmGine::addSprite(SpriteInfo* sprite)
{
	m_sprites.push_back(sprite);

	//m_sprites = (SpriteInfo**) realloc(m_sprites, sizeof(SpriteInfo*)*++_numSprites);
	//m_sprites[_numSprites - 1] = sprite;
}

void GameEmGine::removeSprite(int index)
{
	m_sprites.erase(m_sprites.begin() + index);

	//if(index < _numSprites)
	//{
	//	memmove(m_sprites + index, m_sprites + index + 1, sizeof(SpriteInfo*)*(_numSprites - 1 - index));
	//	delete m_sprites[--_numSprites];
	//}
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


	//realloc(m_cameras, sizeof(Camera3D*)*++_numCameras);
	//m_cameras[_numCameras - 1] = cam;
}

void GameEmGine::update()
{
	glClearDepth(1.f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_mainCamera->update();
	if(m_render != nullptr)
		m_render();

	//3D-Graphics 1
	for(int a = 0; a < m_models.size(); a++)
		m_models[a]->render(*m_modelShader, *m_mainCamera);

	////3D-Graphics 2
	//m_modelBatch->render(*m_modelShader, *m_mainCamera);


	////2D-Graphics 
	//m_spriteBatch->begin();
	//for(int a = 0; a < m_sprites.size(); a++)
	//{
	//	m_spriteBatch->draw(&m_sprites[a]->objectInfo, m_sprites[a]->depth, m_sprites[a]->texture);
	//	if(a + 1 < m_sprites.size())
	//		a++,
	//		m_spriteBatch->draw(&m_sprites[a]->objectInfo, m_sprites[a]->depth, m_sprites[a]->texture);
	//}
	//m_spriteBatch->end();
	//m_spriteBatch->render(*m_cameraShader,*m_mainCamera);

	glfwPollEvents();//updates the event handelers

	if(m_gameLoop != nullptr)
		m_gameLoop();
}

void GameEmGine::changeViewport(GLFWwindow *, int w, int h)
{

	//printf("Width : %d\n"
	//	   "Height: %d\n\n", w, h);

	//m_window->getScreenWidth(); //just for updating window width & height

	glViewport(0, 0, w, h);
	//glFrustum(0, w, 0, h, 0, h);//eye view
	//glOrtho(0, 1, 0, 1, 0, 1);//box view
}