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

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos1[] = { 200.0f, 300.0f, 0.0f, 1.0f }; //���� ���
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
Object Cube = { 0, };
Object Sphere = { 0, };
Object Torus = { 0, };

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

// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�
	glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

	glRotated(Screen.xRot, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);

	DrawCoord();

		glPushMatrix();
			
				glLineWidth(2);
				glColor3f(1, 1, 1);

			glTranslatef(-200, 0, 0);

			glBegin(GL_LINES);

				glVertex3f(0, -100, 0);
				glVertex3f(0, 100, 0);

			glEnd();

			glRotatef(Cube.yRot, 0, 1, 0);

			glTranslatef(Cube.xTran + 50, 0, 0);
			
				glColor3f(1, 0, 0);

				glutSolidCube(50);

		glPopMatrix();

		glPushMatrix();

			glTranslatef(200, 100, -200);

			glRotated(Sphere.yRot, 0, 1, 0);

			glColor3f(0, 1, 0);

			glutWireSphere(50, 20, 20);

		glPopMatrix();

		glPushMatrix();

		glRotatef(30, 0, 0, 1);
			glTranslatef(200, 0, 200);

			
			glColor3f(1, 1, 1);

			glBegin(GL_LINES);

				glVertex3f(0, 0, -100);
				glVertex3f(0, 0, 100);

			glEnd();


		
			glRotatef(Torus.zRot, 0, 0, 1);

			glTranslatef(Torus.xTran + 50, Torus.yTran, Torus.zTran);


			glColor3f(1, 1, 0);

			glutWireSphere(20, 20, 20);
			
			glRotatef(90, 0, 1, 0);

			glColor3f(0, 0, 1);

			glutSolidTorus(10, 50, 10, 10);
			
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

	gluPerspective(60.0f, w / h, 1.0, 2000); //���� ��ȯ ( ���� ���� ) 

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
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

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

	if (key == '1')	Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;


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
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		Cube.yRot += 1;
		Sphere.yRot += 1;
		Torus.zRot += 1;
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