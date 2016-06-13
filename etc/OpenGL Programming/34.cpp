#pragma warning(disable:4996)
#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


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
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

void Building(int i);

bool collision(Object Circle, Object Rect);
bool Leftcollision(Object Circle, Object Rect);
bool Rightcollision(Object Circle, Object Rect);
bool Upcollision(Object Circle, Object Rect);
bool Downcollision(Object Circle, Object Rect);
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLubyte *pBytes;   // 데이터를 가리킬 포인터
BITMAPINFO *info;   // 비트맵 헤더 저장할 변수

GLuint itextures[6];

Object tower[7] = { 0, };

Object hero = { 0, };

Object area[2] = { 0, };

Object Screen = { 0, };

Object pp[7] = { 0, };

GLfloat ambientLight[] = { 0.0f, 0.0f, 0.f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat ambientLight2[] = { 0.0f, 0.0f, 0.f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos0[] = { 400.0f, 500.0f, 0.0f, 1.0f }; //조명위치
GLfloat lightPos1[] = { -400.0f, 500.0f, 0.f, 1.0f }; //조명위치

GLfloat spotStart[4] = { 0, };

GLfloat spotEnd[3] = { 0, -1, 0 };

GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

bool part = false;
DWORD Timer = 0;

bool Left_button = false;
bool Right_button = false;
bool Up_button = false;
bool Down_button = false;
bool Check = false;
bool Check2 = false;
float f_turn = 1.f;
float fSize = 100.f;
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}


void init()
{
	tower[0] = { -125, 25, 150 };
	tower[1] = { -175, 125, 0 };
	tower[2] = { -175, 100, -150 };

	tower[3] = { 0, 0, 0 };
	tower[4] = { 175, 50, 150 };
	tower[5] = { 175, 50, 0 };

	tower[6] = { 130, 50, -150 };

	area[0] = { 175, 50, 50 };
	area[1] = { 175, 50, 100 };

	hero.xTran = 0;
	hero.yTran = -5;
	hero.zTran = 100;
	glFrontFace(GL_CCW);
}

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)

	init();
	glutTimerFunc(500, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);

	glutTimerFunc(30, TimerFunction, 3);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);

	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	glutMainLoop();
}


void DrawPiramid()
{
	glBegin(GL_TRIANGLES);

	// Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-25.0f, -50.0f, 25.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(25.0f, -50.0f, 25.0f);
	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(25.0f, -50.0f, 25.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(25.0f, -50.0f, -25.0f);
	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(25.0f, -50.0f, -25.0f);
	glColor3f(0.0f, 1.0f, 1.0f);     // Blue
	glVertex3f(-25.0f, -50.0f, -25.0f);
	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);       // Blue
	glVertex3f(-25.0f, -50.0f, -25.0f);
	glColor3f(1.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-25.0f, -50.0f, 25.0f);




	glEnd();   // Done drawing the pyramid
}

void door()
{
	glPushMatrix();

	glTranslated(175, 50, 150);

	glColor3ub(255, 0, 255);
	glScaled(1, 3, 1);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(175, 50, 0);

	glColor3ub(255, 0, 255);
	glScaled(1, 3, 1);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(175, 100, 75);

	glScaled(1, 1, 2);
	glColor3ub(255, 0, 255);
	glutSolidCube(50);

	glPopMatrix();
}


void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라
	glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

	glRotated(Screen.xRot + 30, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);

	// 앞면
	glBindTexture(GL_TEXTURE_2D, itextures[3]);
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);

	glTexCoord2f(0, 0);
	glVertex3f(-200.f, -25.f, 200.f);
	glTexCoord2f(0, 1);
	glVertex3f(-200.f, 275.f, 200.f);
	glTexCoord2f(1, 1);
	glVertex3f(200.f, 275.f, 200.f);
	glTexCoord2f(1, 0);
	glVertex3f(200.f, -25.f, 200.f);

	glEnd();

	// 오른쪽 
	glBindTexture(GL_TEXTURE_2D, itextures[3]);
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);

	glTexCoord2f(0, 0);
	glVertex3f(200.f, -25.f, 200.f);
	glTexCoord2f(0, 1);
	glVertex3f(200.f, 275.f, 200.f);
	glTexCoord2f(1, 1);
	glVertex3f(200.f, 275.f, -200.f);
	glTexCoord2f(1, 0);
	glVertex3f(200.f, -25.f, -200.f);

	glEnd();

	// 뒷면
	glBindTexture(GL_TEXTURE_2D, itextures[3]);

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);

	glTexCoord2f(0, 0);
	glVertex3f(200.f, -25.f, -200.f);
	glTexCoord2f(0, 1);
	glVertex3f(200.f, 275.f, -200.f);
	glTexCoord2f(1, 1);
	glVertex3f(-200.f, 275.f, -200.f);
	glTexCoord2f(1, 0);
	glVertex3f(-200.f, -25.f, -200.f);
	glEnd();

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, itextures[3]);

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glTexCoord2f(0, 0);
	glVertex3f(-200.f, -25.f, -200.f);
	glTexCoord2f(0, 1);
	glVertex3f(-200.f, 275.f, -200.f);
	glTexCoord2f(1, 1);
	glVertex3f(-200.f, 275.f, 200.f);
	glTexCoord2f(1, 0);
	glVertex3f(-200.f, -25.f, 200.f);
	glEnd();






	// 바닥
	glPushMatrix();
	glScalef(2.f, 1.f, 2.f);
	glTranslatef(0.f, 75.f, 0.f);
	glBindTexture(GL_TEXTURE_2D, itextures[0]);
	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);

	glTexCoord2f(0, 0);
	glVertex3f(-100.0, -100.0, -100.0);
	glTexCoord2f(0, 1);
	glVertex3f(-100.0, -100.0, 100.0);
	glTexCoord2f(1, 1);
	glVertex3f(100.0, -100.0, 100.0);
	glTexCoord2f(1, 0);
	glVertex3f(100.0, -100.0, -100.0);

	glEnd();
	glPopMatrix();

	// 가운데 피라미드
	glPushMatrix();
	glTranslatef(0.f, 25.f, 0.f);
	DrawPiramid();
	glPopMatrix();


	// 건물1
	glPushMatrix();
	glTranslatef(-200.f, -25.f, 50.f);
	glScalef(1.2f, 1.f, 1.2f);
	glColor3ub(255, 255, 255);
	Building(1);
	glPopMatrix();
	//

	glPushMatrix();

	glTranslatef(-175, 100, 0);
	glColor3ub(30, 144, 255);
	glScaled(1, 5, 1);

	glutSolidCube(50);

	glPopMatrix();


	glPushMatrix();

	glTranslated(-175, 50, -150);
	glColor3ub(00, 255, 255);
	glScaled(1, 3, 1);

	glutSolidCube(50);

	glPopMatrix();


	// 건물2
	glPushMatrix();
	glTranslatef(100.f, -25.f, -150.f);
	glScalef(1.f, 2.f, 1.f);
	glColor3ub(255, 255, 255);
	Building(2);
	glPopMatrix();
	//

	glPushMatrix();


	glTranslated(hero.xTran, hero.yTran, hero.zTran);

	glColor3f(1, 0, 0);

	glutSolidSphere(20, 40, 40);


	glPopMatrix();


	glPopMatrix(); //여기에 추가하십시오

	glPopMatrix();//카메라

	glutSwapBuffers();
}



void Reshape(int w, int h)
{
	glGenTextures(4, itextures);
	//
	glBindTexture(GL_TEXTURE_2D, itextures[0]);
	pBytes = LoadDIBitmap("res/floor.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1280, 960, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	glBindTexture(GL_TEXTURE_2D, itextures[1]);
	pBytes = LoadDIBitmap("res/wood.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 516, 516, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	glBindTexture(GL_TEXTURE_2D, itextures[2]);
	pBytes = LoadDIBitmap("res/triangles.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 225, 225, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	glBindTexture(GL_TEXTURE_2D, itextures[3]);
	pBytes = LoadDIBitmap("res/wall.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 3000, 2000, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정 // 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //투영 변환 ( 원근 투영 ) 

	glTranslatef(0.0, -125.0, -600.0);
	glRotatef(-15.f, 1.f, 0.f, 0.f);
	//관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0번빛을 사용한다.

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT1); // 1번빛을 사용한다.

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	glEnable(GL_LIGHTING); // 빛을 사용한다.
}

void SpecialKeyboardDown(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (!Left_button)
			Left_button = true;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (!Right_button)
			Right_button = true;
	}
	if (key == GLUT_KEY_UP)
	{
		if (!Up_button)
			Up_button = true;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (!Down_button)
			Down_button = true;
	}

	glutPostRedisplay();
}
void SpecialKeyboardUp(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (Left_button)
			Left_button = false;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		if (Right_button)
			Right_button = false;
	}
	if (key == GLUT_KEY_UP)
	{
		if (Up_button)
			Up_button = false;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (Down_button)
			Down_button = false;
	}

	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')   Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zTran -= 5;
	else if (key == '6') Screen.zTran += 5;

	glutPostRedisplay();
}

bool Light = true;

void TimerFunction(int value)
{
	if (value == 1)
	{

		if (Left_button)
		{
			if (!Rightcollision(hero, tower[0]) && !Rightcollision(hero, tower[1]) && !Rightcollision(hero, tower[2]) && !Rightcollision(hero, tower[3]) && !Rightcollision(hero, tower[4]) && !Rightcollision(hero, tower[5]) && !Rightcollision(hero, tower[6]))
			{
				if (hero.xTran > -200)
				{
					hero.xTran -= 5;
				}

			}

		}

		if (Right_button)
		{
			if (!Leftcollision(hero, tower[0]) && !Leftcollision(hero, tower[1]) && !Leftcollision(hero, tower[2]) && !Leftcollision(hero, tower[3]) && !Leftcollision(hero, tower[4]) && !Leftcollision(hero, tower[5]) && !Leftcollision(hero, tower[6]))
			{
				if (hero.xTran < 200)
				{
					hero.xTran += 5;
				}

			}

		}

		if (Up_button)
		{
			if (!Downcollision(hero, tower[0]) && !Downcollision(hero, tower[1]) && !Downcollision(hero, tower[2]) && !Downcollision(hero, tower[3]) && !Downcollision(hero, tower[5]) && !Downcollision(hero, tower[5]) && !Downcollision(hero, tower[6]))
			{
				if (hero.zTran > -200)
				{
					hero.zTran -= 5;
				}

			}

		}

		if (Down_button)
		{
			if (!Upcollision(hero, tower[0]) && !Upcollision(hero, tower[1]) && !Upcollision(hero, tower[2]) && !Upcollision(hero, tower[3]) && !Upcollision(hero, tower[5]) && !Upcollision(hero, tower[5]) && !Upcollision(hero, tower[6]))
			{
				if (hero.zTran < 200)
				{
					hero.zTran += 5;
				}

			}
		}

		glutTimerFunc(30, TimerFunction, 1);
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

	glutPostRedisplay();
}

bool collision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 10);
	float Top = (Circle.zTran - 10);
	float Right = (Circle.xTran + 10);
	float Bottom = (Circle.zTran + 10);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Leftcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran - 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Rightcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran + 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Upcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran - 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran - 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

bool Downcollision(Object Circle, Object Rect)
{
	float Left = (Circle.xTran - 18);
	float Top = (Circle.zTran - 18);
	float Right = (Circle.xTran + 18);
	float Bottom = (Circle.zTran + 18);

	float Left2 = (Rect.xTran - 25);
	float Top2 = (Rect.zTran + 25);
	float Right2 = (Rect.xTran + 25);
	float Bottom2 = (Rect.zTran + 25);

	if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2)
		return true;
	else
		return false;
}

void Building(int i)
{
	glPushMatrix();

	// 앞면
	glBindTexture(GL_TEXTURE_2D, itextures[i]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(fSize, 0.f, fSize);
	glTexCoord2f(1, 1);
	glVertex3f(fSize, fSize, fSize);
	glTexCoord2f(0, 1);
	glVertex3f(0.0, fSize, fSize);

	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.f, fSize);
	glEnd();

	// 오른쪽 
	glBindTexture(GL_TEXTURE_2D, itextures[i]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(fSize, 0.f, 0.f);
	glTexCoord2f(1, 1);
	glVertex3f(fSize, fSize, 0.f);
	glTexCoord2f(0, 1);
	glVertex3f(fSize, fSize, fSize);

	glTexCoord2f(0, 0);
	glVertex3f(fSize, 0.f, fSize);
	glEnd();

	// 뒷면
	glBindTexture(GL_TEXTURE_2D, itextures[i]);

	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.f, 0.f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, fSize, 0.f);
	glTexCoord2f(0, 1);
	glVertex3f(fSize, fSize, 0.f);
	glTexCoord2f(0, 0);
	glVertex3f(fSize, 0.f, 0.f);
	glEnd();

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, itextures[i]);

	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.f, fSize);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, fSize, fSize);
	glTexCoord2f(0, 1);
	glVertex3f(0.0, fSize, 0.f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.f, 0.f);
	glEnd();

	// 밑면
	glBindTexture(GL_TEXTURE_2D, itextures[i]);

	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(fSize, 0.f, fSize);
	glTexCoord2f(1, 1);
	glVertex3f(fSize, 0.f, 0.f);
	glTexCoord2f(0, 1);
	glVertex3f(0.f, 0.f, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.f, fSize);
	glEnd();

	// 윗면
	glBindTexture(GL_TEXTURE_2D, itextures[i]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(fSize, fSize, fSize);
	glTexCoord2f(1, 1);
	glVertex3f(fSize, fSize, 0.f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0, fSize, 0.f);
	glTexCoord2f(0, 0);
	glVertex3f(0.f, fSize, fSize);
	glEnd();


	glPopMatrix();
}