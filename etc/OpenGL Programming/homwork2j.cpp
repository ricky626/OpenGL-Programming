#include <iostream>
#include <cmath>
#include <gl/glut.h>
#include <time.h>
#include <windows.h>
#include <list>
using namespace std;

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600
#define SCREEN_FIELD 2000
#define SCREEN_FAR 800
#define INIT_FAR 1000
#define RECT_SIZE 10
#define MAX_VERTEX 20
#define MAX_BUILDING 8

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Mouse(int button, int state, int x, int y);

void Initialize();
void Release();

static float screen_X = 0;
static float screen_Y = 0;
static float screen_Z = 0;
static float near_farZ = 0;
static bool View_Mode = true;

#include <math.h>
#include <Windows.h>

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

void LoadTexture(const char* filename, int count);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

GLuint textures[6];

GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //물체가 은은하게 나타내는 색

GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체의 주된 색상

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //물체의 면이 띄게 될 색

GLfloat lightPos1[] = { -600.0f, -1500.0f, -1000.0f, 1.0f }; //좌측 상단
GLfloat lightPos2[] = { -200.0f, -1500.0f, -1000.0f, 1.0f }; //우측 상단


GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

typedef struct Object
{
	float xTran;
	float yTran;
	float zTran;

	float xRot;
	float yRot;
	float zRot;
}Object;

struct XYZ {
	float x;
	float y;
	float z;
};

struct FireCracker {
	XYZ pos;

	float lineSize;
	float fireSize;

	bool ani1;
};


Object Screen = { 0, };
Object box = { 0, };

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0 };
FireCracker		fire[3];
float moveY[30][30] = { 0, };

int weather = 1;

class RollerCoaster
{
private:
	float x;
	float y;
	float z;

public:
	RollerCoaster()
		: x(0), y(0), z(0){}
	RollerCoaster(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z){}
	RollerCoaster(const RollerCoaster& r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
	}

public:
	float Get_X() const { return x; }
	float Get_Y() const { return y; }
	float Get_Z() const { return z; }
public:
	void Set_X(float _x) { x = _x; }
	void Set_Y(float _y) { y = _y; }
	void Set_Z(float _z) { z = _z; }
};

class C_Point
{
private:
	float x;
	float y;
	float z;

public:
	C_Point() : x(-750), y(750) {}
	C_Point(float f_x, float f_y) : x(f_x), y(f_y) {}
	C_Point(const C_Point &copy) : x(copy.x), y(copy.y) {}
	float Get_X() const { return x; }
	float Get_Y() const { return y; }
	float Get_Z() const { return z; }
	void Change_Point(float c_x, float c_y) { x = c_x; y = c_y; }

	void Click_Point(float m_x, float m_y)

	{
		x = m_x;
		y = m_y;
	}
};

class Building
{
private:
	float m_fColorR;
	float m_fColorG;
	float m_fColorB;
	float m_nScaleY;
	int m_nTransX;
	int m_nTransY;
	int m_nTransZ;
	int m_nSize;

public:
	Building(){}
public:
	float GetColorR() { return m_fColorB; }
	float GetColorG() { return m_fColorG; }
	float GetColorB() { return m_fColorB; }
	int GetTransX() { return m_nTransX; }
	int GetTransY() { return m_nTransY; }
	int GetTransZ() { return m_nTransZ; }
	float GetScaleY() { return m_nScaleY; }
	int GetSize() { return m_nSize; }

public:
	void SetColorR(float _r) { m_fColorR = _r; }
	void SetColorG(float _g) { m_fColorG = _g; }
	void SetColorB(float _b) { m_fColorB = _b; }
	void SetTransX(int _x) { m_nTransX = _x; }
	void SetTransY(int _y) { m_nTransY = _y; }
	void SetTransZ(int _z) { m_nTransZ = _z; }
	void SetScaleY(float _y) { m_nScaleY = _y; }
	void SetSize(int _s){ m_nSize = _s; }

public:
	float RandFloat(float a, float b)
	{

		return ((b - a)*((float)rand() / RAND_MAX)) + a;
	}
};
C_Point c_point[MAX_VERTEX];
Building g_building[MAX_BUILDING];



static int click_count = 1;
static bool click_TF = true;
static float tension = 0;
static int roop_count = 0;
static int g_maxBuilding = -400;

bool rollerCoasterInit_TF = false;
static bool coasterMove_TF = false;
static int coasterCurCnt = 0;
static int coasterCnt = 0;
static RollerCoaster r[400];
C_Point Cardinals_Spline(C_Point &p0, C_Point &p1, C_Point &p2, C_Point &p3, float tension, float t);

void DrawVanQuad()
{
	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-100, 0, -100);
	glTexCoord2d(0, 0);
	glVertex3f(-100, 0, 100);
	glTexCoord2d(1, 0);
	glVertex3f(100, 0, 100);
	glTexCoord2d(1, 1);
	glVertex3f(100, 0, -100);

	glEnd();
}

void DrawQuad()
{
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-100, 0, -100);
	glTexCoord2d(1, 1);
	glVertex3f(100, 0, -100);
	glTexCoord2d(1, 0);
	glVertex3f(100, 0, 100);
	glTexCoord2d(0, 0);
	glVertex3f(-100, 0, 100);

	glEnd();
}

void main(int arg, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	Initialize();
	glutCreateWindow("숙제2");
	glutDisplayFunc(drawScene);
	glutTimerFunc(800, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	Release();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*       시작점 끝점 미리 초기화       */

	glLoadIdentity();
	glTranslatef(0, 0, -INIT_FAR + near_farZ);
	glRotatef(screen_X, 1.0, 0.0, 0.0);
	glRotatef(screen_Y, 0.0, 1.0, 0.0);
	glRotatef(screen_Z, 0.0, 0.0, 1.0);

	if (!View_Mode)
	{
		glPushMatrix(); //큐브

		glColor3f(0 , 1, 1);
		glTranslated(0, -100, 0);

		glPushMatrix(); //밑면
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glRotated(90, 0, 1, 0);

		glColor3f(1, 1, 1);
		DrawVanQuad();

		glDisable(GL_TEXTURE_2D);


		glPopMatrix();

		glPushMatrix();	 //왼면

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glColor3f(1, 1, 1);

		glTranslated(-100, 100, 0);

		glRotated(90, 0, 0, 1);
		DrawQuad();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		glPushMatrix(); //뒷면

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glColor3f(1, 1, 1);

		glTranslated(0, 100, -100);

		glRotated(90, 0, 0, 1);
		glRotated(90, 1, 0, 0);
		DrawVanQuad();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix(); //오른면

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glColor3f(1, 1, 1);

		glTranslated(100, 100, 0);


		glRotated(90, 0, 0, 1);
		DrawVanQuad();
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //앞면
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glColor3f(1, 1, 1);

		glTranslated(0, 100, 100);

		glRotated(90, 1, 0, 0);
		glRotated(90, 0, 1, 0);

		DrawQuad();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	else if (View_Mode)
	{

		glPushMatrix();
		glColor3f(0.1f, 0.1f, 0.1f);   // gray
		glTranslatef(0, -210, 0);
		glScalef(100.0, 1.0, 1.0);
		glutSolidCube(20);
		glPopMatrix();

	}

	if (roop_count == 0){
		c_point[0].Change_Point(-750, 0);
		c_point[19].Change_Point(750, 0);
	}
	/*               End                */
	glLoadIdentity();
	glTranslatef(0, 0, -INIT_FAR - 800 + near_farZ);
	glRotatef(screen_X, 1.0, 0.0, 0.0);
	glRotatef(screen_Y, 0.0, 1.0, 0.0);
	glRotatef(screen_Z, 0.0, 0.0, 1.0);

	/*           제어점 출력            */
	for (int i = 1; i < click_count; i++)
	{
		glLoadIdentity();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(c_point[i].Get_X(), c_point[i].Get_Y(), -5);
		glutSolidCube(5);
	}
	/*               End                */

	/*           Spline Draw             */
	glLoadIdentity();
	glTranslatef(0, 0, -INIT_FAR + near_farZ);
	glRotatef(screen_X, 1.0, 0.0, 0.0);
	glRotatef(screen_Y, 0.0, 1.0, 0.0);
	glRotatef(screen_Z, 0.0, 0.0, 1.0);

	int valueCnt = 0;
	if (click_count == 21)
	{
		for (int line = 0; line < MAX_VERTEX - 1; line++)
		{
			for (float t = 0; t<1; t += 0.005f)
			{
				glBegin(GL_POINTS);
				glPointSize(3);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(Cardinals_Spline(c_point[line], c_point[line + 1], c_point[line + 2], c_point[line + 3], tension, t).Get_X(),
					Cardinals_Spline(c_point[line], c_point[line + 1], c_point[line + 2], c_point[line + 3], tension, t).Get_Y(), -5);
				glEnd();


				if (!rollerCoasterInit_TF && valueCnt == 10){
					r[coasterCnt].Set_X(Cardinals_Spline(c_point[line], c_point[line + 1], c_point[line + 2], c_point[line + 3], tension, t).Get_X());
					r[coasterCnt].Set_Y(Cardinals_Spline(c_point[line], c_point[line + 1], c_point[line + 2], c_point[line + 3], tension, t).Get_Y());
					r[coasterCnt].Set_Z(-5);
					++coasterCnt;
					valueCnt = 0;
				}
				++valueCnt;

			}

		}
		if (!rollerCoasterInit_TF)
			rollerCoasterInit_TF = true;
	}
	/*            Draw End             */

	for (int i = 0; i < MAX_BUILDING; ++i){
		glPushMatrix();
		glColor3f(g_building[i].GetColorR(), g_building[i].GetColorG(), g_building[i].GetColorB());
		glTranslatef(g_building[i].GetTransX(), g_building[i].GetTransY(), g_building[i].GetTransZ());
		glScalef(1.0, g_building[i].GetScaleY(), 1.0);
		glutSolidCube(g_building[i].GetSize());
		glPopMatrix();
	}

	if (coasterMove_TF && click_count == 21){
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(r[coasterCurCnt].Get_X(), r[coasterCurCnt].Get_Y(), r[coasterCurCnt].Get_Z());
		glutSolidCube(30);
		glPopMatrix();
	}

	roop_count++;
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (View_Mode)
		glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -1, SCREEN_FIELD);
	else
		gluPerspective(60, w / h, 1, 4000);

	glMatrixMode(GL_MODELVIEW);


}
GLvoid TimerFunction(int value)
{
	if (coasterMove_TF && coasterCurCnt < coasterCnt){
		++coasterCurCnt;
		glutTimerFunc(30, TimerFunction, 1);
	}
	glutPostRedisplay();
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		tension += 0.1;
		break;
	case '2':
		tension -= 0.1;
		break;
	case 'x':
		screen_X += 2.0;
		break;
	case 'X':
		screen_X -= 2.0;
		break;
	case 'y':
		screen_Y += 2.0;
		break;
	case 'Y':
		screen_Y -= 2.0;
		break;
	case 'z':
		screen_Z += 2.0;
		break;
	case 'Z':
		screen_Z -= 2.0;
		break;
	case '-':
		near_farZ += 20.0;
		break;
	case '=':
		near_farZ -= 20.0;
		break;
	case '3':
		View_Mode = !View_Mode;
		Reshape(SCREEN_WIDTH, SCREEN_HEIGHT);

		break;
	case 'r': case 'R':
		coasterMove_TF = true;
		coasterCurCnt = 0;
		glutTimerFunc(100, TimerFunction, 1);
		break;


	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float real_x = x - SCREEN_WIDTH / 2;
		float real_y = SCREEN_HEIGHT / 2 - y;

		cout << "real_y = " << real_y << endl;

		if (click_count < 21){                                                            //클릭횟수 15번이상이되면 더이상 제어점을 찍지 않는다.
			for (int i = 0; i< MAX_VERTEX; i++)
			{
				if (((c_point[i].Get_X() < real_x && real_x < c_point[i].Get_X() + RECT_SIZE) &&            //클릭하는곳이 제어점이라면 찍지않는다 (비활성화)
					(c_point[i].Get_Y() < real_y && real_y < c_point[i].Get_Y() + RECT_SIZE))

					)
				{
					click_TF = false;
					break;                                                               //하나라도 겹치면 false로 처리하고 if문을 빠져나간다.
				}
				else                                                                  //아니면 (홣성화)
					click_TF = true;
			}
			if (click_TF && (real_y > g_maxBuilding))
			{
				c_point[click_count].Click_Point(real_x, real_y);                                 //각 제어점 포인트 설정.
				click_count++;                                                            //클릭시마다 클릭카운트 증가.
			}
		}


		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutPostRedisplay();
	}


}
C_Point Cardinals_Spline(C_Point &p0, C_Point &p1, C_Point &p2, C_Point &p3, float tension, float t)
{

	float t2 = t * t;
	float t3 = t2 * t;

	float s = (1 - tension) / 2;

	float b1 = s * ((-t3 + (2 * t2)) - t);
	float b2 = s * (-t3 + t2) + (2 * t3 - 3 * t2 + 1);
	float b3 = s * (t3 - 2 * t2 + t) + (-2 * t3 + 3 * t2);
	float b4 = s * (t3 - t2);

	float x = (p0.Get_X()*b1 + p1.Get_X()*b2 + p2.Get_X()*b3 + p3.Get_X()*b4);
	float y = (p0.Get_Y()*b1 + p1.Get_Y()*b2 + p2.Get_Y()*b3 + p3.Get_Y()*b4);

	return C_Point(x, y);
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

void Initialize()
{
	int minX = -400;

	for (int i = 0; i < MAX_BUILDING; ++i){
		srand(GetTickCount());

		g_building[i].SetColorR(g_building[i].RandFloat(0.0, 1.0));
		g_building[i].SetColorG(g_building[i].RandFloat(0.0, 1.0));
		g_building[i].SetColorB(g_building[i].RandFloat(0.0, 1.0));
		g_building[i].SetScaleY(g_building[i].RandFloat(1.0, 2.5));
		g_building[i].SetSize(rand() % 50 + 30);
		g_building[i].SetTransX(rand() % 800 - 350);
		g_building[i].SetTransY((-200 + (((float)g_building[i].GetSize()*g_building[i].GetScaleY()) / 2)));
		g_building[i].SetTransZ(rand() % 100 - 50);

		minX += rand() % 20 + 80;
		g_building[i].SetTransX(minX);

		Sleep(50);

		if ((g_building[i].GetTransY() + (((float)g_building[i].GetSize()*g_building[i].GetScaleY()) / 2)) > g_maxBuilding)
			g_maxBuilding = (g_building[i].GetTransY() + (((float)g_building[i].GetSize()*g_building[i].GetScaleY()) / 2));
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glGenTextures(2, textures);

	LoadTexture("res/floor.bmp", 1);

}

void Release()
{
}