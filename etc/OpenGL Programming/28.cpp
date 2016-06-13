#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


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

Object pp[7] = { 0, };

GLfloat ambientLight[] = { 0.01f, 0.01f, 0.01f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos[] = { 0.0f, 500.0f, 0.0f, 1.0f }; //������ġ

GLfloat spotStart[4] = { 0, };

GLfloat spotEnd[3] = { 0, -1, 0};

GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

bool part = false;
DWORD Timer = 0;

bool Left_button = false;
bool Right_button = false;
bool Up_button = false;
bool Down_button = false;


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

	hero.xTran = 0;
	hero.yTran = -5;
	hero.zTran = 100;

	spotStart[0] = hero.xTran;
	spotStart[1] = hero.yTran + 100;
	spotStart[2] = hero.zTran;
	spotStart[3] = 1;

}

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	init();
	glutTimerFunc(500, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);

	glutTimerFunc(30, TimerFunction, 3);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);

	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


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


	glPushMatrix();//ī�޶�
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot + 30, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

		glPushMatrix(); //���⿡ �߰��Ͻʽÿ�

			glBegin(GL_QUADS);

			glColor3f(0.35f, 0.35f, 0.35f);

			for (int i = -5; i < 5; i++) //����
			{
				for (int j = -5; j < 5; j++)
				{
					glVertex3f(i * 50,     -25, j * 50);
					glVertex3f(i * 50,     -25, j * 50 + 50);
					glVertex3f(i * 50 + 50, -25, j * 50 + 50);
					glVertex3f(i * 50 + 50, -25, j * 50);
				}
			
			}
			glEnd();

		glPopMatrix();

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

				if (!part)
				{
					glTranslated(hero.xTran, hero.yTran, hero.zTran);

					glColor3f(1, 0, 0);

					glutSolidSphere(20, 50, 50);
				}

				else if (part)
				{
					glTranslated(hero.xTran, hero.yTran, hero.zTran);

						glPushMatrix();
						glColor3f(1, 0, 0);
							glTranslated(3 * cos(0) + pp[0].xTran, 0, 3 * sin(0) + pp[0].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();


						glPushMatrix();
						glColor3f(1, 1, 0);
							glTranslated(3 * cos(1) + pp[1].xTran, 0, 3 * sin(1) + pp[1].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();


						glPushMatrix();
						glColor3f(1, 0, 1);
							glTranslated(3 * cos(2) + pp[2].xTran, 0, 3 * sin(2) + pp[2].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();

						glPushMatrix();
						glColor3f(0, 1, 1);
							glTranslated(3 * cos(3) + pp[3].xTran, 0, 3 * sin(3) + pp[3].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();

						glPushMatrix();
						glColor3f(1, 1, 1);
							glTranslated(3 * cos(4) + pp[4].xTran, 0, 3 * sin(4) + pp[4].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();

						glPushMatrix();
						glColor3f(0, 1, 0);
							glTranslated(3 * cos(5) + pp[5].xTran, 0, 3 * sin(5) + pp[5].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();

						glPushMatrix();
						glColor3f(0, 0, 1);
							glTranslated(3 * cos(6) + pp[6].xTran, 0, 3 * sin(6) + pp[6].zTran);
							glutSolidSphere(3, 20, 20);
						glPopMatrix();
				}
				

			glPopMatrix();

			glPushMatrix();

			
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
			glLightfv(GL_LIGHT1, GL_POSITION, spotStart);   // ���� ����

			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotEnd);   // ���� ����


			glTranslated(spotStart[0], spotStart[1], spotStart[2]);
				glutSolidCube(3);
				

			glPopMatrix();



	glPopMatrix(); //���⿡ �߰��Ͻʽÿ�

	glPopMatrix();//ī�޶�

	glutSwapBuffers();
}



void Reshape(int w, int h)
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳�� // �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING); // ���� ����Ѵ�.

	/*glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);*/
	//glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 80.0f);                 // ���� ����

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
	glLightfv(GL_LIGHT1, GL_POSITION, spotStart);   // ���� ����
	
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotEnd);   // ���� ����

	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

}

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
	static bool spotLight = true;

	if (key == '1')	Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;

	else if (key == 'e' || key == 'E')
	{
		if (spotLight)
		{
			glDisable(GL_LIGHT1);
			spotLight = false;
		}
		else if (!spotLight)
		{
			glEnable(GL_LIGHT1);
			spotLight = true;
		}
	}
	else if (key == 'r' || key == 'R')
	{
		if (!part)
		{
			part = true;
			Timer = GetTickCount();
		}
			
	}

	glutPostRedisplay();
}

bool Light = true;

void TimerFunction(int value)
{
	if (value == 1)
	{
		if (Light)
		{
		//	glDisable(GL_LIGHT0);
			Light = false;
		}
		else
		{
			//	glEnable(GL_LIGHT0);	
			Light = true;
		}
		//glutTimerFunc(500, TimerFunction, 1);
	}
	if (value == 2)
	{
		
		//if (collision(hero, area[0]) || collision(hero, area[1]))
		//{
		//	ambientLight[0] = 1.0;
		//	ambientLight[1] = 0.1;
		//	ambientLight[2] = 0.1;
		//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		//}
		//else
		//{
		//	ambientLight[0] = 0.5;
		//	ambientLight[1] = 0.5;
		//	ambientLight[2] = 0.5;
		//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		//}
		if (Left_button)
		{
			if (!Rightcollision(hero, tower[0]) && !Rightcollision(hero, tower[1]) && !Rightcollision(hero, tower[2]) && !Rightcollision(hero, tower[3]) && !Rightcollision(hero, tower[4]) && !Rightcollision(hero, tower[5]) && !Rightcollision(hero, tower[6]))
			{
				if (hero.xTran > -200)
				{
					hero.xTran -= 4;
					spotStart[0] -= 4;
				}
					
			}

		}

		if (Right_button)
		{
			if (!Leftcollision(hero, tower[0]) && !Leftcollision(hero, tower[1]) && !Leftcollision(hero, tower[2]) && !Leftcollision(hero, tower[3]) && !Leftcollision(hero, tower[4]) && !Leftcollision(hero, tower[5]) && !Leftcollision(hero, tower[6]))
			{
				if (hero.xTran < 200)
				{
					hero.xTran += 4;
					spotStart[0] += 4;
				}
					
			}

		}

		if (Up_button)
		{
			if (!Downcollision(hero, tower[0]) && !Downcollision(hero, tower[1]) && !Downcollision(hero, tower[2]) && !Downcollision(hero, tower[3]) && !Downcollision(hero, tower[4]) && !Downcollision(hero, tower[5]) && !Downcollision(hero, tower[6]))
			{
				if (hero.zTran > -200)
				{
					hero.zTran -= 4;
					spotStart[2] -= 4;
				}
					
			}

		}

		if (Down_button)
		{
			if (!Upcollision(hero, tower[0]) && !Upcollision(hero, tower[1]) && !Upcollision(hero, tower[2]) && !Upcollision(hero, tower[3]) && !Upcollision(hero, tower[4]) && !Upcollision(hero, tower[5]) && !Upcollision(hero, tower[6]))
			{
				if (hero.zTran < 200)
				{
					hero.zTran += 4;
					spotStart[2] += 4;
				}
					
			}
		}

		glutTimerFunc(10, TimerFunction, 2);
	}

	if (value == 3)
	{
		if (GetTickCount() - Timer > 250)
		{
			part = false;
			Timer = 0;
			for (int i = 0; i < 7; i++)
			{
				pp[i].xTran = 0;
				pp[i].zTran = 0;
			}
				
		}

		if (part)
		{
			pp[0].xTran += 4;
			pp[1].xTran += 4;
			pp[1].zTran += 4;
			pp[2].zTran += 4;
			pp[3].xTran -= 4;
			pp[3].zTran += 4;
			pp[4].xTran -= 4;
			pp[5].xTran -= 4;
			pp[5].zTran -= 4;
			pp[6].xTran += 4;
			pp[6].zTran -= 4;

		}

		glutTimerFunc(5, TimerFunction, 3);
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