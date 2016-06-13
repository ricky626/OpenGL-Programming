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

void DrawScene();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

float xRot = 0, yRot = 0, zRot = 0;

//float xBody = 0, yBody = 0, zBody = 0;
//float xHands = 0, yHands = 0, zHands = 0;
//float xFinger = 0, yFinger = 0, zFinger = 0;

Object Body = { 0, };
Object Hand = { 0, };
Object Finger = { 0, };

float zTran = 0;
int BodymoveX = 2;
void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(50, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape);
	glutMainLoop();
}



// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

		glPushMatrix(); // ����
			glColor3ub(180, 180, 0);

			glTranslatef(0.0, 0.0, zTran);

			glRotatef(xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(zRot, 0.0f, 0.0f, 1.0f);

			glScalef(3.0, 2.0, 2.0);

			glBegin(GL_QUADS);
				glVertex3f(-100.0, -100.0, -100.0);
				glVertex3f(-100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, -100.0);
			glEnd();

		glPopMatrix();


		glPushMatrix(); //��ü

			glColor3ub(255, 0, 0);

			glTranslatef(Body.xTran, Body.yTran - 200, Body.zTran);

			glRotatef(Body.xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(Body.yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(Body.zRot, 0.0f, 0.0f, 1.0f);

			glScalef(3.0, 2.0, 2.0);
			glutSolidCube(50);

					glPushMatrix(); //����
					
						glColor3ub(0, 255, 0);

						glTranslatef(Hand.xTran, Hand.yTran + 60, Hand.zTran);

						glRotatef(Hand.xRot, 1.0f, 0.0f, 0.0f);
						glRotatef(Hand.yRot, 0.0f, 1.0f, 0.0f);
						glRotatef(Hand.zRot, 0.0f, 0.0f, 1.0f);

						glScalef(1.5, 7.5, 1.5);
					
						glutSolidCube(10);

							glPushMatrix(); //�����
								
								glColor3ub(0, 0, 255);

								glTranslatef(Finger.xTran, Finger.yTran + 10, Finger.zTran);

								glRotatef(Finger.xRot, 1.0f, 0.0f, 0.0f);
								glRotatef(Finger.yRot, 0.0f, 1.0f, 0.0f);
								glRotatef(Finger.zRot, 0.0f, 0.0f, 1.0f);

								glScalef(0.4, 1.0, 0.4);
								
								glutSolidCube(10);

							glPopMatrix();

					glPopMatrix();

		
		glPopMatrix();

	glPopMatrix();


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

	//glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q') // Body y�� ȸ�� --
	{
		Body.yRot -= 2;
	}
	else if (key == 'w') // Body y�� ȸ�� ++
	{
		Body.yRot += 2;
	}
	else if (key == 'a') // Hand x�� ȸ�� --
	{
		if (Hand.xRot > -28)
		{
			Hand.xRot -= 2;
			Hand.zTran -= 1.5;

			Finger.xRot -= 1.0;
		}

	}
	else if (key == 's') // Hand x�� ȸ�� ++
	{
		if (Hand.xRot < 28)
		{
			Hand.xRot += 2;
			Hand.zTran += 1.5; 

			Finger.xRot += 1.0;
		}
		
	}
	else if (key == 'd') // Hand y�� ȸ�� --
	{
		Hand.yRot -= 2;
	}
	else if (key == 'f') // Hand y�� ȸ�� ++
	{
		Hand.yRot += 2;
	}

	else if (key == 'z') // Finger y�� ȸ�� --
	{
		Finger.yRot -= 2;
	}
	else if (key == 'x') // Finger y�� ȸ�� ++
	{
		Finger.yRot += 2;
	}

	else if (key == 'c') // Finger x�� ȸ�� --
	{
		Finger.xRot -= 1;
		Finger.yTran -= 0.01;
	}
	else if (key == 'v') // Finger x�� ȸ�� ++
	{
		Finger.xRot += 1;
		Finger.yTran += 0.01;
	}

	else if (key == 'i')
	{
		Body = { 0. };
		Hand = { 0. };
		Finger = { 0. };
	}

	glutPostRedisplay();
}


void TimerFunction(int value)
{
	if (value == 1)
	{
		if (Body.xTran == -300 || Body.xTran == 300)
		{
			BodymoveX *= -1;
		}

		Body.xTran += BodymoveX;

		glutTimerFunc(50, TimerFunction, 1);
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}