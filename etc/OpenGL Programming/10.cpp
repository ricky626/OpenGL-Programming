#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_CIRCLE 1000

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void init(void);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void rotation();

bool keyDown = false, bSinToCos = false, bChangeToCos = false;
int bMode = 0; int count = 0;
float drawX = -0.5f,drawY= 0;
float fMoveX = 0.f, fMoveY = 0.f, fRocate = 0.f, fRocate2 = 0.f, fcheck = 0, fScale = 1;
float sinX = 0, sinY = 0;
float radius = 0.3f;
float nBlue = 0, nRed = 1;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)
	init();

	glutTimerFunc(100, TimerFunction, 1);
	//glutSpecialFunc(SKeyboard);
	glutMouseFunc(Mouse); //마우스
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutReshapeFunc(Reshape); glutMainLoop();
}
float DEGINRAD = 3.14159 / 180;
float degInRad = 10.0f * DEGINRAD;
bool rocheck = false;

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	int a = 1;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기 

	glLoadIdentity();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-400, 0);
	glVertex2f(400, 0);
	glVertex2f(0, -300);
	glVertex2f(0, 300);
	glEnd();

	if (keyDown == 1)
	{
		glPushMatrix();

		glTranslatef(fMoveX, fMoveY, 0.0);
		glRotatef(fRocate, 0, 0, 1.0);
		glRotatef(fRocate2, fcheck, 0, 0.0);
		
		//glRotatef(fRocate, drawX * cos(degInRad) - drawY * sin(degInRad), drawX * sin(degInRad) + drawY * cos(degInRad), 1.0);

		glScalef(fScale, fScale, 0);
		if (bMode == 4) //rect
		{
			glColor3f(1, 0.0, 0);
			glRectf(-0.1,-0.1,0.1,0.1);
		}
		
		glBegin(GL_LINE_STRIP); 
		for (float fAngle = 0.f; fAngle < 25.f; fAngle += 0.1f)
		{
			if (bMode == 1){ //sin
				glColor3f(1.0, 0.0, 0.0);
				drawY = (sin(fAngle)  * radius);
				glVertex3f(drawX, drawY, 0.f );
				drawX += 0.005f;
			}
			else if (bMode == 2){ //cos
				glColor3f(1.0, 0.0, 0.0);
				drawY = (cos(fAngle)  * radius);
				glVertex3f(drawX, (cos(fAngle)  * radius), 0.f);
				drawX += 0.005f;
			}
			else if (bMode == 3) // Spring
			{
				glColor3f(nRed, 0.0, nBlue);
				drawY = (sin(fAngle) *radius);
				glVertex3f(cos(fAngle)*radius + drawX, drawY, 0.f);
				drawX += 0.005f;
				nRed -= 0.003;
				nBlue += 0.003;
			}
			else if (bMode == 5)
			{
				glColor3f(1.0, 0.0, 0.0);
				if (bChangeToCos)
					glVertex3f(drawX, (cos(fAngle)  * radius), 0.f);
				else if (!bChangeToCos)
					glVertex3f(drawX, (sin(fAngle)  * radius), 0.f);
				drawX += 0.005f;
			}
		}

		
		nRed = 1;
		nBlue = 0;
		drawX = -0.5f;

		glEnd();
		glPopMatrix();
	}



	//glFlush(); 
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, 800.0f, 600.0f, 0, -1.0, 1.0);
}


void init(void)
{
	
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void Keyboard(unsigned char key, int x, int y)
{

	keyDown = true;
	if (key == 'S' || key == 's')
		bMode = 1;
	if (key == 'C' || key == 'c')
		bMode = 2;
	if (key == 'P' || key == 'p')
		bMode = 3;
	if (key == 'Q' || key == 'q')
		bMode = 4;
	if (key == 'X')fMoveX += 0.1;
	if (key == 'x')fMoveX -= 0.1;
	if (key == 'Y')fMoveY += 0.1;
	if (key == 'y')fMoveY -= 0.1;
	if (key == 'R')
	{
		rocheck = true;
		fRocate += 10;
	}
	else if (key == 'r')
	{
		rocheck = false;
		fRocate += 10;
	}
	if (key == 'v' || key == 'V') fcheck = 0.5, fRocate2 += 10; else fcheck = 0;

	if (key == 'a')
		fScale += 0.1;
	else if (key == 'A')
		fScale -= 0.1;
	if (key == 'b' || key == 'B'){
		bSinToCos = true;
		bMode = 5;
	}
	if (key == 'i' || key == 'I') // 리셋
	{
		keyDown = false, bSinToCos = false, bChangeToCos = false;
		fMoveX = 0.f, fMoveY = 0.f, fRocate = 0.f, fcheck = 0, fScale = 1;
	}
	//if (key == 'E' || 'e')
	//	exit(1);
}

void TimerFunction(int value)
{
	if (bSinToCos)
	{
		if (radius <= 0)
			bChangeToCos = true;
		if (radius > 0.31)
			bSinToCos = false;

		if (bChangeToCos)
			radius += 0.002f;
		else 
			radius -= 0.002f;
	}
	else {
		radius = 0.3f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1); // 0.05초
}
//
//void rotation()
//{
//	float DEGINRAD = 3.14159 / 180;
//	float degInRad = 10.0f * DEGINRAD;
//
//	for (int i = 0; i < 1000; i++)
//	{
//		PointX[i] = (PointX[i] - 100) * cos(degInRad) - (PointY[i] - 75) * sin(degInRad);
//		PointY[i] = (PointX[i] - 100) * sin(degInRad) + (PointY[i] - 75) * cos(degInRad);
//	}
//	glutPostRedisplay();
//}