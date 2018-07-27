#include <GameEmGine.h>
#include <EmGineAudioPlayer.h>
#include <vector>



using namespace std;

float ang = 2, x = 0, y = 0, z = 0;
bool m_left = 0, m_right = 0, m_up = 0, m_down = 0,
rotLeft = 0, rotRight = 0, rotUp = 0, rotDown = 0;

float width = 250, height = 250;
//static Quat points[13];
GameEmGine game("The Real Game", 1000, 800, 0, 0, 0, false);
GLSLCompiler colourProgram, colourProgram2;
Logger tlog = Logger("New Log:>");

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
	m_up = (key == 'W' ? true : m_up);
	m_down = (key == 'S' ? true : m_down);

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
	m_up = (key == 'W' ? false : m_up);
	m_down = (key == 'S' ? false : m_down);

	rotLeft = (key == GLFW_KEY_LEFT ? false : rotLeft);
	rotRight = (key == GLFW_KEY_RIGHT ? false : rotRight);
	rotUp = (key == GLFW_KEY_UP ? false : rotUp);
	rotDown = (key == GLFW_KEY_DOWN ? false : rotDown);

	if(key == GLFW_KEY_F)
	{
		static bool full;
		game.getWindow()->setFullScreen(full = !full);
		printf("Full Screen: %s\n", full ? "true" : "false");
	}

	if(key == 'R')
	{
		game.setCameraAngle(0, {1,1,1});
		game.setCameraPosition({0,0,0});
	}
	printf("key RELEASED code: %d\n\n", key);
}


void update()
{
	float move=10;
	if(m_up)
		game.moveCameraPositionBy({0,0,move});
	else if(m_down)
		game.moveCameraPositionBy({0,0,-move});
	if(m_left)
		game.moveCameraPositionBy({-move,0,0});
	else if(m_right)
		game.moveCameraPositionBy({move,0,0});


	if(rotUp)
		game.moveCameraAngleBy(ang,{5,0,0});
	else if(rotDown)	 
		game.moveCameraAngleBy(ang, {-5,0,0});
	
	if(rotLeft)
		game.moveCameraAngleBy(ang,{0,5,0});
	else if(rotRight)
		game.moveCameraAngleBy(ang, {0,-5,0});
}


void render()
{
	static float time;
	time += 0.01;



	//drawPyrimid(points, 250, 250);


	//sprite.setRotation(45);

	//glUniform1f(colourProgram.getUniformLocation("tm"), time);

	////colourProgram.enable();
	//sprite->draw();
	//sprite2->draw();
	//_colourProgram.disable();
	//_colourProgram2.enable();
	//sprite2.draw();
	//_colourProgram2.disable(); 
}
SpriteInfo sp1, sp2;
void main()
{
	tlog.writeLog("loggn\n");
	


	XboxController xbc;
	xbc.buttons.buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &xbc.numButtons);
	printf("Number of joysticks: %d\n", xbc.numButtons);

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
	game.addModel("Models/nanosuit.obj");

	EmGineAudioPlayer player;
	Sound *sound = nullptr;

	player.createSound(&sound, "Menu Music (Main Loop).mp3");
	player.play(sound, true);

	//engine stuff
	//game.backgroundColour(1, 0, 0);
	//game.shaderInit(shaderInit);
	game.keyPressed(keyInputPressed);
	game.keyReleased(keyInputReleased);
	game.renderUpdate(render);
	game.gameLoopUpdate(update);
	game.run();


}