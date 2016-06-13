#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct Object
{
	float xTran;
	float yTran;
	float zTran;

	float xRot;
	float yRot;
	float zRot;

}Object;

using namespace std;
void DrawScene();
void Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);


void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

bool collision(Object Circle, Object Rect);
bool Leftcollision(Object Circle, Object Rect);
bool Rightcollision(Object Circle, Object Rect);
bool Upcollision(Object Circle, Object Rect);
bool Downcollision(Object Circle, Object Rect);


Object tower[7] = { 0, };

Object hero = { 0, };

Object area[2] = { 0, };

Object Screen = { 0, };

GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos[] = { 0.0f, 500.0f, 0.0f, 1.0f }; //조명위치
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void init()
{
	tower[0] = { -175, 25, 150 };
	tower[1] = { -175, 125, 0 };
	tower[2] = { -175, 100, -150 };
	tower[3] = { 0, 0, 0 };
	tower[4] = { 175, 50, 150 };
	tower[5] = { 175, 50, 0 };
	tower[6] = { 175, 50, -150 };

	area[0] = { 175, 50, 50 };
	area[1] = { 175, 50, 100 };

	hero.zTran = 100;

}

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)

	init();
	glutTimerFunc(500, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);

	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	glutMainLoop();
}


void DrawCoord(void)
{
	glPushMatrix();

	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	glColor3d(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	glColor3d(0, 0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);
	glEnd();
	glPopMatrix();
}

void DrawPiramid()
{
	glBegin(GL_TRIANGLES);

	// Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(50.0f, -50.0f, 50.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(50.0f, -50.0f, 50.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(50.0f, -50.0f, -50.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(50.0f, -50.0f, -50.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-50.0f, -50.0f, -50.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-50.0f, -50.0f, -50.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-50.0f, -50.0f, 50.0f);

	glEnd();   // Done drawing the pyramid
}

void door()
{
	glPushMatrix();

		glTranslated(175, 50, 150);

		glColor3f(1, 0.5, 0.5);
		glScaled(1, 3, 1);
		glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

		glTranslated(175, 50, 0);

		glColor3f(1, 0.5, 0.5);
		glScaled(1, 3, 1);
		glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

		glTranslated(175, 100, 75);

		glScaled(1, 1, 2);
		glColor3f(1, 0.5, 0.5);
		glutSolidCube(50);

	glPopMatrix();
}


void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot+45, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

		glPushMatrix(); //여기에 추가하십시오

			glBegin(GL_QUADS);

			glColor3f(0.35f, 0.35f, 0.35f);

			for (int i = -100; i < 100; i++) //장판
			{
				glVertex3f(-i * 5, -25, -i * 5);
				glVertex3f(-i * 5, -25, i * 5);
				glVertex3f(i * 5, -25, i * 5);
				glVertex3f(i * 5, -25, -i * 5);
			}
			glEnd();

			glPushMatrix();

				DrawPiramid();

			glPopMatrix();

			glPushMatrix();

				glTranslated(-175, 25, 150);
				glColor3f(0.54, 0.2, 0.8);
				glScaled(1, 2, 1);
				
				glutSolidCube(50);

			glPopMatrix();

			glPushMatrix(); 

				glTranslatef(-175, 125, 0);
				glColor3f(0.5, 0.7, 0.8);
				glScaled(1, 6, 1);
				
					glutSolidCube(50);

			glPopMatrix();

			glPushMatrix();

				glTranslated(-175, 100, -150);
				glColor3f(0.8, 0.7, 0.2);
				glScaled(1, 5, 1);
				
				glutSolidCube(50);

			glPopMatrix();

			glPushMatrix();

				door();

			glPopMatrix();

			glPushMatrix();
			
				glTranslated(175, 0, -150);

				glColor3f(0.5, 1.0, 0.5);

				glutSolidCube(50);

			glPopMatrix();

			glPushMatrix();

				glTranslated(hero.xTran, hero.yTran, hero.zTran);

				glColor3f(1, 0, 0);

				glutSolidSphere(20, 50, 50);

			glPopMatrix();



		glPopMatrix(); //여기에 추가하십시오

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

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //투영 변환 ( 원근 투영 ) 

	glTranslatef(0.0, 0.0, -700.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0번빛을 사용한다.

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

}
bool Left_button = false;
bool Right_button = false;
bool Up_button = false;
bool Down_button = false;

void SpecialKeyboardDown(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (!Left_button)
			Left_button = true;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (!Right_button)
			Right_button = true;
	}
	if (key == GLUT_KEY_UP)
	{
		if (!Up_button)
			Up_button = true;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (!Down_button)
			Down_button = true;
	}

	glutPostRedisplay();
}
void SpecialKeyboardUp(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (Left_button)
			Left_button = false;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (Right_button)
			Right_button = false;
	}
	if (key == GLUT_KEY_UP)
	{
		if (Up_button)
			Up_button = false;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (Down_button)
			Down_button = false;
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

	glutPostRedisplay();
}

bool Light = true;

void TimerFunction(int value)
{
	if (value == 1)
	{
		if (Light)
		{
			glDisable(GL_LIGHT0);
			Light = false;
		}
		else
		{
			glEnable(GL_LIGHT0);
			Light = true;
		}
		glutTimerFunc(500, TimerFunction, 1);
	}
	if (value == 2)
	{
		if (collision(hero, area[0]) || collision(hero, area[1]))
		{
			ambientLight[0] = 1.0;
			ambientLight[1] = 0.1;
			ambientLight[2] = 0.1;
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		}
		else
		{
			ambientLight[0] = 0.5;
			ambientLight[1] = 0.5;
			ambientLight[2] = 0.5;
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		}

		if (Left_button)
		{
			if (!Rightcollision(hero, tower[0]) && !Rightcollision(hero, tower[1]) && !Rightcollision(hero, tower[2]) && !Rightcollision(hero, tower[3]) && !Rightcollision(hero, tower[4]) && !Rightcollision(hero, tower[5]) && !Rightcollision(hero, tower[6]))
			{
				if (hero.xTran > -200)
					hero.xTran -= 4;
			}

		}

		if (Right_button)
		{
			if (!Leftcollision(hero, tower[0]) && !Leftcollision(hero, tower[1]) && !Leftcollision(hero, tower[2]) && !Leftcollision(hero, tower[3]) && !Leftcollision(hero, tower[4]) && !Leftcollision(hero, tower[5]) && !Leftcollision(hero, tower[6]))
			{
				if (hero.xTran < 200)
					hero.xTran += 4;
			}

		}

		if (Up_button)
		{
			if (!Downcollision(hero, tower[0]) && !Downcollision(hero, tower[1]) && !Downcollision(hero, tower[2]) && !Downcollision(hero, tower[3]) && !Downcollision(hero, tower[4]) && !Downcollision(hero, tower[5]) && !Downcollision(hero, tower[6]))
			{
				if (hero.zTran > -200)
					hero.zTran -= 4;
			}

		}

		if (Down_button)
		{
			if (!Upcollision(hero, tower[0]) && !Upcollision(hero, tower[1]) && !Upcollision(hero, tower[2]) && !Upcollision(hero, tower[3]) && !Upcollision(hero, tower[4]) && !Upcollision(hero, tower[5]) && !Upcollision(hero, tower[6]))
			{
				if (hero.zTran < 200)
					hero.zTran += 4;
			}
		}
		


		glutTimerFunc(10, TimerFunction, 2);
	}
	
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
}

bool collision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 10);
	float Top = (Circle.zTran - 10);
	float Right = (Circle.xTran + 10);
	float Bottom = (Circle.zTran + 10);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Leftcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran - 25);
	float Bottom2 = (Rect.zTran + 25);
	
	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Rightcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran + 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Upcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran - 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Downcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran + 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}