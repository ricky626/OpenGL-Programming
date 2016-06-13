#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_CIRCLE 1000

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

bool keyDown = false , bMouse = false;
float radius = 0.3f, fRocate = 0, fSpeed = 0, fScale = 0;
float fSin = 0, fCos = 0, fLadian = 0, fLadian2=0, fAngle2 = 0.f;
float fVectorX1, fVectorY1, fVectorX2[1000], fVectorY2[1000] , fsaveX = -0.8,fsaveY = 0;
float fRectX = 0, fRectY = 0 , mouseX,mouseY = 0;
int ap = 1;
int nMode = 0;
int count = 0 , clickcount = 0;

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
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape); glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	int a = 1;
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glLoadIdentity();

	//glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_LINES); //�߽ɼ�
	//glVertex2f(-400, 0);
	//glVertex2f(400, 0);
	//glVertex2f(0, -300);
	//glVertex2f(0, 300);
	//glEnd();


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
		glRectf(fRectX - 0.05, fRectY - 0.05, fRectX + 0.05, fRectY + 0.05);
		glPopMatrix();
	}

	
	glBegin(GL_LINE_STRIP);
	if (nMode == 1)
	{
		glColor3f(0, 0.0, 1);
		glVertex3f(fVectorX1, fVectorY1, 0.f);
		glVertex3f(fVectorX2[count], fVectorY2[count], 0.f);
	}
	if (nMode == 2) //���� �������� ������Ų�㿡 �׸���
	{
		for (float fAngle = 0; fAngle < 50.f; fAngle += 0.1)
		{
			fVectorX2[count] = sin((double)fAngle) + cos((double)fAngle);
			fVectorY2[count] = sin((double)fAngle) - cos((double)fAngle);
			glVertex3f(fVectorX2[count] * fLadian, fVectorY2[count] * fLadian, 0.f);
			fLadian += 0.001;
			count++;
		}
		count = 0;
		fLadian = 0;
	}
	if (nMode == 3) //�������
	{
		glColor3f(0, 0, 1);
		
		for (int i = 0; i < 5; i++)
		{
			ap *= -1;
			fsaveX += 0.2;
			fsaveY = 0.5;
			fVectorX2[i] = fsaveX;
			fVectorY2[i] = fsaveY*ap;
			glVertex3f(fVectorX2[i], fVectorY2[i], 0.f);
		}
		fsaveX = -0.8;
		fsaveY = 0;
		ap = 1;
	}
	if (nMode == 4)
	{
		glColor3f(0, 0, 1);
		for (int i = 0; i < clickcount; i++)
		{
			glVertex3f(fVectorX2[i], fVectorY2[i], 0.f);
		}
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
	glLoadIdentity();\

	glViewport(0, 0, w, h);
	glOrtho(0, 800.0f, 600.f, 0, -1.0, 1.0);

	for (int i = 0; i < 1000; i++)
	{
		fVectorX2[i] = 0;
		fVectorY2[i] = 0;
	}
}


void Keyboard(unsigned char key, int x, int y)
{

	keyDown = true;
	if (key == 'a'){
		nMode = 1;
		fRocate = 0;
		count = 0;
		fVectorX1 = -0.5;
		fVectorY1 = 0.0;
		fVectorX2[0] = 0.5;
		fVectorY2[0] = 0.0;
		fRectX = fVectorX1;
		fRectY = fVectorY1;
	}
	if (key == 's')
	{
		nMode = 2;
		fRocate = 0;
		fAngle2 = 0;
		fLadian2 = 0;
		fVectorX1 = 0.f;
		fVectorY1 = 0.f;
		fVectorX2[0] = 0.0;
		fVectorY2[0] = 0.0;
		fRectX = fVectorX1;
		fRectY = fVectorY1;
	}
	if (key == 'd')
	{
		nMode = 3;
		for (int i = 0; i < 5; i++)
		{
			fVectorX2[i] = -0.8;
			fVectorY2[i] = 0;
		}
		fRocate = 0;
		fRectX = -0.6;
		fRectY = -0.5;
		count = 0;
	}
	if (key == 'f')
	{
		nMode = 4;
		fRocate = 0;
		fRectX = 0;
		fRectY = 0;
		count = 0;
		for (int i = 0; i < 5; i++)
		{
			fVectorX2[i] = 0;
			fVectorY2[i] = 0;
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseX = x;
		mouseY = y;
		fVectorX2[clickcount] = (mouseX / (800.f) - 0.5) * 2;
		fVectorY2[clickcount] = - (mouseY / (600.f) - 0.5) * 2;
		if (clickcount == 0)
		{
			fRectX = fVectorX2[clickcount];
			fRectY = fVectorY2[clickcount];
		}
		if (clickcount < 5)
			clickcount++;
		else{
			clickcount = 0;
			count = 0;
			for (int i = 0; i < 5; i++)
			{
				fVectorX2[i] = 0;
				fVectorY2[i] = 0;
			}
			bMouse = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		bMouse = true;
	}

}

void TimerFunction(int value)
{
	printf("%f\n", abs(sin(fSpeed) + cos(fSpeed)));
	fSin = sin(fSpeed)* radius;
	fCos = cos(fSpeed) * radius;

	if (nMode == 1)
	if (fVectorX2[count] != fRectX || fVectorY2[count] != fRectY)
	{
		fRectX += (float)(fVectorX2[count] - fRectX) / 20.f;
		fRectY += (float)(fVectorY2[count] - fRectY) / 20.f;
	}
	if (nMode == 2)
	{
		if (fAngle2 <= 70.5f)
		{
			fRocate += 4;
			fAngle2 += 0.1;
			fLadian2 += 0.001;
		}
		fRectX = fLadian2;
	}
	if (nMode == 3)
	{
		if (fVectorX2[count + 1] != fRectX || fVectorY2[count + 1] != fRectY)
		{
			fRectX += (float)(fVectorX2[count + 1] - fRectX) / 20.f;
			fRectY += (float)(fVectorY2[count + 1] - fRectY) / 20.f;
		}
		if (fVectorX2[count + 1] - 0.005 <= fRectX)
		{
			if (count < 3)
				count++;
		}
	}
	if (nMode == 4 && bMouse)
	{
		if (fVectorX2[count + 1] != fRectX || fVectorY2[count + 1] != fRectY)
		{
			fRectX += (float)(fVectorX2[count + 1] - fRectX) / 20.f;
			fRectY += (float)(fVectorY2[count + 1] - fRectY) / 20.f;
		}
		if (fVectorX2[count + 1] >= fRectX - 0.01 &&
			(fVectorX2[count + 1] <= fRectX + 0.01) &&
			(fVectorY2[count + 1] >= fRectY - 0.01) &&
			(fVectorY2[count + 1] <= fRectY + 0.01))
		{
			if (count < 3)
				count++;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1); // 0.05��
}