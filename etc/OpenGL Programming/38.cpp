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

GLuint textures[2];


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

Object box = { 0, };

Object torus = { 0, };

Object snow = { 0, };
float moveZ = 1;
bool check = true;

Object hamuk = { 0, };

GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos[] = { 0.0f, 500.0f, 0.0f, 1.0f }; //조명위치
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot + 30, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);

		glPushMatrix();


			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[0]);

				glBegin(GL_QUADS);

				glTexCoord2d(0, 1);
					glVertex3f(-200, -25, -200);

					glTexCoord2d(0, 0);
					glVertex3f(-200, -25, 200);

					glTexCoord2d(1, 0);
					glVertex3f(200, -25, 200);

					glTexCoord2d(1, 1);
					glVertex3f(200, -25, -200);

				glEnd();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix();

		glTranslated(0, 175, -175);

		glRotated(90, 1, 0, 0);

			glColor3f(1, 1, 1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[0]);

			glBegin(GL_QUADS);

			glTexCoord2d(0, 1);
			glVertex3f(-200, -25, -200);

			glTexCoord2d(0, 0);
			glVertex3f(-200, -25, 200);

			glTexCoord2d(1, 0);
			glVertex3f(200, -25, 200);

			glTexCoord2d(1, 1);
			glVertex3f(200, -25, -200);

			glEnd();

			glDisable(GL_TEXTURE_2D);

		glPopMatrix();


		glPushMatrix(); //돌아가는 큐브 불투명

			glTranslated(-130, 20, -100);
			glRotated(120, 0, 1.5, 1);
			glRotated(box.yRot, 1, 0, 0);

			glBlendFunc(GL_ONE, GL_ZERO);
			glColor3f(0, 0, 1);

			glutSolidCube(20);

		glPopMatrix();

		glPushMatrix(); //돌아가는 큐브 투명

			glTranslated(-130, 30, -100);

			glRotated(120, 0, 1.5, 1);
			glRotated(box.yRot, 1, 0, 1);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(1, 1, 0, 0.5);
					glutSolidCube(60);

		glPopMatrix();

		glPushMatrix(); //관람차 토러스

			glBlendFunc(GL_ONE, GL_ZERO);

			glColor3f(1, 1, 1);

			glTranslated(100, 130, -150);

			glutSolidTorus(5, 100, 30, 30);
			
		glPopMatrix();

		glPushMatrix(); //관람차 막대기

			glColor3f(1, 1, 1);

			glTranslated(100, 130, -150);
			glRotated(torus.zTran, 0, 0, 1);

			glScaled(0.5f, 9.0f, 0.5f);
			glutSolidCube(30);

		glPopMatrix();

		glPushMatrix(); //관람차 막대기

			glColor3f(1, 1, 1);

			glTranslated(100, 130, -150);
			glRotated(90, 0, 0, 1);
			glRotated(torus.zTran, 0, 0, 1);

			glScaled(0.5f, 9.0f, 0.5f);
			glutSolidCube(30);

		glPopMatrix();


		glPushMatrix();

			glTranslated(100, 130, -150);
			glRotated(45, 0, 0, 1);
			glRotated(torus.zTran, 0, 0, 1);

			glScaled(0.5f, 9.0f, 0.5f);
			glutSolidCube(30);

		glPopMatrix();

		glPushMatrix();

			glTranslated(100, 130, -150);
			glRotated(-45, 0, 0, 1);
			glRotated(torus.zTran, 0, 0, 1);

			glScaled(0.5f, 9.0f, 0.5f);
			glutSolidCube(30);

		glPopMatrix();



			glPushMatrix(); //관람차

			

			glTranslated(100, 130, -150);

				glRotated(torus.zTran, 0, 0, 1);

				glTranslated(0, 140, 0);
				glRotated(torus.yTran, 0, 0, 1);



				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix();

				//glTranslated(100, 0, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(0, -140, 0);
			glRotated(torus.yTran, 0, 0, 1);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix();

				//glTranslated(-30, 130, -150);
				
			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(140, 0, 0);
			glRotated(torus.yTran, 0, 0, 1);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix(); 

				//glTranslated(230, 130, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(-140, 0, 0);
			glRotated(torus.yTran, 0, 0, 1);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix();

				//glTranslated(5, 25, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(140 / sqrt(2), 140 /sqrt(2), 0);
			//glRotated(45, 0, 0, 1);
			glRotated(torus.yTran, 0, 0, 1);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix();

				//glTranslated(200, 25, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(-140 / sqrt(2), -140 / sqrt(2), 0);
			//glRotated(45, 0, 0, 1);
			glRotated(torus.yTran, 0, 0, 1);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix(); 

				//glTranslated(5, 230, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(-140 / sqrt(2), 140 / sqrt(2), 0);
			//glRotated(45, 0, 0, 1);
			glRotated(torus.yTran, 0, 0, 1);
				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix(); 

				
				//glTranslated(200, 230, -150);

			glTranslated(100, 130, -150);

			glRotated(torus.zTran, 0, 0, 1);

			glTranslated(140 / sqrt(2), -140 / sqrt(2), 0);
			//glRotated(45, 0, 0, 1);
			glRotated(torus.yTran, 0, 0, 1);
				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();

			glPushMatrix(); //관람차

				glTranslated(100, 130, -150);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();
			////////////////////////////////////////////////////



			////////////////////////왼쪽 해먹
			glPushMatrix();
			glTranslated(-100, 150, 100);

			glRotated(hamuk.zRot, 0, 0, 1);

			glTranslated(0, -100, 0);


				glColor3f(0, 0, 1);

				glScaled(10, 1, 5);

				glutSolidCube(10);

			glPopMatrix();

			glPushMatrix();

				glTranslated(-100, 150, 100);
				glRotated(hamuk.zRot, 0, 0, 1);

				glColor3f(1, 0, 0);
				glLineWidth(5);

				glBegin(GL_LINE_LOOP);

					glVertex3f(0, 0, 0);
					glVertex3f(-50, -100, 0);
					glVertex3f(50, -100, 0);

				glEnd();

			glPopMatrix();

			glPushMatrix();

				glTranslated(-100, 150, 100);
				glRotated(hamuk.zRot, 0, 0, 1);

				glColor3f(0, 1, 1);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();


			/////////////////////오른쪽 해먹
	
			

			glPushMatrix();
				

			glTranslated(100, 150, 100);

			glRotated(-hamuk.zRot, 0, 0, 1);

			glTranslated(0, -100, 0);

				glColor3f(0, 0, 1);

				glScaled(10, 1, 5);

				glutSolidCube(10);

			glPopMatrix();

			glPushMatrix();

				glTranslated(100, 150, 100);

				glRotated(-hamuk.zRot, 0, 0, 1);

				glColor3f(1, 0, 0);
				glLineWidth(5);

				glBegin(GL_LINE_LOOP);

					glVertex3f(0, 0, 0);
					glVertex3f(-50, -100, 0);
					glVertex3f(50, -100, 0);

				glEnd();


			glPopMatrix();


			glPushMatrix();

				glTranslated(100, 150, 100);

				glRotated(-hamuk.zRot, 0, 0, 1);

				glColor3f(0, 1, 1);

				glutSolidSphere(10, 20, 20);

			glPopMatrix();


			/////////////////////////

			if (check == false)
			{
				glPushMatrix(); //눈사람

					glTranslated(-snow.xTran, 150, 100);

					glRotated(hamuk.zRot, 0, 0, 1);
					glTranslated(0, -75, 0);

					glColor3f(1, 1, 0);

					glutSolidSphere(20, 20, 20);

					glTranslated(0, 25, 0);

					glutSolidSphere(10, 20, 20);


				glPopMatrix();
			}
			else if (check == true)
			{
				glPushMatrix(); //눈사람

					glTranslated(snow.xTran, 150, 100);

					glRotated(-hamuk.zRot, 0, 0, 1);
					glTranslated(0, -75, 0);

					glColor3f(1, 1, 0);

					glutSolidSphere(20, 20, 20);

					glTranslated(0, 25, 0);

					glutSolidSphere(10, 20, 20);


				glPopMatrix();
			}
			



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

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);

	glGenTextures(1, textures);

	LoadTexture("res/floor.bmp", 0);

	snow.xTran = 100;
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
	else if(key == 27) exit(0);

	glutPostRedisplay();
}


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

}

void TimerFunction(int value)
{
	if (value == 1)
	{
		box.yRot += 2;
		torus.zTran -= 1;

		torus.yTran += 1;

		if (hamuk.zRot == -40)
		{
			moveZ *= -1;
		}
		else if (hamuk.zRot == 40)
		{
			moveZ *= -1;
			check = !check;
		}
		hamuk.zRot -= moveZ;


		glutTimerFunc(10, TimerFunction, 1);
		glutPostRedisplay();
	}

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
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
