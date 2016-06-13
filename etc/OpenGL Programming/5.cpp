#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);
void Keyboard(unsigned char key, int x, int y);

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(500, Timerfunction, 1);
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
	int moveX = 3;
	int moveY = 3;
}Box;

#define MAXCOUNT 20

int count = 0;
int recount = 0;

Box* box = new Box[MAXCOUNT];

int sizeX = 40, sizeY = 20;

float r_color = 0.5f, g_color = 0, b_color = 0;


GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(r_color, g_color, b_color);

	for (int i = 0; i < MAXCOUNT; i++)
	{
		glRectd(box[i].x, box[i].y, box[i].x + sizeX, box[i].y + sizeY);
	}

	glFlush(); //화면에 출력하기
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A') // fast
	{
		for (int i = 0; i < MAXCOUNT; i++)
		{
			if (box[i].moveX < 0) box[i].moveX--;
			else if (box[i].moveX >= 0) box[i].moveX++;
			if (box[i].moveY < 0) box[i].moveY--;
			else if (box[i].moveX >= 0) box[i].moveY++;
		}
	}

	else if (key == 's' || key == 'S') // slow
	{
		for (int i = 0; i < MAXCOUNT; i++)
		{
			if (box[i].moveX < 0) box[i].moveX++;
			else if (box[i].moveX > 0) box[i].moveX--;

			if (box[i].moveY < 0) box[i].moveY++;
			else if (box[i].moveY > 0) box[i].moveY--;
		}
	}
}


bool movecheck = false;

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (movecheck == false)
		{
			glutTimerFunc(20, Timerfunction, 2);
			movecheck = true;
		}
			
		if (recount > MAXCOUNT-1)
			recount = 0;
		if (count > MAXCOUNT-1)
		{
			box[recount].x = rand() % 700;
			box[recount++].y = rand() % 500;
			return;
		}

		box[count].x = x;
		box[count++].y = y;
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
		swap3(&r_color, &g_color, &b_color);		

		glutTimerFunc(500, Timerfunction, 1);
	}

	else if (value == 2)
	{

		for (int i = 0; i < MAXCOUNT; i++)
		{
			box[i].x += box[i].moveX;
			box[i].y += box[i].moveY;

			if (box[i].x >= 800 - sizeX || box[i].x <= 0)
				box[i].moveX *= -1;
			if (box[i].y >= 600 - sizeY || box[i].y <= 0)
				box[i].moveY *= -1;
		}

		glutTimerFunc(20, Timerfunction, 2);
	}
		
	glutPostRedisplay();
	
}



