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
void MenuFunc(int button);

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
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(20, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����

	int SubMenu1;
	int MainMenu;

	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("��������", SubMenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}
void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		glEnable(GL_DEPTH_TEST);
		break;
	case 2:
		glDisable(GL_DEPTH_TEST);
		break;
	}
}

Object Screen = {};
Object Dount[10] = {};
float moveY[10] = {};

int DountCount = 1;


// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glPushMatrix();//ī�޶�
		
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

			glPushMatrix();

				glColor3ub(180, 180, 0);

				glTranslatef(0.0, 0.0, 0);
				glRotatef(0, 1.0f, 0.0f, 0.0f);
				glRotatef(0, 0.0f, 1.0f, 0.0f);
				glRotatef(0, 0.0f, 0.0f, 1.0f);

				glScalef(3.0, 2.0, 2.0);

				glBegin(GL_QUADS);
					glVertex3f(-100.0, -100.0, -100.0);
					glVertex3f(-100.0, -100.0, 100.0);
					glVertex3f(100.0, -100.0, 100.0);
					glVertex3f(100.0, -100.0, -100.0);
				glEnd();

			glPopMatrix();

			glPushMatrix();

				glColor3ub(255, 0, 0);

				glTranslatef(0, 0, 0);
				glScalef(1.0, 40.0, 1.0);

				glutSolidCube(10);

			glPopMatrix();

			glPushMatrix();

				glColor3ub(0, 0, 255);
				
				for (int i = 0; i < DountCount; i++)
				{
					if (i == 2 || i == 5 || i == 8 || i == 11)
					{
						continue;
					}
						glLoadIdentity();
						glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);
						glRotated(Screen.xRot, 1, 0, 0);
						glRotated(Screen.yRot, 0, 1, 0);
						glRotated(Screen.zRot, 0, 0, 1);

						glRotatef(Dount[i].yRot, 0, 1, 0);

						glTranslatef(Dount[i].xTran + 25, Dount[i].yTran + 200, Dount[i].zTran);

						glRotatef(90, 1, 0, 0);

						glutWireTorus(20, 50, 20, 20);
					
				}

			glPopMatrix();
			
			glPushMatrix();

				glColor3ub(0, 255, 0);

				for (int i = 2; i < DountCount; i += 3)
				{
					glLoadIdentity();
					glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);
					glRotated(Screen.xRot, 1, 0, 0);
					glRotated(Screen.yRot, 0, 1, 0);
					glRotated(Screen.zRot, 0, 0, 1);

					glRotatef(Dount[i].yRot, 0, 1, 0);

					glTranslatef(Dount[i].xTran + 25, Dount[i].yTran + 200, Dount[i].zTran);

					glRotatef(90, 1, 0, 0);

					glScalef(3.0, 3.0, 1.0);

					glutSolidCube(40);
				}

			glPopMatrix();

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

	gluPerspective(60.0f, w / h, 1.0, 1000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 10; i++)
		moveY[i] = 2;
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

	glutPostRedisplay();

}

void TimerFunction(int value)
{
	for (int i = 0; i < DountCount; i++)
	{
		if (Dount[i].yTran < -375 + (i * 40) && moveY[i] != 0)
		{
			moveY[i] = 0;

			if (i < 9)
			{
				Dount[i].yRot = 0;
				Dount[i].xTran -= 25;
				DountCount++;
			}
			else if (i == 9)
			{
				DountCount = 1;
				for (int i = 0; i < 10; i++)
				{
					Dount[i] = { 0, 0, 0, 0, 0, 0 };
					moveY[i] = 2;
				}
				i = 0;
				Dount[i].yTran += 50;
			}
		}

		Dount[i].yTran -= moveY[i];
		Dount[i].yRot += moveY[i];
	}
	

	cout << DountCount << endl;
	glutTimerFunc(20, TimerFunction, 1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
}