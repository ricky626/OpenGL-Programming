#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Init();

void DrawLine();
void DrawSin();
void DrawCos();
void DrawSpring();
void DrawRect();

void rotation();

float PointX[1000] = { 0, };//점 정보
float PointY[1000] = { 0, };//점 정보

float xPos = 0, yPos = 0;//좌표
float moveX = 0.0f, moveY = 0.0f;//각 좌표 이동하는 거리

int check = 0;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutTimerFunc(500, Timerfunction, 1);
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}


GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawLine();


	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	
	switch (check)
	{
	case 1: //Sin
		DrawSin();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 1000; i++)
		{
			glVertex3f(PointX[i] + moveX, PointY[i] + moveY, 1.0f);
		}

		glEnd();
		break;

	case 2: //Cos
		DrawCos();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 1000; i++)
		{
			glVertex3f(PointX[i] + moveX, PointY[i] + moveY, 1.0f);
		}

		glEnd();
		break;

	case 3: //Spring
		DrawSpring();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 1000; i++)
		{
			glVertex3f(PointX[i] + moveX, PointY[i] + moveY, 1.0f);
		}

		glEnd();
		break;

	case 4: //Rectangle
		DrawRect();
		break;
	case 5:
		glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 1000; i++)
			{
				glVertex3f(PointX[i] + moveX, PointY[i] + moveY, 1.0f);
			}
		glEnd();
		break;
	}

	

	glutSwapBuffers(); //화면에 출력하기
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1') check = 1;
	else if (key == '2') check = 2;
	else if (key == '3') check = 3;
	else if (key == '4') check = 4;

	if (key == 'r' || key == 'R')
	{
		check = 5;
		rotation();
	}
	else if (key == 'l' || key == 'L')
	{
		moveY -= 10;
	}
	else if (key == '.')
	{
		moveY += 10;
	}
	else if (key == ',')
	{
		moveX -= 10;
	}
	else if (key == '/')
	{
		moveX += 10;
	}


	glutPostRedisplay();
}


void Timerfunction(int value)
{
	if (value == 1)
	{
	
	}

	glutPostRedisplay();

}

void Init()
{
	xPos = 0;
	yPos = 0;
	
	for (int i = 0; i < 1000; i++)
	{
		PointX[i] = xPos;
		PointY[i] = yPos;
	}
}

void DrawLine()
{
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glPointSize(1.0f);

	glBegin(GL_LINE_STRIP);
		glVertex3f(400.0f, 0.0f, 1.0f);
		glVertex3f(400.0f, 600.0f, 1.0f);
	glEnd();

	
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glPointSize(1.0f);

	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f, 300.0f, 1.0f);
		glVertex3f(800.0f, 300.0f, 1.0f);
	glEnd();
}

void DrawSin()
{
	Init();
	for (int i = 0; i < 1000; i++)
	{
		xPos += 10;
		yPos = sin(xPos * 3.14 / 180) * 100 + 300;
		PointX[i] = xPos;
		PointY[i] = yPos;
	}

}

void DrawCos()
{
	Init();
	for (int i = 0; i < 1000; i++)
	{
		xPos += 10;
		yPos = cos(xPos * 3.14 / 180) * 100 + 300;
		PointX[i] = xPos;
		PointY[i] = yPos;
	}

}

void DrawSpring()
{
	float radius = 100;//반지름

	float DEGINRAD = 3.14159 / 180;
	float degInRad = 0.0f;
	float Nums = 0;//x증가분
	float x_left = 400;//중심좌표
	float y_left = 300;//중심좌표

	Init();

	for (int i = 0; i < 1000; i++)
	{
		degInRad = i*DEGINRAD;
		PointX[i] = (cos(degInRad)*radius) + x_left + Nums + 200;
		PointY[i] = (sin(degInRad)*radius) + y_left;
		Nums -= 0.5;
	}
}

void DrawRect()
{
	
}

void rotation()
{
	float DEGINRAD = 3.14159 / 180;
	float degInRad = 10.0f * DEGINRAD;

	for (int i = 0; i < 1000; i++)
	{
		PointX[i] = (PointX[i]-100) * cos(degInRad) - (PointY[i]-75) * sin(degInRad);
		PointY[i] = (PointX[i]-100) * sin(degInRad) + (PointY[i]-75) * cos(degInRad);
	}
	glutPostRedisplay();
}