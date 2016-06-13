#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

void LoadTexture(const char* filename, int count);
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

GLuint textures[6];

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

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0 };

float moveY[30][30] = { 0, };

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos1[] = { -400.0f, 300.0f, -400.0f, 1.0f }; //���� ���
GLfloat lightPos2[] = { 400.0f, 300.0f, -400.0f, 1.0f }; //���� ���
GLfloat lightPos3[] = { -400.0f, 300.0f, 400.0f, 1.0f }; //���� �ϴ�
GLfloat lightPos4[] = { 400.0f, 300.0f, 400.0f, 1.0f }; //���� �ϴ�

GLfloat light1yRot = 0;
GLfloat light2yRot = 0;
GLfloat light3yRot = 0;
GLfloat light4yRot = 0;
bool Normal = false;

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

	//glColor3ub(255, 0, 0);

	// Front
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, 100.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glTexCoord2f(0, 0);
	glVertex3f(-100.0f, -100.0f, 100.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue

	glTexCoord2f(1, 0);
	glVertex3f(100.0f, -100.0f, 100.0f);


	// Right
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, 100.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glTexCoord2f(1, 0);
	glVertex3f(100.0f, -100.0f, 100.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glTexCoord2f(0, 0);
	glVertex3f(100.0f, -100.0f, -100.0f);

	// Back
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, 100.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glTexCoord2f(0, 1);
	glVertex3f(100.0f, -100.0f, -100.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glTexCoord2f(0, 0);
	glVertex3f(-100.0f, -100.0f, -100.0f);

	// Left
//	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glTexCoord2f(0.5, 1);
	glVertex3f(0.0f, 100.0f, 0.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glTexCoord2f(0, 1);
	glVertex3f(-100.0f, -100.0f, -100.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glTexCoord2f(0, 0);
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
		glPushMatrix(); //����
		glColor3f(1, 1, 1);
			glScalef(6.5, 2.0, 5.0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_QUADS);
	

			if (Normal)
				glNormal3f(0, 1, 0);
			else
				glNormal3f(0, 0, 0);

			
			glTexCoord2f(1, 1);
			glVertex3f(-100.0, -100.0, -100.0);
			glTexCoord2f(1, 0);
			glVertex3f(-100.0, -100.0, 100.0);
			glTexCoord2f(0, 0);
			glVertex3f(100.0, -100.0, 100.0);
			glTexCoord2f(0, 1);
			glVertex3f(100.0, -100.0, -100.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		// �Ƕ�̵�
		glPushMatrix();
			glTranslated(-300, -97, 0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			
			DrawPiramid();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//�Ƕ�̵�2
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
			glTranslated(300, -97, 0);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			DrawPiramid();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//���� + ��
		glPushMatrix();

			//glColor3f(1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
			glTranslated(-300, 0, 0);

			glRotatef(Earth.xRot, 1, 0, 0);
			glRotatef(Earth.yRot, 0, 1, 0);
			glRotatef(Earth.zRot, 0, 0, 1);

			glTranslatef(Earth.xTran + 250, Earth.yTran - 100, Earth.zTran);

			if (Normal)
				glNormal3f(0, 1, 0);
			else
				glNormal3f(0, 0, 0);

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glutSolidSphere(30, 20, 20);

			glPushMatrix();


				glColor3f(0, 1, 0);

				glRotatef(Earth.xRot, 1, 0, 0);
				glRotatef(Earth.yRot, 0, 1, 0);
				glRotatef(Earth.zRot, 0, 0, 1);

				glTranslatef(Earth.xTran + 50, Earth.yTran, Earth.zTran);

				if (Normal)
					glNormal3f(0, 1, 0);
				else
					glNormal3f(0, 0, 0);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		// ���� + ��
		glPushMatrix();

			//glColor3f(0, 0, 1);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glTranslated(300, 0, 0);

			glRotatef(Earth.xRot, 1, 0, 0);
			glRotatef(Earth.yRot, 0, 1, 0);
			glRotatef(Earth.zRot, 0, 0, 1);

			glTranslatef(Earth.xTran + 250, Earth.yTran - 100, Earth.zTran);

			if (Normal)
				glNormal3f(0, 1, 0);
			else
				glNormal3f(0, 0, 0);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glBindTexture(GL_TEXTURE_2D, textures[5]);
			glutSolidSphere(30, 20, 20);

			glPushMatrix();

				glColor3f(0, 1, 0);

				glRotatef(Earth.xRot, 1, 0, 0);
				glRotatef(Earth.yRot, 0, 1, 0);
				glRotatef(Earth.zRot, 0, 0, 1);

				glTranslatef(Earth.xTran + 50, Earth.yTran, Earth.zTran);

				if (Normal)
					glNormal3f(0, 1, 0);
				else
					glNormal3f(0, 0, 0);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//���� ��� ����
		glPushMatrix();

		glColor3f(1, 0, 0);

		glRotated(light1yRot, 0, 1, 0);

		glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

		glutSolidCube(5);

		glPopMatrix();

		//���� ��� ����
		glPushMatrix();

		glColor3f(0, 1, 0);


		glRotated(light2yRot, 0, 1, 0);

		glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

		glutSolidCube(5);

		glPopMatrix();

		//���� �ϴ� ����
		glPushMatrix();

		glColor3f(1, 1, 0);

		glRotated(light3yRot, 0, 1, 0);

		glTranslatef(lightPos3[0], lightPos3[1], lightPos3[2]);

		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);

		glutSolidCube(5);

		glPopMatrix();

		//���� �ϴ� ����
		glPushMatrix();

		glColor3f(0, 0, 1);

		glRotated(light4yRot, 0, 1, 0);

		glTranslatef(lightPos4[0], lightPos4[1], lightPos4[2]);

		glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);

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
	glEnable(GL_NORMALIZE);



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

	glGenTextures(6, textures); // n���� �̹��� �ؽ�ó ������ ����.

	LoadTexture("res/5.bmp", 0);
	LoadTexture("res/2.bmp", 1);
	LoadTexture("res/3.bmp", 2);
	LoadTexture("res/1.bmp", 3);
	LoadTexture("res/6.bmp", 4);
	LoadTexture("res/4.bmp", 5);


	
}

void LoadTexture(const char* filename, int count)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó ��� ����

	glBindTexture(GL_TEXTURE_2D, textures[count]); //�ؽ�ó�� ��ü�� �����Ѵ�.
	pBytes = LoadDIBitmap(filename, &info); //�̹��� �ε��� �Ѵ�.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //�ؽ�ó ���� ���Ǹ� �Ѵ�.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //�ؽ�ó �Ķ���� ����

	//	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó ��� ����
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
			glDisable(GL_LIGHT2);
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

	cout << Light1;
	cout << Light2;
	cout << Light3;
	cout << Light4 << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << ambientLight[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << diffuseLight[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << specularLight[i] << " ";
	}
	cout << endl;

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	static int check = 0;
	static float theta = 0;

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

		light1yRot += 1;
		light2yRot += 1;
		light3yRot += 1;
		light4yRot += 1;

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

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}