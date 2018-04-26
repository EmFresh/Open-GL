#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);
	glutSwapBuffers();
}

void main(int argA,char** argB)
{
	glutInit(&argA,argB);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

	glutInitWindowSize(500,500);

	glutCreateWindow("Hello glut");

	glutReshapeFunc(changeViewport);

	glutDisplayFunc(render);

	if(GLEW_OK != glewInit())
		return;
	
	glutMainLoop();
}