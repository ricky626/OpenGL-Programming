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
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	glutMainLoop();
}

Object Screen = { 0, };
Object Earth = { 0, };

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �ֵ� ����


GLfloat lightPos[] = { -400.0f, 300.0f, 0.0f, 1.0f }; //������ ��ġ
GLfloat lightPos2[] = { 400.0f, 300.0f, 0.0f, 1.0f }; //������ ��ġ

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��ü�� ���� ��� �� ��
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�
	glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

	glRotated(Screen.xRot+30, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);
		
		glPushMatrix();


			glColor3ub(180, 180, 0);

			/*glTranslatef(0.0, 0.0, zTran);
			glRotatef(xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(zRot, 0.0f, 0.0f, 1.0f);*/

			glScalef(5.0, 2.0, 5.0);

			glBegin(GL_QUADS);
				glVertex3f(-100.0, -100.0, -100.0);
				glVertex3f(-100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, -100.0);
			glEnd();

		glPopMatrix();
			
		glPushMatrix();
		

		glTranslated(0, -97, 0);

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

		glPopMatrix();
		
		glPushMatrix();

			glColor3f(0, 0, 1);
		
			glRotatef(Earth.xRot, 1, 0, 0);
			glRotatef(Earth.yRot, 0, 1, 0);
			glRotatef(Earth.zRot, 0, 0, 1);

			glTranslatef(Earth.xTran + 400, Earth.yTran - 100, Earth.zTran);


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

		glPushMatrix();

			glColor3f(1, 0, 0);
			glTranslatef(lightPos[0], lightPos[1], lightPos[2]);

				glutSolidCube(5);

		glPopMatrix();

		glPushMatrix();

			glColor3f(0, 1, 0);
			glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);

				glutSolidCube(5);

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
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT1); // 1������ ����Ѵ�.


	//Ambient(��ü�� �����ϰ� ��Ÿ���»�), Diffuse(��ü�� �ֵ� ����), Specular(��ü�� ���� ��� �� ��), Emission(�߱���), Shiness(����������)
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);


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

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		Earth.yRot -= 2;

		glutTimerFunc(10, TimerFunction, 1);
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