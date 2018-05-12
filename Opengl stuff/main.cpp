#include "GameEngine.h"
#include <vector>


using namespace std;

float ang = .005, x = 0, y = 0, z = 0;
bool m_left = 0, m_right = 0, m_up = 0, m_down = 0;

float width = 250, height = 250;
static Quaternion points[13];
GameEngine *game = new GameEngine("The Real Game", 0, 1000, 800);
Logger tlog;

//GLSL_Compiler colourProg;



//creates a triangle in pixles
void drawTriangle(float x, float y, float w, float h)
{
	Size winSize = {game->getWindowWidth(),	game->getWindowHeight()};
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(x / winSize.row, (h / winSize.colum) + (y / winSize.colum));	//top
	glColor3f(0, 1, 0);
	glVertex2f(-(w / winSize.row) + (x / winSize.row), -(h / winSize.colum) + (y / winSize.colum));	//bottom left
	glColor3f(0, 0, 1);
	glVertex2f((w / winSize.row) + (x / winSize.row), -(h / winSize.colum) + (y / winSize.colum));	//bottom right
	glEnd();
}

void drawPyrimid(Quaternion points[12], float width, float height)
{
	Size winSize/* = {glutGet(GLUT_WINDOW_WIDTH),	glutGet(GLUT_WINDOW_HEIGHT)}*/;
	//static Quaternion points[12];
	//Front
	glBegin(GL_TRIANGLES);
	glColor4f(1, 0, 0, 1);
	glVertex3f(points[0][1], points[0][2], points[0][3]);	//top
	glColor4f(0, 1, 0, 1);
	glVertex3f(points[1][1], points[1][2], points[1][3]);	//bottom left
	glColor4f(0, 0, 1, 1);
	glVertex3f(points[2][1], points[2][2], points[2][3]);	//bottom right
	glEnd();

	//Left
	glBegin(GL_TRIANGLES);
	glColor4f(1, 0, 0, 1);
	glVertex3f(points[3][1], points[3][2], points[3][3]);	//top
	glColor4f(0, 0, 1, 1);
	glVertex3f(points[4][1], points[4][2], points[4][3]);	//bottom left
	glColor4f(0, 1, 0, 1);
	glVertex3f(points[5][1], points[5][2], points[5][3]);	//bottom right
	glEnd();

	//Back
	glBegin(GL_TRIANGLES);
	glColor4f(1, 0, 0, 1);
	glVertex3f(points[6][1], points[6][2], points[6][3]);	//top
	glColor4f(0, 1, 0, 1);
	glVertex3f(points[7][1], points[7][2], points[7][3]);	//bottom left
	glColor4f(0, 0, 1, 1);
	glVertex3f(points[8][1], points[8][2], points[8][3]);	//bottom right
	glEnd();

	//Right
	glBegin(GL_TRIANGLES);
	glColor4f(1, 0, 0, 1);
	glVertex3f(points[9][1], points[9][2], points[9][3]);	//top
	glColor4f(0, 0, 1, 1);
	glVertex3f(points[10][1], points[10][2], points[10][3]);	//bottom left
	glColor4f(0, 1, 0, 1);
	glVertex3f(points[11][1], points[11][2], points[11][3]);	//bottom right
	glEnd();
}

void keyInputPressed(int key, int mod)
{


	m_left = (key == GLFW_KEY_LEFT ? true : m_left);
	m_right = (key == GLFW_KEY_RIGHT ? true : m_right);
	m_up = (key == GLFW_KEY_UP ? true : m_up);
	m_down = (key == GLFW_KEY_DOWN ? true : m_down);


	printf("key PRESED code: %d\n\n", (int)key);
}
void keyInputReleased(int key, int mod)
{

	m_left = (key == GLFW_KEY_LEFT ? false : m_left);
	m_right = (key == GLFW_KEY_RIGHT ? false : m_right);
	m_up = (key == GLFW_KEY_UP ? false : m_up);
	m_down = (key == GLFW_KEY_DOWN ? false : m_down);

	if(key == GLFW_KEY_R)
	{
		Size winSize = {game->getWindowWidth(),	game->getWindowHeight()};
		//front
		points[0] = {false,0, (height / winSize.colum),0};  //top
		points[1] = {false,-(width / winSize.row), -(height / winSize.colum), 0 - (width / winSize.row)};//bottom left
		points[2] = {false,(width / winSize.row), -(height / winSize.colum), 0 - (width / winSize.row)}; //bottom right
																										 //left
		points[3] = points[0];
		points[4] = {false,-(width / winSize.row), -(height / winSize.colum), (width / winSize.row)};
		points[5] = points[1];
		//back
		points[6] = points[0];
		points[7] = {false,(width / winSize.row), -(height / winSize.colum),  (width / winSize.row)};
		points[8] = points[4];
		//right
		points[9] = points[0];
		points[10] = points[2];
		points[11] = points[7];
	}
	printf("key RELEASED code: %d\n\n", (int)key);
}


void update()
{
	//left-right rotation
	if(m_left || m_right)
	{
		points[0].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[1].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[2].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[3].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[4].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[5].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[6].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[7].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[8].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[9].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[10].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
		points[11].rotate(m_right ? -ang : ang, 0, m_left || m_right, 0);
	}

	////up-down rotation
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
	//	points[0] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[1] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[2] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[3] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[4] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[5] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[6] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[7] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[8] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[9] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[10] += Quat {0,0,0,m_up ? ang : -ang};
	//	points[11] += Quat {0,0,0,m_up ? ang : -ang};
	//}

	//scale
	if(m_left || m_right)
	{
		points[0].scale(m_right ? 1 + ang : 1 - ang);
		points[1].scale(m_right ? 1 + ang : 1 - ang);
		points[2].scale(m_right ? 1 + ang : 1 - ang);
		points[3].scale(m_right ? 1 + ang : 1 - ang);
		points[4].scale(m_right ? 1 + ang : 1 - ang);
		points[5].scale(m_right ? 1 + ang : 1 - ang);
		points[6].scale(m_right ? 1 + ang : 1 - ang);
		points[7].scale(m_right ? 1 + ang : 1 - ang);
		points[8].scale(m_right ? 1 + ang : 1 - ang);
		points[9].scale(m_right ? 1 + ang : 1 - ang);
		points[10].scale(m_right ? 1 + ang : 1 - ang);
		points[11].scale(m_right ? 1 + ang : 1 - ang);
	}


	if(m_left)
	{
		printf("the triangle went left\n");
		x -= 10;
		printf("x: %f\n", x);
	}
	if(m_right)
	{
		printf("the triangle went right\n");
		x += 10;
		printf("x: %f\n", x);
	}
	if(m_down)
	{
		printf("the triangle went down\n");
		y -= 10;
		printf("y: %f\n", y);
	}
	if(m_up)
	{
		printf("the triangle went up\n");
		y += 10;
		printf("y: %f\n", y);
	}


}

void render()
{

	drawPyrimid(points, 250, 250);

	//glFlush();
	update();
}

//Callback Example
void callBack(int thing(int, double))
{
	thing(2, 4);
}

void main(int argA, char** argB)
{
	Size winSize = {game->getWindowWidth(),	game->getWindowHeight()};
  //front
	points[0] = {false,0, (height / winSize.colum),0};  //top
	points[1] = {false,-(width / winSize.row), -(height / winSize.colum),  -(width / winSize.row)};//bottom left
	points[2] = {false,(width / winSize.row), -(height / winSize.colum),  -(width / winSize.row)}; //bottom right
   //left
	points[3] = points[0];
	points[4] = {false,-(width / winSize.row), -(height / winSize.colum), (width / winSize.row)};
	points[5] = points[1];
   //back
	points[6] = points[0];
	points[7] = {false,(width / winSize.row), -(height / winSize.colum),  (width / winSize.row)};
	points[8] = points[4];
   //right
	points[9] = points[0];
	points[10] = points[2];
	points[11] = points[7];


	//engine stuff
	game->backgroundColour(0, 0, 0);
	game->keyPressed(keyInputPressed);
	game->keyReleased(keyInputReleased);
	game->renderUpdate(render);
	game->gameLoopUpdate(update);
	game->run();


	//const Quaternion q1 {{0,5,0,0}};
	//Quaternion q2;
	//q1*q2;
	//q1.print();
	//Matrix m1 = &vector<vector<float>>{
	//{2.f,3.f},
	//{3.f,4.f},
	//{4,5}},
	//m2 = &vector<vector<float>> {
	//{3,4,5},
	//{2,3,4}
	//};
	//m1.print();
	//m2.print();
	//Matrix::matrixMulti(m1, m2).print();
	//
	//printf("%f\n",m1[2][0]);


}