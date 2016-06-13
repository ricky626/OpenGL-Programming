#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

typedef struct Circle
{
	int x;
	int y;
	int r;
	int size;
	bool check;
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
float xx, yy;
Circle cir[10];
int size[10];

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1.0f);

	if (Mousecheck)
	{
		glPointSize(4);
		glBegin(GL_POINTS);

		for (int j = 0; j < 10; j++)
		{
			for (float i = 0; i < (3.14 * 2); i += 0.1)
			{
				cir[j].r = 50;
				glVertex2d((cir[j].r + size[j]) * cos(i) + cir[j].x,
					(cir[j].r + size[j]) * sin(i) + cir[j].y);
			}
		}

		glEnd();
	}


	glFlush(); //화면에 출력하기
}

int count = 0;
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int j = 0; j < 10; j++)
		{
			cir[j].x = x;
			cir[j].y = y;
			size[j] = 0;
		}
		if (!Mousecheck)
		{
			Mousecheck = true;
			glutTimerFunc(10, Timerfunction, 1);
		}

	}

	glutPostRedisplay();
}


void Timerfunction(int value)
{
	if (value == 1)
	{
		for (int j = 0; j < 10; j++)
			size[j]+=4;

		glutTimerFunc(10, Timerfunction, 1);
	}

	glutPostRedisplay();

}


