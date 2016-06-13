#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

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
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

GLfloat AmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat DiffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat SpecularLight[] = { 1.f, 1.f, 1.f, 1.0 };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


GLfloat lightPos[] = { 0.0, 200.0, 0.0, 1.0 };



char* string1 = { "(GL_ONE, GL_ZERO)" }; 
char* string2 = { "(GL_ZERO, GL_ONE)" };
char* string3 = { "(GL_ONE, GL_ONE)" };
char* string4 = { "(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)" };
char* string5 = { "(GL_SRC_ALPHA, GL_ONE)" };
char* string6 = { "(GL_ZERO, GL_SRC_COLOR)" };
char* string7 = { "(GL_ONE_MINUS_DST_COLOR, GL_ZERO)" };
char* string8 = { "(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR)" };
char* string9 = { "(GL_ONE, GL_ONE)" };

float alpha[9] = { 0, };
Object Screen = { 0, };
int check = 4;

Object box = { 0, };

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(400, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	//glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	glutMainLoop();
}



void DrawImage(int index)
{
	glColor4f(1, 0, 0, alpha[index]);
	glutSolidCube(50);

	glColor4f(0, 1, 0, alpha[index]);

	glTranslated(30, 0, -20);
	glRotated(270, 1, 0, 0);

	glutSolidCone(50, 50, 50, 50);

	glColor4f(0, 0, 1, alpha[index]);

	glTranslated(-20, 0, 0);
	glRotated(-270, 1, 0, 0);
	glutSolidCone(50, 20, 20, 20);
}

// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�


		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 100);

		glRotated(Screen.xRot, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);


		glPushMatrix(); // 1

			glBlendFunc(GL_ONE, GL_ZERO);
			glTranslated(-200, 200, 0);
			
			DrawImage(0);
			
			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-70, -100);
			for (int i = 0; i < strlen(string1); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
			
		glPopMatrix();

		glPushMatrix(); // 2

			glBlendFunc(GL_ZERO, GL_ONE);
			glTranslated(0, 200, 0);

			DrawImage(1);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-70, -100);
			for (int i = 0; i < strlen(string2); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string2[i]);

		glPopMatrix();


		glPushMatrix(); // 3

			glBlendFunc(GL_ONE, GL_ONE);
			glTranslated(200, 200, 0);

			DrawImage(2);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-70, -100);
			for (int i = 0; i < strlen(string3); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string3[i]);

		glPopMatrix();

		
		glPushMatrix(); // 4

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslated(-200, 0, 0);
			
			DrawImage(3);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-160, -80);
			for (int i = 0; i < strlen(string4); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string4[i]);

		glPopMatrix();

		glPushMatrix(); // 5

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glTranslated(0, 0, 0);

			DrawImage(4);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-120, -105);
			for (int i = 0; i < strlen(string5); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string5[i]);

		glPopMatrix();


		glPushMatrix(); // 6

			glBlendFunc(GL_ONE, GL_ONE);
			glTranslated(200, 0, 0);

			DrawImage(5);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-90, -100);
			for (int i = 0; i < strlen(string6); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string6[i]);

		glPopMatrix();

		glPushMatrix(); // 7

			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);			
			glTranslated(-200, -200, 0);

			DrawImage(6);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-160, -90);
			for (int i = 0; i < strlen(string7); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string7[i]);

		glPopMatrix();

		glPushMatrix(); // 8

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
			glTranslated(0, -200, 0);

			DrawImage(7);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-110, -130);
			for (int i = 0; i < strlen(string8); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string8[i]);

		glPopMatrix();


		glPushMatrix(); // 9

			glBlendFunc(GL_ONE, GL_ONE);
			glTranslated(200, -200, 0);

			DrawImage(8);

			glBlendFunc(GL_ONE, GL_ONE);
			glRasterPos2f(-70, -100);
			for (int i = 0; i < strlen(string9); i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string9[i]);

		glPopMatrix();

		glPushMatrix();

		glColor3f(1, 1, 1);
		glTranslated(0, -15, 0);

		glBegin(GL_LINE_STRIP);

			glVertex2f(box.xTran - 100, box.yTran + 100);
			glVertex2f(box.xTran - 100, box.yTran - 100);
			glVertex2f(box.xTran + 100, box.yTran - 100);
			glVertex2f(box.xTran + 100, box.yTran + 100);
			glVertex2f(box.xTran - 100, box.yTran + 100);

		glEnd();

		glPopMatrix();


			


	glPopMatrix();//ī�޶�

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	//glOrtho(0, 800, 600, 0, -1.0, 1.0);
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

	//glEnable(GL_LIGHTING);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	//glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);

	for (int i = 0; i < 9; i++)
	{
		alpha[i] = 0.5;

	}
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (box.xTran > -200)
		{
			box.xTran -= 200;
			check--;
		}

	}

	else if (key == GLUT_KEY_RIGHT)
	{
		if (box.xTran < 200)
		{
			box.xTran += 200;
			check++;
		}

	}

	else if (key == GLUT_KEY_UP)
	{
		if (box.yTran < 200)
		{
			box.yTran += 200;
			check -= 3;
		}

	}

	else if (key == GLUT_KEY_DOWN)
	{
		if (box.yTran > -200)
		{
			box.yTran -= 200;
			check += 3;
		}

	}
	printf("%d\n", check);

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

	else if (key == 'q')
	{
		if (alpha[check] > 0.1) 
			alpha[check] -= 0.1f;
	}
	else if (key == 'w')
	{
		if (alpha[check] < 1.0) 
			alpha[check] += 0.1f;
	}


	for (int i = 0; i < 3; i++)
	{
		printf("%f %f %f\n", alpha[i * 3], alpha[i * 3 + 1], alpha[i * 3 + 2]);
	}
		

	glutPostRedisplay();
}

void TimerFunction(int value)
{

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