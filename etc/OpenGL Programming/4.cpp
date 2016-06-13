#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

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
	glutTimerFunc(1000, Timerfunction, 1);
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}


int count = 0;
int recount = 0;
int* px = new int[10];
int* py = new int[10];
int sizeX = 40, sizeY = 20;
float r_color = 0.5f, g_color = 0, b_color = 0;


GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(r_color, g_color, b_color);

	for (int i = 0; i < 10; i++)
	{
		glRectd(px[i], py[i], px[i] + sizeX, py[i] + sizeY);
	}


	glFlush(); //화면에 출력하기
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (recount > 9)
			recount = 0;
		if (count > 9)
		{
			px[recount] = rand() % 700;
			py[recount++] = rand() % 500;
			return;
		}

		px[count] = x;
		py[count++] = y;
	}

	glutPostRedisplay();
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void swap3(float* r, float* g, float* b)
{
	float temp = *r;
	*r = *g;
	*g = *b;
	*b = temp;
}

void Timerfunction(int value)
{
	if (value == 1)
	{
		swap(&sizeX, &sizeY);
		swap3(&r_color, &g_color, &b_color);
	}
	

	glutPostRedisplay();
	glutTimerFunc(1000, Timerfunction, 1);
}



