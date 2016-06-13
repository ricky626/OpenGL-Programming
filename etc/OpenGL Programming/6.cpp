#include <GL/glut.h> // includes gl.h glu.h
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

typedef struct Box
{
	int x;
	int y;
	int moveX = 10;
	int moveY = 10;
}Box;

float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)(x1 - x2) * (x1 - x2) + (float)(y1 - y2) * (y1 - y2)));
}

bool InCircle(int x, int y, int mx, int my, int BSIZE)
{
	if (LengthPts(x + BSIZE, y + BSIZE, mx, my) < BSIZE)
		return				true;
	else
		return				false;

}


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
#define MAXCOUNT 10

Box* box = new Box[MAXCOUNT];
Box* mem = new Box[MAXCOUNT];



GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);


	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAXCOUNT; i++)
	{
		glRectd(box[i].x, box[i].y, box[i].x + 50, box[i].y + 50);
	}


	glFlush(); //화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < MAXCOUNT; i++)
		{
			if (InCircle(box[i].x, box[i].y, x, y, 25))
			{
				glutTimerFunc(20, Timerfunction, 2);
			}
		}
	}

	glutPostRedisplay();
}


int i = 0;
int check[10] = { 0, };

void Timerfunction(int value)
{
	if (value == 2)
	{
		for (int i = 0; i < MAXCOUNT; i++)
		{
			if (box[i].x < 750 && box[i].y != 550 && box[i].x != 0 && check[i] == 0)
			{
				box[i].x += box[i].moveX;
				
			}

			if (box[i].x < mem[i].x && box[i].x >= 0 && box[i].y == mem[i].y && check[i] == 1)
			{
				if (box[i].x == mem[i].x && box[i].y == mem[i].y)
				{
					check[i] = 0;
				}
				else
					box[i].x += box[i].moveX;

			}

			if (box[i].x == 750 && box[i].y < 550)
			{
				box[i].y += box[i].moveY;
				check[i] = 1;
			}

			if (box[i].y == 550 && box[i].x > 0)
			{
				box[i].x -= box[i].moveX;
			}

			if (box[i].y <= 550 && box[i].x == 0 && box[i].y > mem[i].y)
			{
				box[i].y -= box[i].moveY;
			}
		}

		glutTimerFunc(20, Timerfunction, 2);
	}

	else if (value == 1 && i != MAXCOUNT)
	{
		box[i].x = (rand() % 14) * 50 + 50;
		box[i].y = (rand() % 11) * 50;

		mem[i].x = box[i].x;
		mem[i].y = box[i].y;

		i++;
		glutTimerFunc(500, Timerfunction, 1);
	}

	glutPostRedisplay();

}