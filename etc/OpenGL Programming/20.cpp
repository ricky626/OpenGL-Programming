#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
void DrawScene();
void Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

typedef struct Object
{
	float xTran;
	float yTran;
	float zTran;

	float xRot;
	float yRot;
	float zRot;
}Object;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)

	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	glutMainLoop();
}

float Vertex[][3]
{
	{ -100, 100, -100 }, // 0
	{ -100, 100, 100 }, // 1
	{ 100, 100, 100 }, // 2
	{ 100, 100, -100 }, // 3
	{ -100, -100, -100 },// 4
	{ -100, -100, 100 }, // 5
	{ 100, -100, 100 }, // 6
	{ 100, -100, -100 } // 7
};

Object Screen = {};
Object Box = {};
Object Circle[5] = {};
int Circount = 0;

float moveX[5], moveY[5];

float rectRed[4] = {255, 255, 0, 255};
float rectGreen[4] = {0, 255, 0, 0};
float rectBlue[4] = {0, 0, 255, 255};




// 윈도우 출력 함수
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

		glPushMatrix();

			glRotated(Box.zRot, 0, 0, 1);

			glBegin(GL_QUADS); //앞면을 봐야함
			
			glColor3f(rectRed[0], rectGreen[0], rectBlue[0]); //빨강
				glVertex3fv(Vertex[0]); //-100, 100, -100
				glVertex3fv(Vertex[3]); // 100, 100, -100
				glVertex3fv(Vertex[2]); // 100, 100, 100
				glVertex3fv(Vertex[1]); //-100, 100, 100

			glColor3f(rectRed[1], rectGreen[1], rectBlue[1]); //노랑
				glVertex3fv(Vertex[3]); // 100, 100, -100
				glVertex3fv(Vertex[7]); // 100, -100, -100
				glVertex3fv(Vertex[6]); // 100, -100, 100
				glVertex3fv(Vertex[2]); // 100, 100, 100

			glColor3f(1, 1, 1);//
				glVertex3fv(Vertex[0]); // -100, 100, -100
				glVertex3fv(Vertex[3]); // 100, 100, -100
				glVertex3fv(Vertex[7]); // 100, -100, -100
				glVertex3fv(Vertex[4]); // -100, -100, -100

			glColor3f(rectRed[2], rectGreen[2], rectBlue[2]); // 파랑
				glVertex3fv(Vertex[7]); // 100, -100, -100
				glVertex3fv(Vertex[4]); // -100, -100, -100
				glVertex3fv(Vertex[5]); // -100, -100, 100
				glVertex3fv(Vertex[6]); // 100, -100, 100

			glColor3f(rectRed[3], rectGreen[3], rectBlue[3]); // 보라
				glVertex3fv(Vertex[4]); // -100, -100, -100
				glVertex3fv(Vertex[0]); // -100, 100, -100
				glVertex3fv(Vertex[1]); // -100, 100, 100
				glVertex3fv(Vertex[5]); // -100, -100, 100

			glEnd();

		glPopMatrix();

		glPushMatrix();
			
			glColor3ub(0, 0, 0);

			for (int i = 0; i < Circount; i++)
			{
				glLoadIdentity();
				glTranslated(Circle[i].xTran, Circle[i].yTran, Circle[i].zTran);
				glutSolidSphere(5, 20, 20);
			}
			
		glPopMatrix();

	glPopMatrix();//카메라

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정 // 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1000.0); //투영 변환 ( 원근 투영 ) 

	glTranslatef(0.0, 0.0, -700.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	for (int i = 0; i < 5; i++)
	{
		moveX[i] = rand() % 4 + 1;
		moveY[i] = rand() % 4 + 1;
	}
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{

	}

	else if (key == GLUT_KEY_RIGHT)
	{

	}

	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')	Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;

	else if ((key == 'b' || key == 'B') && Circount < 5)
	{
		if (Circount == 0)
		{
			glutTimerFunc(20, TimerFunction, 1);
		}

		glLoadIdentity();
		Circount++;
	}

	glutPostRedisplay();
}

void swap3(float* r, float* g, float* b)
{
	float temp = *r;
	*r = *g;
	*g = *b;
	*b = temp;
}

void TimerFunction(int value)
{
	for (int i = 0; i < Circount; i++)
	{
		if (Circle[i].xTran > 97)
		{

			moveX[i] *= -1;
			swap3(&rectRed[1], &rectGreen[1], &rectBlue[1]);
		}
		if (Circle[i].xTran < -97)
		{
			moveX[i] *= -1;
			swap3(&rectRed[3], &rectGreen[3], &rectBlue[3]);
		}

		if (Circle[i].yTran < -97)
		{
			moveY[i] *= -1;
			swap3(&rectRed[2], &rectGreen[2], &rectBlue[2]);
		}
		if (Circle[i].yTran > 97)
		{
			moveY[i] *= -1;
			swap3(&rectRed[0], &rectGreen[0], &rectBlue[0]);
		}
		

		Circle[i].xTran += moveX[i];
		Circle[i].yTran += moveY[i];
	}

	

	glutTimerFunc(20, TimerFunction, 1);

	glutPostRedisplay();
}



void Mouse(int button, int state, int x, int y)
{
	static int mx = 0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x;
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (mx > x)
			Box.zRot += 10;
		else if (mx < x)
			Box.zRot -= 10;
	}

	glutPostRedisplay();
}