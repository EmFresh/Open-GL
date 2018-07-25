#include <GameEmGine.h>
#include <AudioPlayer.h>
#include <vector>



using namespace std;

float ang = .5, x = 0, y = 0, z = 0;
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

//creates a triangle in pixles
//void drawTriangle(float x, float y, float w, float h)
//{
//	Size winSize = {game.getWindowWidth(),	game.getWindowHeight()};
//	glBegin(GL_TRIANGLES);
//	glColor3f(1, 0, 0);
//	glVertex2f(x / winSize.row, (h / winSize.colum) + (y / winSize.colum));	//top
//	glColor3f(0, 1, 0);
//	glVertex2f(-(w / winSize.row) + (x / winSize.row), -(h / winSize.colum) + (y / winSize.colum));	//bottom m_left
//	glColor3f(0, 0, 1);
//	glVertex2f((w / winSize.row) + (x / winSize.row), -(h / winSize.colum) + (y / winSize.colum));	//bottom m_right
//	glEnd();
//}

//void drawPyrimid(Quat points[12], float width, float height)
//{
//	//Size winSize/* = {glutGet(GLUT_WINDOW_WIDTH),	glutGet(GLUT_WINDOW_HEIGHT)}*/;
//	//static Quaternion points[12];
//	//Front
//	glBegin(GL_TRIANGLES);
//	glColor4f(1, 0, 0, 1);
//	glVertex3f(points[0][1], points[0][2], points[0][3]);	//top
//	glColor4f(0, 1, 0, 1);
//	glVertex3f(points[1][1], points[1][2], points[1][3]);	//bottom m_left
//	glColor4f(0, 0, 1, 1);
//	glVertex3f(points[2][1], points[2][2], points[2][3]);	//bottom m_right
//	glEnd();
//
//	//Left
//	glBegin(GL_TRIANGLES);
//	glColor4f(1, 0, 0, 1);
//	glVertex3f(points[3][1], points[3][2], points[3][3]);	//top
//	glColor4f(0, 0, 1, 1);
//	glVertex3f(points[4][1], points[4][2], points[4][3]);	//bottom m_left
//	glColor4f(0, 1, 0, 1);
//	glVertex3f(points[5][1], points[5][2], points[5][3]);	//bottom m_right
//	glEnd();
//
//	//Back
//	glBegin(GL_TRIANGLES);
//	glColor4f(1, 0, 0, 1);
//	glVertex3f(points[6][1], points[6][2], points[6][3]);	//top
//	glColor4f(0, 1, 0, 1);
//	glVertex3f(points[7][1], points[7][2], points[7][3]);	//bottom m_left
//	glColor4f(0, 0, 1, 1);
//	glVertex3f(points[8][1], points[8][2], points[8][3]);	//bottom m_right
//	glEnd();
//
//	//Right
//	glBegin(GL_TRIANGLES);
//	glColor4f(1, 0, 0, 1);
//	glVertex3f(points[9][1], points[9][2], points[9][3]);	//top
//	glColor4f(0, 0, 1, 1);
//	glVertex3f(points[10][1], points[10][2], points[10][3]);	//bottom m_left
//	glColor4f(0, 1, 0, 1);
//	glVertex3f(points[11][1], points[11][2], points[11][3]);	//bottom m_right
//	glEnd();
//}

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


	printf("key RELEASED code: %d\n\n", key);
}


void update()
{
	////m_left-m_right rotation
	//if(m_left || m_right)
	//{
	//	points[0].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[1].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[2].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[3].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[4].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[5].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[6].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[7].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[8].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[9].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[10].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//	points[11].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	//}

	////m_up-m_down rotation
	//if(m_up || m_down)
	//{
	//	points[0].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[1].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[2].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[3].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[4].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[5].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[6].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[7].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[8].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[9].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[10].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//	points[11].rotate(m_up ? -ang : ang, m_up || m_down, 0, 0);
	//}


	////Z movement
	//if(m_up || m_down)
	//{
	//	points[0] += Quat {0,0,m_up ? ang : -ang};
	//	points[1] += Quat {0,0,m_up ? ang : -ang};
	//	points[2] += Quat {0,0,m_up ? ang : -ang};
	//	points[3] += Quat {0,0,m_up ? ang : -ang};
	//	points[4] += Quat {0,0,m_up ? ang : -ang};
	//	points[5] += Quat {0,0,m_up ? ang : -ang};
	//	points[6] += Quat {0,0,m_up ? ang : -ang};
	//	points[7] += Quat {0,0,m_up ? ang : -ang};
	//	points[8] += Quat {0,0,m_up ? ang : -ang};
	//	points[9] += Quat {0,0,m_up ? ang : -ang};
	//	points[10] += Quat {0,0,m_up ? ang : -ang};
	//	points[11] += Quat {0,0,m_up ? ang : -ang};
	//}
	//
	////scale
	//if(m_left || m_right)
	//{
	//	points[0].scale(m_right ? 1 + ang : 1 - ang);
	//	points[1].scale(m_right ? 1 + ang : 1 - ang);
	//	points[2].scale(m_right ? 1 + ang : 1 - ang);
	//	points[3].scale(m_right ? 1 + ang : 1 - ang);
	//	points[4].scale(m_right ? 1 + ang : 1 - ang);
	//	points[5].scale(m_right ? 1 + ang : 1 - ang);
	//	points[6].scale(m_right ? 1 + ang : 1 - ang);
	//	points[7].scale(m_right ? 1 + ang : 1 - ang);
	//	points[8].scale(m_right ? 1 + ang : 1 - ang);
	//	points[9].scale(m_right ? 1 + ang : 1 - ang);
	//	points[10].scale(m_right ? 1 + ang : 1 - ang);
	//	points[11].scale(m_right ? 1 + ang : 1 - ang);
	//}


	//if(m_left)
	//{
	//	printf("the triangle went m_left\n");
	//	x -= 10;
	//	printf("x: %f\n", x);
	//}
	//if(m_right)
	//{
	//	printf("the triangle went m_right\n");
	//	x += 10;
	//	printf("x: %f\n", x);
	//}
	//if(m_down)
	//{
	//	printf("the triangle went m_down\n");
	//	y -= 10;
	//	printf("y: %f\n", y);
	//}
	//if(m_up)
	//{
	//	printf("the triangle went m_up\n");
	//	y += 10;
	//	printf("y: %f\n", y);
	//}

	if(m_up)
		game.moveCameraBy({0,0,5});
	else if(m_down)
		game.moveCameraBy({0,0,-5});
	if(m_left)
		game.moveCameraBy({-5,0,0});
	else if(m_right)
		game.moveCameraBy({5,0,0});


	if(rotUp)
		game.moveAngleBy(ang,{5,0,0});
	else if(rotDown)	 
		game.moveAngleBy(ang, {-5,0,0});
	//if(rotUp)
	//	game.moveCameraBy({0,0,5});
	//else if(rotDown)
	//	game.moveCameraBy({0,0,-5});


	if(rotLeft)
		game.moveAngleBy(ang,{0,5,0});
	else if(rotRight)
		game.moveAngleBy(ang, {0,-5,0});
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
	//	Size winSize = {game.getWindowWidth(),	game.getWindowHeight()};
	//  //front
	//	points[0] = {false,0, (height / winSize.colum),0};  //top
	//	points[1] = {false,-(width / winSize.row), -(height / winSize.colum),  -(width / winSize.row)};//bottom m_left
	//	points[2] = {false,(width / winSize.row), -(height / winSize.colum),  -(width / winSize.row)}; //bottom m_right
	//   //m_left
	//	points[3] = points[0];
	//	points[4] = {false,-(width / winSize.row), -(height / winSize.colum), (width / winSize.row)};
	//	points[5] = points[1];
	//   //back
	//	points[6] = points[0];
	//	points[7] = {false,(width / winSize.row), -(height / winSize.colum),  (width / winSize.row)};
	//	points[8] = points[4];
	//   //m_right
	//	points[9] = points[0];
	//	points[10] = points[2];
	//	points[11] = points[7];



		//Sprite
		//	*sprite = new Sprite({{0,0}                 , {(float)game.getWindowWidth() / 2,(float)game.getWindowHeight()}}, "Assets/bleach.jpg"),
		//	*sprite2 = new Sprite({{(float)game.getWindowWidth() / 2, 0}, {(float)game.getWindowWidth() / 2,(float)game.getWindowHeight()}}, "Assets/bleach.jpg");
		//
		//game.addSprite(sprite);
		//game.addSprite(sprite2);

		//for(int a = 0; a < 998; a++)
		//	game.addSprite(new Sprite({{-.5,0}, {1,2}}, "Assets/RandomButton.png"));



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

	AudioPlayer player;
	Sound *sound = nullptr;

	player.createSound(&sound, "Menu Music (Main Loop).mp3");
	player.play(sound, true);

	//engine stuff
	//game.backgroundColour(.5, .5, .5);
	//game.shaderInit(shaderInit);
	game.keyPressed(keyInputPressed);
	game.keyReleased(keyInputReleased);
	game.renderUpdate(render);
	game.gameLoopUpdate(update);
	game.run();


}