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

void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void TimerFunction(int value);
bool collision(Object Rect, Object Circle);

Object Screen = { 0, };

Object Body = { 0, };
Object Hand = { 0, };
Object Finger = { 0, };
Object Circle = { 0, };

int count = 0;
bool check = false;
int BodymoveX = 2;

int changeColorR = 255, changeColorG = 0, changeColorB = 0;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)
	glutReshapeFunc(Reshape);

	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����

	
	glutMainLoop();
}



// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran+80);
		glRotatef(20, 1, 0, 0);
		
		glRotatef(Screen.xRot, 1, 0, 0);
		glRotatef(Screen.yRot, 0, 1, 0);
		glRotatef(Screen.zRot, 0, 0, 1);

		glPushMatrix();
			glColor3ub(180, 180, 0);

			//glTranslatef(0.0, 0.0, 200);

			//glRotatef(10, 1, 0, 0);
			glScalef(3.0, 2.0, 2.0);

			glBegin(GL_QUADS);
				glVertex3f(-100.0, -100.0, -100.0);
				glVertex3f(-100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, -100.0);
			glEnd();

		glPopMatrix();

		glPushMatrix();
			glColor3f(changeColorR, changeColorG, changeColorB);


			glTranslatef(Circle.xTran, Circle.yTran - 160, Circle.zTran);

			glRotatef(Circle.xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(Circle.yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(Circle.zRot, 0.0f, 0.0f, 1.0f);



			//glScalef(2.0, 2.0, 2.0);

			glutSolidSphere(40, 30, 30); //������ 20

		glPopMatrix();

		glPushMatrix(); //��ü

			glColor3ub(255, 0, 0);
			
			glTranslatef(Body.xTran, Body.yTran-150, Body.zTran);

			glRotatef(Body.xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(Body.yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(Body.zRot, 0.0f, 0.0f, 1.0f);

			//glScalef(2.0, 2.0, 2.0);
			glutSolidCube(100);

			glPushMatrix(); //����

				glColor3ub(0, 255, 0);

				glTranslatef(Hand.xTran, Hand.yTran + 60, Hand.zTran);

				glRotatef(Hand.xRot, 1.0f, 0.0f, 0.0f);
				glRotatef(Hand.yRot, 0.0f, 1.0f, 0.0f);
				glRotatef(Hand.zRot, 0.0f, 0.0f, 1.0f);

				glScalef(2.0, 2.0, 2.0);
				glScalef(1.5, 7.5, 1.5);

				glutSolidCube(10);

				glPushMatrix(); //�����

					glColor3ub(0, 0, 255);

					glRotatef(Finger.xRot, 1.0f, 0.0f, 0.0f);
					glRotatef(Finger.yRot, 0.0f, 1.0f, 0.0f);
					glRotatef(Finger.zRot, 0.0f, 0.0f, 1.0f);

					glTranslatef(Finger.xTran, Finger.yTran + 5, Finger.zTran);
					
					//glScalef(2.0, 2.0, 2.0);
					glScalef(0.4, 0.8, 0.4);

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

	glEnable(GL_DEPTH_TEST);
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

	else if (key == 'i') // �ʱ�ȭ
	{
		Body = { 0. };
		Hand = { 0. };
		Finger = { 0. };
	}

	else if (key == '1') //x�� ȸ�� --
	{
		Screen.xRot -= 2;
	}
	else if (key == '2') //x�� ȸ�� ++
	{
		Screen.xRot += 2;
	}
	else if (key == '3') //y�� ȸ�� --
	{
		Screen.yRot -= 2;
	}
	else if (key == '4') //y�� ȸ�� ++
	{
		Screen.yRot += 2;
	}
	else if (key == '5') //z�� ȸ�� --
	{
		Screen.zRot -= 2;
	}
	else if (key == '6') //z�� ȸ�� ++
	{
		Screen.zRot += 2;
	}

	else if (key == '9')
	{
		Screen.zTran -= 5;
	}
	else if (key == '0')
	{
		Screen.zTran += 5;
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (Circle.xTran > -300)
			Circle.xTran -= 5;

		if (check == 0)
			Circle.zRot += 5;
		else
			Circle.zRot -= 5;
	}

	else if (key == GLUT_KEY_RIGHT)
	{
		if (Circle.xTran < 300)
			Circle.xTran += 5;

		if (check == 1)
			Circle.zRot += 5;
		else
			Circle.zRot -= 5;
	}


	else if (key == GLUT_KEY_UP)
	{
		if (Circle.zTran > -200)
			Circle.zTran -= 5;
		
		//if (count == 175)
		//{
		//	count = 0;
		//	if (check == 0)
		//		check = 1;
		//	else if (check == 1)
		//		check = 0;
		//}
		//else
			count += 5;

		Circle.xRot -= 5;

	}

	else if (key == GLUT_KEY_DOWN)
	{
		if (Circle.zTran < 150)
			Circle.zTran += 5;

		//if (count == 175)
		//{
		//	count = 0;
		//	if (check == 0)
		//		check = 1;
		//	else if (check == 1)
		//		check = 0;
		//}
		//else
			count += 5;

		Circle.xRot += 5;

	}

	glutPostRedisplay();
}


void TimerFunction(int value)
{
	if (value == 1)
	{
		if (Body.xTran == -250 || Body.xTran == 250)
		{
			BodymoveX *= -1;
		}

		Body.xTran += BodymoveX;


		if (collision(Body, Circle))
		{
			changeColorR = 0;
			changeColorB = 255;
		}
		else
		{
			changeColorR = 255;
			changeColorB = 0;
		}

		glutTimerFunc(10, TimerFunction, 1);
	}
	glutPostRedisplay();
}

/*bool collision(Object Rect, Object Circle)
{
	float Left = (Rect.xTran - 50) * 2;
	float Top = (Rect.zTran - 50) * 2;
	float Right = (Rect.xTran + 50) * 2;
	float Bottom = (Rect.zTran + 50) * 2;

	float CirX = Circle.xTran * 2;
	float CirY = Circle.zTran * 2;

	float rr = 20 * 2;

	float m1 = sqrt(pow(Left - CirX, 2) + pow(Top - CirY, 2));

	float m2 = sqrt(pow(Left - CirX, 2) + pow(Bottom - CirY, 2));

	float m3 = sqrt(pow(Right - CirX, 2) + pow(Top - CirY, 2));
	float m4 = sqrt(pow(Right - CirX, 2) + pow(Bottom - CirY, 2));

	bool bw = (Left <= CirX - rr && Top <= CirY + rr && Right >= CirX + rr && Bottom >= CirY - rr);
	bool by = (Left <= CirX + rr && Top <= CirY - rr & Right >= CirX - rr && Bottom >= CirY + rr);

	bool cy = (m1 <= rr || m2 <= rr || m3 <= rr || m4 <= rr);

	return (bw || by || cy);
}*/

bool collision(Object Rect, Object Circle)
{
	float Left = (Rect.xTran - 50);
	float Top = (Rect.zTran - 50);
	float Right = (Rect.xTran + 50);
	float Bottom = (Rect.zTran + 50);

	float Left2 = (Circle.xTran - 40);
	float Top2 = (Circle.zTran - 40);
	float Right2 = (Circle.xTran + 40);
	float Bottom2 = (Circle.zTran + 40);


	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}