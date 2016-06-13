#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

void LoadTexture(const char* filename, int count);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

GLuint textures[6];


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

bool collision(Object Circle, Object Rect);
bool Leftcollision(Object Circle, Object Rect);
bool Rightcollision(Object Circle, Object Rect);
bool Upcollision(Object Circle, Object Rect);
bool Downcollision(Object Circle, Object Rect);


Object tower[7] = { 0, };

Object hero = { 0, };

Object Screen = { 0, };

GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos[] = { 0.0f, 500.0f, 0.0f, 1.0f }; //조명위치
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void init()
{
	tower[0] = { 0, 0, 0 };
	tower[1] = { 100, -25, -100 };

	hero.zTran = 100;

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

	//glutTimerFunc(50, TimerFunction, 1);
	glutTimerFunc(10, TimerFunction, 2);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);

	glutDisplayFunc(DrawScene); // 출력 함수의 지정
	

	glutMainLoop();

}


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
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(50.0f, -50.0f, 50.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(50.0f, -50.0f, 50.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(50.0f, -50.0f, -50.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(50.0f, -50.0f, -50.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-50.0f, -50.0f, -50.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 50.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-50.0f, -50.0f, -50.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-50.0f, -50.0f, 50.0f);

	glEnd();   // Done drawing the pyramid
}

void door()
{
	glPushMatrix();

	glTranslated(175, 50, 150);

	glColor3f(1, 0.5, 0.5);
	glScaled(1, 3, 1);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(175, 50, 0);

	glColor3f(1, 0.5, 0.5);
	glScaled(1, 3, 1);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(175, 100, 75);

	glScaled(1, 1, 2);
	glColor3f(1, 0.5, 0.5);
	glutSolidCube(50);

	glPopMatrix();
}

void DrawVanQuad()
{
	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-25, 0, -25);

	glTexCoord2d(0, 0);
	glVertex3f(-25, 0, 25);

	glTexCoord2d(1, 0);
	glVertex3f(25, 0, 25);

	glTexCoord2d(1, 1);
	glVertex3f(25, 0, -25);

	glEnd();
}

void DrawQuad()
{
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-250, 0, -250);

	glTexCoord2d(1, 1);
	glVertex3f(250, 0, -250);

	glTexCoord2d(1, 0);
	glVertex3f(250, 0, 250);

	glTexCoord2d(0, 0);
	glVertex3f(-250, 0, 250);

	glEnd();
}




void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라
	glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

	glRotated(Screen.xRot + 30, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);


		glPushMatrix();
			
		glRotated(270, 0, 1, 0); //밑면

			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);

			DrawVanQuad();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();


		glPushMatrix(); //왼면

		glTranslated(-250, 250, 0);
		glRotated(90, 0, 0, 1);


			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			
			DrawVanQuad();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //뒷면

			glTranslated(0, 250, -250);
			glRotated(90, 1, 0, 0);
			glRotated(90, 0, 1, 0);


			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);

			DrawVanQuad();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();


		glPushMatrix(); //오른면

			glTranslated(250, 250, 0);
			glRotated(90, 0, 0, 1);


			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[1]);

			DrawVanQuad();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //왼쪽 문
		
			glTranslated(-249, 100, 0);
			glRotated(90, 0, 0, 1);
		
			glColor3f(0, 0, 0);

			glBegin(GL_QUADS);

				glVertex3f(-100, 0, -100);
				glVertex3f(-100, 0, 100);
				glVertex3f(100, 0, 100);
				glVertex3f(100, 0, -100);

			glEnd();

		glPopMatrix();

		glPushMatrix(); //오른쪽 문

			glTranslated(249, 100, 0);
			glRotated(90, 0, 0, 1);

			glColor3f(0, 0, 0);

			glBegin(GL_QUADS);

			glVertex3f(-100, 0, -100);
			glVertex3f(-100, 0, 100);
			glVertex3f(100, 0, 100);
			glVertex3f(100, 0, -100);

			glEnd();

		glPopMatrix();



		glTranslated(0, 25, 0);

		glPushMatrix();
			glTranslated(0, 25, 0);
			DrawPiramid();

		glPopMatrix();


		glPushMatrix(); //hero

			glTranslated(hero.xTran, hero.yTran, hero.zTran);
			glColor3f(1, 0, 0);

			glutSolidSphere(20, 50, 50);

		glPopMatrix();

		glPushMatrix();

			glTranslated(-120, 0, 100);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1, 0, 0, 0.5);

			glutSolidCube(50);
		glPopMatrix();

		glPushMatrix();

			glTranslated(120, 0, 100);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0, 1, 0, 0.5f);

			glutSolidCube(50);

		glPopMatrix();

		glPushMatrix(); //포탈

			glTranslated(100, -25, -100);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1, 1, 0, 0.5f);

			glutSolidCube(50);

		glPopMatrix();

		glPushMatrix();

		glTranslated(0, -25, 120);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0, 0, 1, 0.5f);

		glutSolidCube(50);

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

	glTranslatef(0.0, 0.0, -800.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0번빛을 사용한다.

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	glEnable(GL_BLEND);

	glGenTextures(2, textures);

	LoadTexture("res/floor.bmp", 1);

}

static bool Left_button = false;
static bool Right_button = false;
static bool Up_button = false;
static bool Down_button = false;

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
	if (key == '1')	Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;




	glutPostRedisplay();
}


void TimerFunction(int value)
{
	if (value == 1)
	{

		glutTimerFunc(50, TimerFunction, 1);
	}

	if (value == 2)
	{
		if (hero.xTran < -250 && hero.zTran < 100 && hero.zTran > -100)
		{
			hero.xTran = 240;
		}

		else if (hero.xTran > 250 && hero.zTran < 100 && hero.zTran > -100)
		{
			hero.xTran = -240;
		}
		
		if (collision(hero, tower[1]))
		{
			hero = { 0, 0, 120 };
		}

		if (Left_button)
		{
			if (!Rightcollision(hero, tower[0]))
			{
					hero.xTran -= 4;
			}

		}

		if (Right_button)
		{
			if (!Leftcollision(hero, tower[0]))
			{
					hero.xTran += 4;
			}

		}

		if (Up_button)
		{
			if (!Downcollision(hero, tower[0]))
			{
				if (hero.zTran > -250)
					hero.zTran -= 4;
			}

		}

		if (Down_button)
		{
			if (!Upcollision(hero, tower[0]))
			{
				if (hero.zTran < 250)
					hero.zTran += 4;
			}
		}



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


void LoadTexture(const char* filename, int count)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // 텍스처 모드 설정

	glBindTexture(GL_TEXTURE_2D, textures[count]); //텍스처와 객체를 결합한다.
	pBytes = LoadDIBitmap(filename, &info); //이미지 로딩을 한다.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //텍스처 설정 정의를 한다.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //텍스처 파라미터 설정

	//	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // 텍스처 모드 설정
}

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
