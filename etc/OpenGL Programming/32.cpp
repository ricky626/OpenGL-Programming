#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

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
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	glutMainLoop();

}

Object Screen = { 0, };

GLuint textures[6];

// 윈도우 출력 함수
void DrawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();//카메라

		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot + 30, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);
		
		glPushMatrix();
		
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glBegin(GL_QUADS);
		{
			//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			//앞면
			//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
			glTexCoord2f(1, 1);
			glVertex3f(50.0, 50.0, 50.0f);
			//  glColor3f(1.0f,0.0,1.0f);  // Magenta
			glTexCoord2f(0, 1);
			glVertex3f(-50.0, 50.0, 50.0f);
			//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
			glTexCoord2f(0, 0);
			glVertex3f(-50.0, -50.0, 50.0f);
			//  glColor3f(0.0f,0.0f,1.0f);  // Blue
			glTexCoord2f(1, 0);
			glVertex3f(50.0, -50.0, 50.0f);
		}

		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
		{
			//뒷면
			//  glColor3f(1.0f,1.0f,1.0f);  // White
			glTexCoord2f(1, 1);
			glVertex3f(-50.0, 50.0, -50.0);
			//  glColor3f(0.0f,1.0f,0.0f);  // Green
			glTexCoord2f(0, 1);
			glVertex3f(50.0, 50.0, -50.0);
			//  glColor3f(1.0f,0.0f,0.0f);  // Red
			glTexCoord2f(0, 0);
			glVertex3f(50.0f, -50.0f, -50.0f);
			//  glColor3f(0.0f,0.0f,0.0f);  // Black
			glTexCoord2f(1, 0);
			glVertex3f(-50.0, -50.0, -50.0);

		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS);
		{
			//윗면
			//  glColor3f(1.0f,0.0,1.0f);  // Magenta
			glTexCoord2f(1, 1);
			glVertex3f(-50.0, 50.0, 50.0f);
			//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
			glTexCoord2f(0, 1);
			glVertex3f(50.0, 50.0, 50.0f);
			//  glColor3f(0.0f,1.0f,0.0f);  // Green
			glTexCoord2f(0, 0);
			glVertex3f(50.0, 50.0, -50.0);
			//  glColor3f(1.0f,1.0f,1.0f);  // White
			glTexCoord2f(1, 0);
			glVertex3f(-50.0, 50.0, -50.0);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glBegin(GL_QUADS);
		{
			//아랫면
			//  glColor3f(1.0f,0.0f,0.0f);  // Red
			glTexCoord2f(1, 1);
			glVertex3f(50.0f, -50.0f, -50.0f);
			//  glColor3f(0.0f,0.0f,0.0f);  // Black
			glTexCoord2f(0, 1);
			glVertex3f(50.0, -50.0, 50.0f);
			//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
			glTexCoord2f(0, 0);
			glVertex3f(-50.0, -50.0, 50.0f);
			//  glColor3f(0.0f,0.0f,1.0f);  // Blue
			glTexCoord2f(1, 0);
			glVertex3f(-50.0, -50.0, -50.0);

		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glBegin(GL_QUADS);
		{
			//왼면
			//  glColor3f(1.0f,0.0,1.0f);  // Magenta
			glTexCoord2f(1, 1);
			glVertex3f(-50.0, 50.0, 50.0f);
			//  glColor3f(1.0f,1.0f,1.0f);  // White
			glTexCoord2f(0, 1);
			glVertex3f(-50.0, 50.0, -50.0);
			//  glColor3f(0.0f,0.0f,0.0f);  // Black
			glTexCoord2f(0, 0);
			glVertex3f(-50.0, -50.0, -50.0);
			//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
			glTexCoord2f(1, 0);
			glVertex3f(-50.0, -50.0, 50.0f);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glBegin(GL_QUADS);
		{
			//오른면
			//  glColor3f(0.0f,1.0f,0.0f);  // Green
			glTexCoord2f(1, 1);
			glVertex3f(50.0, 50.0, -50.0);
			//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
			glTexCoord2f(0, 1);
			glVertex3f(50.0, 50.0, 50.0f);
			//  glColor3f(0.0f,0.0f,1.0f);  // Blue
			glTexCoord2f(0, 0);
			glVertex3f(50.0, -50.0, 50.0f);
			//  glColor3f(1.0f,0.0f,0.0f);  // Red
			glTexCoord2f(1, 0);
			glVertex3f(50.0f, -50.0f, -50.0f);
		}
		glEnd();
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

	glTranslatef(0.0, 0.0, -700.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glGenTextures(6, textures); // n개의 이미지 텍스처 매핑을 한다

	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]); //텍스처와 객체를 결합한다.
		pBytes = LoadDIBitmap("res/blue.bmp", &info); //이미지 로딩을 한다.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //텍스처 설정 정의를 한다.

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //텍스처 파라미터 설정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //텍스처 파라미터 설정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //텍스처 파라미터 설정
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //텍스처 파라미터 설정

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE); // 텍스처 모드 설정
	}
	glEnable(GL_TEXTURE_2D);
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
	Screen.yRot += 2;
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