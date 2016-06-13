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
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)

	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	glutMainLoop();
}

Object Screen = { 0, };
Object Earth = { 0, };

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0};

float moveY[30][30] = { 0, };

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos1[] = { -400.0f, 300.0f, -400.0f, 1.0f }; //좌측 상단
GLfloat lightPos2[] = { 400.0f, 300.0f, -400.0f, 1.0f }; //우측 상단
GLfloat lightPos3[] = { -400.0f, 300.0f, 400.0f, 1.0f }; //좌측 하단
GLfloat lightPos4[] = { 400.0f, 300.0f, 400.0f, 1.0f }; //우측 하단


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

// 윈도우 출력 함수
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라
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

		// 피라미드
		glPushMatrix();

			glTranslated(-300, -97, 0);
			DrawPiramid();

		glPopMatrix();

		//피라미드2
		glPushMatrix();

			glTranslated(300, -97, 0);
			DrawPiramid();

		glPopMatrix();

		//지구 + 원
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

		// 지구 + 원
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

		//좌측 상단 조명
		glPushMatrix();

			glColor3f(1, 0, 0);
			glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);

			glutSolidCube(5);

		glPopMatrix();

		//우측 상단 조명
		glPushMatrix();

			glColor3f(0, 1, 0);
			glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);

			glutSolidCube(5);

		glPopMatrix();

		//좌측 하단 조명
		glPushMatrix();

			glColor3f(1, 1, 0);
			glTranslatef(lightPos3[0], lightPos3[1], lightPos3[2]);

			glutSolidCube(5);

		glPopMatrix();

		//우측 하단 조명
		glPushMatrix();

			glColor3f(0, 0, 1);
			glTranslatef(lightPos4[0], lightPos4[1], lightPos4[2]);

			glutSolidCube(5);

		glPopMatrix();

		//눈
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

	glPopMatrix();//카메라

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정 // 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //투영 변환 ( 원근 투영 ) 

	glTranslatef(0.0, 0.0, -1200.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);



	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 0번빛을 사용한다.

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT1); // 1번빛을 사용한다.

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT0); // 2번빛을 사용한다.

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
	//glEnable(GL_LIGHT1); // 3번빛을 사용한다.


	//Ambient(물체가 은은하게 나타내는색), Diffuse(물체의 주된 색상), Specular(물체의 면이 띄게 될 색), Emission(발광색), Shiness(빛나는정도)
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