#include <GameEmGine.h>
#include <EmGineAudioPlayer.h>
#include <vector>



using namespace std;

float ang = 2;
int numModel = 0;
bool m_left = 0, m_right = 0, m_in = 0, m_out = 0, m_up = 0, m_down = 0,
rotLeft = 0, rotRight = 0, rotUp = 0, rotDown = 0;
EmGineAudioPlayer* omniPlayer;

#define modSize 3 
//float width = 250, height = 250;
//static Quat points[13];
GameEmGine game("The Real Game", 1000, 800, 0, 0, 0, false);
GLSLCompiler colourProgram, colourProgram2;
Logger tlog = Logger("New Log:>");
Model* mod[modSize];
//GLSLCompiler colourProg;

void shaderInit()
{
	//shader initialization
	colourProgram.compileShaders("Shaders/Colour Shading.vtsh", "Shaders/Colour Shading.fmsh");
	colourProgram.linkShaders();
	colourProgram2.compileShaders("Shaders/Colour Shading 2.vtsh", "Shaders/Colour Shading 2.fmsh");
	colourProgram2.linkShaders();
}

void keyInputPressed(int key, int mod)
{
	m_left = (key == 'A' ? true : m_left);
	m_right = (key == 'D' ? true : m_right);
	m_up = (key == 'E' ? true : m_up);
	m_down = (key == 'Q' ? true : m_down);
	m_in = (key == 'W' ? true : m_in);
	m_out = (key == 'S' ? true : m_out);

	rotLeft = (key == GLFW_KEY_LEFT ? true : rotLeft);
	rotRight = (key == GLFW_KEY_RIGHT ? true : rotRight);
	rotUp = (key == GLFW_KEY_UP ? true : rotUp);
	rotDown = (key == GLFW_KEY_DOWN ? true : rotDown);


	printf("key PRESED code: %d\n\n", key);
}

void keyInputReleased(int key, int mod)
{
	m_left = (key == 'A' ? false : m_left);
	m_right = (key == 'D' ? false : m_right);
	m_in = (key == 'W' ? false : m_in);
	m_out = (key == 'S' ? false : m_out);
	m_up = (key == 'E' ? false : m_up);
	m_down = (key == 'Q' ? false : m_down);

	rotLeft = (key == GLFW_KEY_LEFT ? false : rotLeft);
	rotRight = (key == GLFW_KEY_RIGHT ? false : rotRight);
	rotUp = (key == GLFW_KEY_UP ? false : rotUp);
	rotDown = (key == GLFW_KEY_DOWN ? false : rotDown);

	if(key == GLFW_KEY_KP_6)
		game.setFPSLimit(game.getFPSLimit() + 5);
	if(key == GLFW_KEY_KP_4)
		game.setFPSLimit(game.getFPSLimit() - 5);

	if(key == GLFW_KEY_F)
	{
		static bool full;
		game.getWindow()->setFullScreen(full = !full);
		printf("Full Screen: %s\n", full ? "true" : "false");
	}

	//if(key == GLFW_KEY_SPACE)
	//	numModel = (numModel < modSize - 1 ? numModel + 1 : 0);
	if(key == GLFW_KEY_SPACE)
		omniPlayer->stopAll();
	if(key == 'N')
		omniPlayer->play(true,true);
	if(key == 'M')
		omniPlayer->muteAll();
	if(key == 'I')
		printf 
		("Song %s\n",omniPlayer->isStoped()?"has stoped":"is playing");
	if(key == 'P')
		omniPlayer->pauseAll();


	if(key == 'R')
	{
		game.setCameraAngle(0, {1,1,1});
		game.setCameraPosition({0,0,0});
	}
	printf("key RELEASED code: %d\n\n", key);
}


void update()
{
	float move = 20;

	//Camera Movement
	if(m_in)
		mod[numModel]->getTransformer().translateBy(0, 0, move);
	else if(m_out)
		mod[numModel]->getTransformer().translateBy(0, 0, -move);
	if(m_up)
		mod[numModel]->getTransformer().translateBy(0, move, 0);
	else if(m_down)
		mod[numModel]->getTransformer().translateBy(0, -move, 0);
	if(m_right)
		mod[numModel]->getTransformer().translateBy(move, 0, 0);
	else if(m_left)
		mod[numModel]->getTransformer().translateBy(-move, 0, 0);



	if(game.isControllerConnected(0))
	{

		Xinput p1 = game.getController(0);

		p1.numButtons;
		p1.numSticks;

		if(Xinput::buttonPressed(p1.buttons.A))
			printf("%d\n", p1.buttons.A);

		game.moveCameraPositionBy({p1.sticks[LS].x * move , p1.sticks[LS].y * move,0});//move camera
		game.moveCameraAngleBy(ang * (abs(p1.sticks[RS].x) + abs(p1.sticks[RS].y)), {p1.sticks[RS].y  ,p1.sticks[RS].x, 0});//rotate camera
		game.moveCameraPositionBy({0 , 0,p1.triggers[LT] * -move});//move out
		game.moveCameraPositionBy({0 , 0,p1.triggers[RT] * move});//move in

	}

	//Rotate Camera
	if(rotUp)
		mod[numModel]->getTransformer().rotateBy({ang,0,0});
	else if(rotDown)
		mod[numModel]->getTransformer().rotateBy({-ang,0,0});
	if(rotLeft)
		mod[numModel]->getTransformer().rotateBy({0,-ang,0});
	else if(rotRight)
		mod[numModel]->getTransformer().rotateBy({0,ang,0});
}


void render()
{}

SpriteInfo sp1, sp2;

void main()
{
	tlog.writeLog("loggn\n");


	VboInfo2D info{{0,0}, {(float) game.getWindowWidth() / 2,(float) game.getWindowHeight() / 2}},
		info2{{(float) game.getWindowWidth() / 2,0}, {(float) game.getWindowWidth() / 2,(float) game.getWindowHeight() / 2}};
	//static Texture2D tex = ResourceManager::getTexture2D("Assets/bleach.jpg");

	for(int a = 0; a < 1000; a++)
	{
		sp1 = {info,"Assets/bleach.jpg",0},
			sp2 = {info2,"Assets/bleach.jpg",0};
		game.addSprite(&sp1);
		game.addSprite(&sp2);
	}


	Model* model = new Model("Models/crysis_nano_suit_2/scene.gltf");
	Model* model2 = new Model("Models/albeto/scene.gltf");
	//Model* succubus = new Model("Models/succubus/scene.gltf");
	mod[0] = model;
	mod[1] = model2;
	//mod[2] = succubus;

	//succubus->getTransformer().setPosition(500, 0, 0);
	//succubus->getTransformer().setScale(1);
	model2->getTransformer().setRotation({-90,0,0});
	model2->getTransformer().setScale(3);
	model->getTransformer().setScale(.15);
	model->getTransformer().setPosition(500, 0, 1000);
	//model->getTransformer().setRotation(90, {1,0,0});

	//game.addModelBatch("Models/crysis_nano_suit_2/scene.gltf");
	game.addModel(model);
	//game.addModel(model2);
	//game.addModel(succubus);

	EmGineAudioPlayer player;
	omniPlayer = &player;
	//Sound *sound = nullptr;
	
	player.createSound("Menu Music (Main Loop).mp3");
	player.createStream("Running running n'... forever.mp3");
	player.play();
	player.setVolume(-1);

	//engine stuff
	//game.backgroundColour(.3, 0, 0);
	//game.shaderInit(shaderInit);
	game.keyPressed(keyInputPressed);
	game.keyReleased(keyInputReleased);
	//game.renderUpdate(render);
	game.gameLoopUpdate(update);
	game.run();

	//the game ended... go home... please
}