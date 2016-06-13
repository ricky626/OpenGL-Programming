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
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	glutMainLoop();
}

Object Screen = { 0, };
Object Earth = { 0, };

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0};

float moveY[30][30] = { 0, };

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos1[] = { -400.0f, 300.0f, -400.0f, 1.0f }; //���� ���
GLfloat lightPos2[] = { 400.0f, 300.0f, -400.0f, 1.0f }; //���� ���
GLfloat lightPos3[] = { -400.0f, 300.0f, 400.0f, 1.0f }; //���� �ϴ�
GLfloat lightPos4[] = { 400.0f, 300.0f, 400.0f, 1.0f }; //���� �ϴ�


GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

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
	glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-100.0f, -100.0f, 100.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(100.0f, -100.0f, 100.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(100.0f, -100.0f, 100.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(100.0f, -100.0f, -100.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(100.0f, -100.0f, -100.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-100.0f, -100.0f, -100.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-100.0f, -100.0f, -100.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-100.0f, -100.0f, 100.0f);

	glEnd();   // Done drawing the pyramid
}

// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

		glRotated(Screen.xRot + 30, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);


		DrawCoord();

		glPushMatrix();

			glColor3ub(180, 180, 0);

			glScalef(6.5, 2.0, 5.0);

			glBegin(GL_QUADS);
				glVertex3f(-100.0, -100.0, -100.0);
				glVertex3f(-100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, -100.0);
			glEnd();

		glPopMatrix();

		// �Ƕ�̵�
		glPushMatrix();

			glTranslated(-300, -97, 0);
			DrawPiramid();

		glPopMatrix();

		//�Ƕ�̵�2
		glPushMatrix();

			glTranslated(300, -97, 0);
			DrawPiramid();

		glPopMatrix();

		//���� + ��
		glPushMatrix();

			glColor3f(1, 0, 0);

			glTranslated(-300, 0, 0);

			glRotatef(Earth.xRot, 1, 0, 0);
			glRotatef(Earth.yRot, 0, 1, 0);
			glRotatef(Earth.zRot, 0, 0, 1);

			glTranslatef(Earth.xTran + 250, Earth.yTran - 100, Earth.zTran);


			glutSolidSphere(30, 20, 20);

			glPushMatrix();
				
			
				glColor3f(0, 1, 0);

				glRotatef(Earth.xRot, 1, 0, 0);
				glRotatef(Earth.yRot, 0, 1, 0);
				glRotatef(Earth.zRot, 0, 0, 1);

				glTranslatef(Earth.xTran + 50, Earth.yTran, Earth.zTran);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();

		glPopMatrix();

		// ���� + ��
		glPushMatrix(); 

			glColor3f(0, 0, 1);

			glTranslated(300, 0, 0);

			glRotatef(Earth.xRot, 1, 0, 0);
			glRotatef(Earth.yRot, 0, 1, 0);
			glRotatef(Earth.zRot, 0, 0, 1);

			glTranslatef(Earth.xTran + 250, Earth.yTran - 100, Earth.zTran);


			glutSolidSphere(30, 20, 20);

			glPushMatrix();

				glColor3f(0, 1, 0);

				glRotatef(Earth.xRot, 1, 0, 0);
				glRotatef(Earth.yRot, 0, 1, 0);
				glRotatef(Earth.zRot, 0, 0, 1);

				glTranslatef(Earth.xTran + 50, Earth.yTran, Earth.zTran);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();

		glPopMatrix();

		//���� ��� ����
		glPushMatrix();

			glColor3f(1, 0, 0);
			glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);

			glutSolidCube(5);

		glPopMatrix();

		//���� ��� ����
		glPushMatrix();

			glColor3f(0, 1, 0);
			glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);

			glutSolidCube(5);

		glPopMatrix();

		//���� �ϴ� ����
		glPushMatrix();

			glColor3f(1, 1, 0);
			glTranslatef(lightPos3[0], lightPos3[1], lightPos3[2]);

			glutSolidCube(5);

		glPopMatrix();

		//���� �ϴ� ����
		glPushMatrix();

			glColor3f(0, 0, 1);
			glTranslatef(lightPos4[0], lightPos4[1], lightPos4[2]);

			glutSolidCube(5);

		glPopMatrix();

		//��
		glPushMatrix();
			glColor3f(1, 1, 1);

			
			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					glLoadIdentity();

					glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

					glRotated(Screen.xRot + 30, 1, 0, 0);
					glRotated(Screen.yRot, 0, 1, 0);
					glRotated(Screen.zRot, 0, 0, 1);

					glTranslatef(Snow[i][j].xTran, Snow[i][j].yTran, Snow[i][j].zTran);


					glutSolidCube(5);
				}
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

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -1200.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);



	glEnable(GL_LIGHTING); // ���� ����Ѵ�.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT1); // 1������ ����Ѵ�.

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 2������ ����Ѵ�.

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT1); // 3������ ����Ѵ�.


	//Ambient(��ü�� �����ϰ� ��Ÿ���»�), Diffuse(��ü�� �ֵ� ����), Specular(��ü�� ���� ��� �� ��), Emission(�߱���), Shiness(����������)
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);


	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			Snow[i][j].xTran = rand() % 1000 - 500;
			Snow[i][j].yTran = rand() % 200 + 400;
			Snow[i][j].zTran = rand() % 800 - 400;

			moveY[i][j] = rand() % 5 + 1;
		}
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
	static bool Light1 = true;
	static bool Light2 = true;
	static bool Light3 = true;
	static bool Light4 = true;

	if (key == 'q' || key == 'Q')
	{
		if (Light1)
		{
			glEnable(GL_LIGHT0);
			Light1 = false;
		}

		else
		{
			glDisable(GL_LIGHT0);
			Light1 = true;
		}

	}

	else if (key == 'w' || key == 'W')
	{
		if (Light2)
		{
			glEnable(GL_LIGHT1);
			Light2 = false;
		}

		else
		{
			glDisable(GL_LIGHT1);
			Light2 = true;
		}

	}

	else if (key == 'e' || key == 'E')
	{
		if (Light3)
		{
			glEnable(GL_LIGHT2);
			Light3 = false;
		}
		else
		{
			glDisable (GL_LIGHT2);
			Light3 = true;
		}
	}

	else if (key == 'r' || key == 'R')
	{
		if (Light4)
		{
			glEnable(GL_LIGHT3);
			Light4 = false;
		}
		else
		{
			glDisable(GL_LIGHT3);
			Light4 = true;
		}
	}

	else if (key == 'a') //ambient
	{
		for (int i = 0; i < 3; i++)
		{
			if (ambientLight[i] > 0)
				ambientLight[i] -= 0.1;
		}
	}

	else if (key == 'A')
	{
		for (int i = 0; i < 3; i++)
		{
			if (ambientLight[i] < 1)
				ambientLight[i] += 0.1;
		}
	}

	else if (key == 'd') //diffuse
	{
		for (int i = 0; i < 3; i++)
		{
			if (diffuseLight[i] > 0)
				diffuseLight[i] -= 0.1;
		}
	}
	
	else if (key == 'D')
	{
		for (int i = 0; i < 3; i++)
		{
			if (diffuseLight[i] < 1)
				diffuseLight[i] += 0.1;
		}
	}

	else if (key == 's') //specular
	{
		for (int i = 0; i < 3; i++)
		{
			if (specularLight[i] > 0)
				specularLight[i] -= 0.1;
		}
	}

	else if (key == 'S')
	{
		for (int i = 0; i < 3; i++)
		{
			if (specularLight[i] < 1)
				specularLight[i] += 0.1;
		}
	}
	else if (key == '1') Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
	
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	static int check = 0;

	if (value == 1)
	{
		Earth.yRot -= 2;

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				if (Snow[i][j].yTran > -200)
					Snow[i][j].yTran -= moveY[i][j];
				else
				{
					Snow[i][j].xTran = rand() % 1000 - 500;
					Snow[i][j].yTran = rand() % 200 + 400;
					Snow[i][j].zTran = rand() % 800 - 400;
				}

			}
		}
		glutTimerFunc(10, TimerFunction, 1);
	}
	if (value == 2)
	{
		if (Screen.zTran < 180 && check == 0)
			Screen.zTran += 1;
		else if (Screen.zTran >= 180 && check == 0)
			check = 1;

		if (Screen.yRot < 1440 && check == 1)
			Screen.yRot++;
		else if (Screen.yRot >= 1440 && check == 1)
		{
			check = 2;
		}

		if (Screen.zTran > 0 && check == 2)
			Screen.zTran -= 1;
		else if (Screen.zTran == 0 && check == 2)
		{
			Screen.yRot = 0;
			check = 0;
		}			
		
		
		cout << Screen.zTran << endl;
		cout << Screen.yRot << endl;
		cout << check << endl;
		

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