#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

typedef struct Circle
{
	float x;
	float y;
	float r = 0;
	float theta = 0;
	float size = 0;
}Circle;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}

bool Mousecheck = false;


Circle cir[100];

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1.0f);

	glRectf(100, 100, 100, 100);
	if (Mousecheck)
	{
		glPointSize(4);

		glBegin(GL_POINTS);

		for (int i = 0; i < 100; i++)
		{
			glVertex2d((cir[i].r + cir[i].theta * 5) * cos(cir[i].theta) + cir[i].x,
				(cir[i].r + cir[i].theta * 5) * sin(cir[i].theta) + cir[i].y);
		}
		
		
		glEnd();
	}

	glFlush(); //화면에 출력하기
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 100; i++)
		{
			cir[i].x = x;
			cir[i].y = y;
		}

		
		if (!Mousecheck)
		{
			Mousecheck = true;
			glutTimerFunc(50, Timerfunction, 1);
		}

	}

	glutPostRedisplay();
}


void Timerfunction(int value)
{

	if (value == 1)
	{

		for (int i = 0; i < 100; i++)
			cir[i].theta -= 0.1f;

		glutTimerFunc(50, Timerfunction, 1);
		glutPostRedisplay();
	}
	



}


