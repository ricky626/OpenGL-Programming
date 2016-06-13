#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_CIRCLE 1000

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

bool keyDown = false;
float radius = 0.3f, fRocate = 0, fSpeed = 0, fScale = 0;

float fSin = 0 , fCos = 0;
int ap = 1;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(100, TimerFunction, 1);
	//glutSpecialFunc(SKeyboard);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape); glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	int a = 1;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-400, 0);
	glVertex2f(400, 0);
	glVertex2f(0, -300);
	glVertex2f(0, 300);
	glEnd();


	glPushMatrix();
	glTranslatef(0, 0, 0.0);
	glRotatef(0, 0, 0, 0.0);
	glScalef(1, 1, 0);
	if (keyDown)
	{
		glPushMatrix();
		//glScalef(1, 1, 1);
		glRotatef(fRocate, 0, 0, 1);
		
		//glTranslatef(fCos+0.3, fSin, 0.0);
		
		glColor3f(1, 0.0, 0);
		glRectf(-0.35 - fScale, -0.05 - fScale, -0.3 + 0.05 + fScale, 0.05 + fScale);
		glPopMatrix();
	}

	glBegin(GL_LINE_STRIP);

	for (float fAngle = 0.f; fAngle < 25.f; fAngle += 0.01f)
	{
		glColor3f(1, 1.0, 0);
		glVertex3f(cos(fAngle)*radius, (sin(fAngle) *radius), 0.f); //0.6pi ������
	}
	glEnd();

	glPopMatrix();


	//glFlush(); 
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, 800.0f, 600.0f, 0, -1.0, 1.0);
}


void Keyboard(unsigned char key, int x, int y)
{

	keyDown = true;
	
}

void TimerFunction(int value)
{
	printf("%f\n" , abs(sin(fSpeed)+cos(fSpeed)));
	fSin = sin(fSpeed)* radius;
	fCos = cos(fSpeed) * radius;
	fRocate += 3.6; //0.6PI = 360
	fSpeed += 0.05;
	if ((int)fRocate % 100 == 0)
		ap *= -1;
	fScale += 0.001 * ap;

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1); // 0.05��
}