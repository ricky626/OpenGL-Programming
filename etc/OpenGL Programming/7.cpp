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
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}

typedef struct Box
{
	int x;
	int y;
	int sizeX;
	int sizeY;
	int moveX = 1;
	int moveY = 1;
}Box;


#define MAXCOUNT 20

Box* box = new Box[MAXCOUNT];
Box enemy;

int count = 0;
bool enemycheck = false;



GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1.0f);

	for (int i = 0; i < MAXCOUNT; i++)
	{
		glRectd(box[i].x, box[i].y, box[i].x + box[i].sizeX, box[i].y + box[i].sizeY);
	}

	if (enemycheck)
	{
		glColor3f(1, 0, 0.0f);
		glRectd(enemy.x, enemy.y, enemy.x + 40, enemy.y + 40);
	}


	glFlush(); //화면에 출력하기
}


void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		enemy.x = x - 20;
		enemy.y = y - 20;
		enemycheck = true;
		glutTimerFunc(20, Timerfunction, 1);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		box[count].sizeX = (rand() % 2 + 1) * ((rand() % 4 + 1) * 10);
		box[count].sizeY = (rand() % 2 + 1) * ((rand() % 4 + 1) * 10);
		box[count].x = (rand() % 14) * 50 + 50;
		box[count++].y = (rand() % 11) * 50;
	}

	glutPostRedisplay();
}


void Timerfunction(int value)
{
	if (value == 1)
	{
		for (int i = 0; i < MAXCOUNT; i++)
		{
			if (box[i].x > enemy.x)
				box[i].x -= box[i].moveX;
			if (box[i].x < enemy.x)
				box[i].x += box[i].moveX;

			if (box[i].y > enemy.y)
				box[i].y -= box[i].moveY;
			if (box[i].y < enemy.y)
				box[i].y += box[i].moveY;
		}

		glutTimerFunc(100, Timerfunction, 1);
	}

	glutPostRedisplay();

}


