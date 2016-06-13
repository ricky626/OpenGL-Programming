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

	float zMove;
	float State;
}Object;


GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.0f, 0.3f, 0.0f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 0.0f, 1.0f, 0.0f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //������ġ
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	glutMainLoop();
}

Object Screen = { 0, };
Object Car = { 0, };
Object Load[3] = { 0, };


float JTime = -1;
int Loadcount = 2;
int MoveState = 0;
bool LeftJump = false;
bool RightJump = false;

float Maxjump = 50;

// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();//ī�޶�
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 50);

		glRotated(Screen.xRot+10, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

		glPushMatrix();

			glColor3ub(180, 50, 0);

			glTranslatef(-125, 0, 0);

			glBegin(GL_QUADS);
			//glNormal3f(0, 1, 0);
				glVertex3f(-50.0, -100.0, -300.0);
				glVertex3f(-50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, -300.0);
			glEnd();

			glTranslatef(125, 0, 0);

			glBegin(GL_QUADS);
			//glNormal3f(0, 1, 0);
				glVertex3f(-50.0, -100.0, -300.0);
				glVertex3f(-50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, -300.0);
			glEnd();

			glTranslatef(125, 0, 0);

			glBegin(GL_QUADS);
			//glNormal3f(0, 1, 0);
				glVertex3f(-50.0, -100.0, -300.0);
				glVertex3f(-50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, 400.0);
				glVertex3f(50.0, -100.0, -300.0);
			glEnd();

		glPopMatrix();


		glPushMatrix();
			
			glColor3f(0, 0, 1);
			glTranslated(Car.xTran, Car.yTran-70, Car.zTran);
			
			glRotatef(Car.xRot, 1, 0, 0);
			glRotatef(Car.yRot + 270, 0, 1, 0);
			glRotatef(Car.zRot, 0, 0, 1);

			glPushMatrix();

				glColor3f(0, 0, 1);
				glScalef(2.5, 1, 1);
				glNormal3f(0, 1, 0);
					glutSolidCube(30);

			glPopMatrix();

			
			glPushMatrix();
			
				glColor3f(1, 1, 1);
				glNormal3f(0, 1, 0);
				glTranslated(30, -18, 0);
					glutSolidSphere(5, 20, 20);
				glTranslated(-60, 0, 0);
					glutSolidSphere(5, 20, 20);

			glPopMatrix();

		glPopMatrix();

		glPushMatrix();

		glColor3f(1, 1, 1);

		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);

		glutSolidCube(1);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

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

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	Car.zMove = 2;
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (LeftJump == false)
		{
			Loadcount--;
			LeftJump = true;

			ambientLight[1] = 1.0f;
			diffuseLight[1] = 1.0f;
			specularLight[1] = 0.3f;
		}
			
	}

	else if (key == GLUT_KEY_RIGHT)
	{
		if (RightJump == false)
		{
			Loadcount++;
			RightJump = true;
			ambientLight[1] = 1.0f;
			diffuseLight[1] = 1.0f;
			specularLight[1] = 0.3f;
		}
			
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
	if (value == 1)
	{
		lightPos[0] = Car.xTran;
		lightPos[1] = Car.yTran + 20;
		lightPos[2] = Car.zTran;

		if (Car.zTran < -225 || Car.zTran > 325)
			Car.zMove *= -1;

		Car.zTran += Car.zMove;

		if (RightJump == true || LeftJump == true)
		{
			if (Car.yTran < Maxjump && MoveState == 0)
			{
				Car.yTran++;

				if (RightJump)
				{
					Car.xTran += 2.5;
					Car.zRot -= 3.6;
				}
					
				else if (LeftJump)
				{
					Car.xTran -= 2.5;
					Car.zRot += 3.6;
				}
					
			}
			else
			{
				MoveState = 1;
				if (Loadcount >= 1 && Loadcount <= 3)
				{
					if (Car.yTran > 0)
					{
						Car.yTran--;
						if (RightJump)
							Car.zRot -= 3.6;
						else
							Car.zRot += 3.6;
					}
					else
					{
						LeftJump = false;
						RightJump = false;
						MoveState = 0;
						diffuseLight[1] = 0.3f;
						specularLight[1] = 1.0f;
						ambientLight[1] = 0.3f;
					}
				}
				else
				{
					Car.yTran -= 4;
				}
				
			}
		}
		//lightPos[0] = Car.xTran;
		//lightPos[1] = Car.yTran + 50;
		//lightPos[2] = Car.zTran;
	}

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
}