
#include <sstream>
using std::ostringstream;
#include <iomanip>
using std::fixed;
using std::setprecision;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cstdlib>
using std::exit;
#ifndef __APPLE__-
# include <GL/glut.h>   
#else
# include <GLUT/glut.h>
#endif

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
Building g_building[8];

static int g_maxBuilding = -400;



Object Screen = { 0, };
Object box = { 0, };

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0 };
FireCracker		fire[3];
float moveY[30][30] = { 0, };

int weather = 1;
const int ESCKEY = 27;

const int startwinsize = 800;

const double vertsize = 15;
const double curvewid = 3.;
const double polywid = 2.;
const int numcurvesegments = 100;

const double tensionchg = 0.01;
vector<vector<GLdouble> > verts;
bool currentlymoving;
int selectedvert;
vector<GLdouble> savevert;
int savemx, savemy;
bool drawpoly;
bool drawverts;

double tension;
int max_count = 0;
int View_Mode = 1;

void Reshape(int w, int h);
void TimerFunction(int value);
void bresenhamLine(int x1, int y1, int x2, int y2);

void drawCardinalSpline(const vector<vector<GLdouble> > & v,
	int segs,
	double c)
{
	int n = verts.size();

	if (n <= 2)
	{
		if (n == 1)
		{
			glBegin(GL_POINTS);
			glVertex2dv(&v[0][0]);
			glEnd();
		}
		else if (n == 2)
		{
			glBegin(GL_LINES);
			glVertex2dv(&v[0][0]);
			glVertex2dv(&v[1][0]);
			glEnd();
		}
		return;
	}


	double xa, xb, xc, xd;
	double ya, yb, yc, yd;
	glBegin(GL_LINE_STRIP);

	xa = (1. - c) / 2 * verts[0][0]
		- 1. / 2 * verts[1][0]
		+ c / 2 * verts[2][0];
	xb = 0.;
	xc = (c - 3.) / 2 * verts[0][0]
		+ 3. / 2 * verts[1][0]
		+ -c / 2 * verts[2][0];
	xd = verts[0][0];
	ya = (1. - c) / 2 * verts[0][1]
		- 1. / 2 * verts[1][1]
		+ c / 2 * verts[2][1];
	yb = 0.;
	yc = (c - 3.) / 2 * verts[0][1]
		+ 3. / 2 * verts[1][1]
		+ -c / 2 * verts[2][1];
	yd = verts[0][1];
	for (int k = 1; k <= segs; ++k)
	{
		double t = double(k) / segs;
		double x = xa*t*t*t + xb*t*t + xc*t + xd;
		double y = ya*t*t*t + yb*t*t + yc*t + yd;
		glVertex2d(x, y);
	}

	glVertex2dv(&verts[1][0]);
	for (int j = 0; j < n - 3; ++j)
	{
		xa = -c*verts[j][0]
			+ (2. - c)*verts[j + 1][0]
			+ (c - 2.)*verts[j + 2][0]
			+ c*verts[j + 3][0];
		xb = 2.*c*verts[j][0]
			+ (c - 3.)*verts[j + 1][0]
			+ (3. - 2.*c)*verts[j + 2][0]
			- c*verts[j + 3][0];
		xc = -c*verts[j][0]
			+ c*verts[j + 2][0];
		xd = verts[j + 1][0];
		ya = -c*verts[j][1]
			+ (2. - c)*verts[j + 1][1]
			+ (c - 2.)*verts[j + 2][1]
			+ c*verts[j + 3][1];
		yb = 2.*c*verts[j][1]
			+ (c - 3.)*verts[j + 1][1]
			+ (3. - 2.*c)*verts[j + 2][1]
			- c*verts[j + 3][1];
		yc = -c*verts[j][1]
			+ c*verts[j + 2][1];
		yd = verts[j + 1][1];
		for (int k = 1; k <= segs; ++k)
		{
			double t = double(k) / segs;
			double x = xa*t*t*t + xb*t*t + xc*t + xd;
			double y = ya*t*t*t + yb*t*t + yc*t + yd;
			glVertex2d(x, y);
		}
	}

	xa = -c / 2 * verts[n - 3][0]
		+ 1. / 2 * verts[n - 2][0]
		+ (c - 1.) / 2 * verts[n - 1][0];
	xb = 3.*c / 2 * verts[n - 3][0]
		- 3. / 2 * verts[n - 2][0]
		+ (3. - 3.*c) / 2 * verts[n - 1][0];
	xc = -c*verts[n - 3][0]
		+ c*verts[n - 1][0];
	xd = verts[n - 2][0];
	ya = -c / 2 * verts[n - 3][1]
		+ 1. / 2 * verts[n - 2][1]
		+ (c - 1.) / 2 * verts[n - 1][1];
	yb = 3.*c / 2 * verts[n - 3][1]
		- 3. / 2 * verts[n - 2][1]
		+ (3. - 3.*c) / 2 * verts[n - 1][1];
	yc = -c*verts[n - 3][1]
		+ c*verts[n - 1][1];
	yd = verts[n - 2][1];
	for (int k = 1; k <= segs; ++k)
	{
		double t = double(k) / segs;
		double x = xa*t*t*t + xb*t*t + xc*t + xd;
		double y = ya*t*t*t + yb*t*t + yc*t + yd;
		glVertex2d(x, y);
	}

	glEnd();
}

void DrawVanQuad()
{
	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-400, 0, -400);
	glTexCoord2d(0, 0);
	glVertex3f(-400, 0, 400);
	glTexCoord2d(1, 0);
	glVertex3f(400, 0, 400);
	glTexCoord2d(1, 1);
	glVertex3f(400, 0, -400);

	glEnd();
}

void DrawQuad()
{
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(-400, 0, -400);
	glTexCoord2d(1, 1);
	glVertex3f(400, 0, -400);
	glTexCoord2d(1, 0);
	glVertex3f(400, 0, 400);
	glTexCoord2d(0, 0);
	glVertex3f(-400, 0, 400);

	glEnd();
}

void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();


	glTranslated(Screen.xTran, Screen.yTran, Screen.zTran);

	glRotated(Screen.xRot, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);

	if (View_Mode == 2)
	{
		glTranslatef(0.0, -400.0, -700.0);
		glRotated(90, 0, 1, 0);
	}
	else if (View_Mode == 3)
	{
		glTranslatef(-400.0, -400.0, -1500.0);
	}


	/*glPushMatrix();

	glTranslated(100, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);

	glColor3ub(255, 0, 0);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();


	glTranslated(200, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);
	glColor3ub(0, 255, 0);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(300, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);
	glColor3ub(0, 0, 255);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(400, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);
	glColor3ub(255, 255, 0);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(500, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);
	glColor3ub(0, 255, 255);
	glutSolidCube(50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(600, 50, 0);
	if (View_Mode == 3)
		glRotated(box.yRot, 0, 1, 0);
	glColor3ub(255, 0, 255);
	glutSolidCube(50);

	glPopMatrix();*/

	for (int i = 0; i < 8; ++i){
		glPushMatrix();
		if (View_Mode != 3)
		{
			glTranslated(0, 300, 0);
		}

		else if (View_Mode == 3)
		{
			glTranslated(0, 200, 0);
			//glRotated(box.yRot, 0, 1, 0);
		}
				

			glColor3f(g_building[i].GetColorR(), g_building[i].GetColorG(), g_building[i].GetColorB());
			glTranslatef(g_building[i].GetTransX(), g_building[i].GetTransY(), g_building[i].GetTransZ());
			glScalef(1.0, g_building[i].GetScaleY(), 1.0);
			glutSolidCube(g_building[i].GetSize());
		glPopMatrix();
	}

	if (View_Mode == 3)
	{
		glPushMatrix(); //큐브


		//glTranslatef(400.0, 400.0, 700);
		glTranslated(400, 0, 0);
		glRotated(box.yRot, 0, 1, 0);


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

		glTranslated(-400, 400, 0);

		glRotated(90, 0, 0, 1);
		DrawQuad();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		glPushMatrix(); //뒷면

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glColor3f(1, 1, 1);

		glTranslated(0, 400, -400);

		glRotated(90, 0, 0, 1);
		glRotated(90, 1, 0, 0);
		DrawVanQuad();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix(); //오른면

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glColor3f(1, 1, 1);

		glTranslated(400, 400, 0);


		glRotated(90, 0, 0, 1);
		DrawVanQuad();
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //앞면
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glColor3f(1, 1, 1);

		glTranslated(0, 400, 400);

		glRotated(90, 1, 0, 0);
		glRotated(90, 0, 1, 0);

		DrawQuad();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		if (weather == 2)
		{
			glPushMatrix();

			glColor3ub(67, 218, 236);


			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					glLoadIdentity();


					glTranslatef(0.0, 0.0, -1500.0);
					glRotated(box.yRot, 0, 1, 0);

					glScaled(0.5, 7, 0.5);

					glTranslatef(Snow[i][j].xTran, Snow[i][j].yTran, Snow[i][j].zTran);


					glutSolidCube(5);
				}
			}

			glPopMatrix();
		}

		else if (weather == 3)
		{
			glPushMatrix(); //눈

			glColor3f(1, 1, 1);


			for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					glLoadIdentity();


					glTranslatef(0.0, 0.0, -1500.0);
					glRotated(box.yRot, 0, 1, 0);

					glTranslatef(Snow[i][j].xTran, Snow[i][j].yTran, Snow[i][j].zTran);


					glutSolidCube(5);
				}
			}
			glPopMatrix();
		}




		glPopMatrix();
	}

	glPushMatrix();
	// Draw control points ("verts")
	//glLoadIdentity();

	if (View_Mode == 3)
	{
		glTranslatef(0.0, 50.0, -100.0);

	}

	if (drawverts)
	{

		glPointSize(vertsize);
		glBegin(GL_POINTS);
		for (int i = 0; i<verts.size(); ++i)
		{
			if (i == selectedvert)
				glColor3d(1., 0., 0.);
			else
				glColor3d(0., 0., 0.);
			glVertex2dv(&verts[i][0]);
		}
		glEnd();
	}

	// Draw control polygon
	if (verts.size() >= 2 && drawpoly)
	{

		glLineWidth(polywid);
		glColor3d(0.4, 0.4, 0.4);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i<verts.size(); ++i)
			glVertex2dv(&verts[i][0]);
		glEnd();
	}
	//glPopMatrix();

	//glPushMatrix();
	// Draw curve
	glColor3d(0.0, 0.0, 1.0);
	glPointSize(curvewid);
	glLineWidth(curvewid);

	drawCardinalSpline(verts, numcurvesegments, tension);

	glPopMatrix();


	glPushMatrix();
	{
		for (int i = 0; i < 3; ++i) {
			glPushMatrix();
			glTranslated(200, 0, 100);
			if (i == 0) {
				glTranslatef(-100, 0, -250);
				glColor3f(0.5, 0, 0);

			}
			else if (i == 1) {
				glTranslatef(100, 0, -250);
				glColor3f(0.0, 0, 0.5);
			}
			else if (i == 2) {
				glTranslatef(500, 0, -250);
				glColor3f(0.0, 0.7, 0.0);
			}

			if (fire[i].ani1 == false)
				bresenhamLine(0, fire[i].lineSize, 0, fire[i].lineSize + 100);

			else {
				if (i == 0) {
					glPushMatrix();
					{
						glTranslatef(0, 500, 0);
						bresenhamLine(-fire[i].fireSize, -fire[i].fireSize, fire[i].fireSize, fire[i].fireSize);
						bresenhamLine(-fire[i].fireSize, fire[i].fireSize, fire[i].fireSize, -fire[i].fireSize);
						bresenhamLine(0, fire[i].fireSize, 0, -fire[i].fireSize);
					}
					glPopMatrix();
				}
				else if (i == 1) {
					glPushMatrix();
					{
						glTranslatef(0, 500, 0);
						bresenhamLine(-fire[i].fireSize, -fire[i].fireSize, fire[i].fireSize, fire[i].fireSize);
						bresenhamLine(-fire[i].fireSize, fire[i].fireSize, fire[i].fireSize, -fire[i].fireSize);
						bresenhamLine(0, fire[i].fireSize, 0, -fire[i].fireSize);
					}
					glPopMatrix();
				}
				else if (i == 2) {
					glPushMatrix();
					{
						glTranslatef(0, 400, 0);
						bresenhamLine(-fire[i].fireSize, -fire[i].fireSize, fire[i].fireSize, fire[i].fireSize);
						bresenhamLine(-fire[i].fireSize, fire[i].fireSize, fire[i].fireSize, -fire[i].fireSize);
						bresenhamLine(0, fire[i].fireSize, 0, -fire[i].fireSize);
					}
					glPopMatrix();
				}
			}
			glPopMatrix();
		}


	}
	glPopMatrix();

	glPopMatrix();

	// Draw documentation
	//glLoadIdentity();
	//glMatrixMode(GL_PROJECTION);  // Set up simple ortho projection

	//glMatrixMode(GL_MODELVIEW);

	glutSwapBuffers();
}




void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': case '1':
		View_Mode = 1;
		Reshape(800, 800);
		//glDisable(GL_LIGHT0); // 1번빛을 사용한다.
		//glDisable(GL_LIGHT1); // 1번빛을 사용한다.
		glutPostRedisplay();
		break;
	case 'w': case '2':
		View_Mode = 2;
		Reshape(800, 800);
		//glDisable(GL_LIGHT0); // 1번빛을 사용한다.
		//glDisable(GL_LIGHT1); // 1번빛을 사용한다.
		glutPostRedisplay();
		break;
	case 'e': case '3':
		View_Mode = 3;
		Reshape(800, 800);
		glEnable(GL_LIGHT0); // 0번빛을 사용한다.
		glEnable(GL_LIGHT1); // 1번빛을 사용한다.
		glutPostRedisplay();
		break;
	case 'a':
		if (View_Mode == 3)
		{
			Screen.xRot -= 2;
			glutPostRedisplay();
		}
		break;
	case 'b':
		if (View_Mode == 3)
		{
			Screen.xRot += 2;
			glutPostRedisplay();
		}
		break;
	case 'c':
		if (View_Mode == 3)
		{
			Screen.yRot -= 2;
			glutPostRedisplay();
		}
		break;
	case '4':
		if (View_Mode == 3)
		{
			Screen.yRot += 2;
			glutPostRedisplay();
		}
		break;
	case '5':
		if (View_Mode == 3)
		{
			Screen.zRot -= 2;
			glutPostRedisplay();
		}
		break;
	case '6':
		if (View_Mode == 3)
		{
			Screen.zRot += 2;
			glutPostRedisplay();
		}
		break;

	case ESCKEY:  // Esc: quit
		exit(0);
		break;
	case 'p':
	case 'P':
		drawpoly = !drawpoly;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		drawverts = !drawverts;
		glutPostRedisplay();
		break;
	}
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (View_Mode == 1)
	{
		glOrtho(0, w, startwinsize - h, startwinsize, 0, 800);

	}
	else if (View_Mode == 2)
	{

		gluPerspective(60.0f, w / h, 1.0, 4000); //투영 변환 ( 원근 투영 )

	}


	else if (View_Mode == 3)
	{
		gluPerspective(60.0f, w / h, 1.0, 4000.0); //투영 변환 ( 원근 투영 )

	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	printf("View mode : %d\n", View_Mode);
}

void Mouse(int button, int state, int x, int y)
{
	if (button != GLUT_LEFT_BUTTON)
		return;

	if (state == GLUT_UP)
	{
		currentlymoving = false;
		printf("%d %d\n", x, startwinsize - y);
		return;
	}

	int mousex = x;
	int mousey = startwinsize - y;

	int i;
	for (i = 0; i < verts.size(); ++i)
	{
		int slop = (vertsize / 2) + 2;
		if (mousex >= verts[i][0] - slop
			&& mousex <= verts[i][0] + slop
			&& mousey >= verts[i][1] - slop
			&& mousey <= verts[i][1] + slop) break;
	}

	if (i == verts.size())
	{
		verts.push_back(vector<GLdouble>(2));
		verts[i][0] = mousex;
		verts[i][1] = mousey;
	}

	selectedvert = i;
	savemx = mousex; savemy = mousey;
	savevert = verts[i];
	currentlymoving = true;

	glutPostRedisplay();
}


void Mousemotion(int x, int y)
{
	if (!currentlymoving) return;

	int mousex = x;
	int mousey = startwinsize - y;

	verts[selectedvert][0] = savevert[0] + mousex - savemx;
	verts[selectedvert][1] = savevert[1] + mousey - savemy;

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		box.yRot -= 1;

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				if (weather == 3)
				{
					if (Snow[i][j].yTran > -400)
						Snow[i][j].yTran -= moveY[i][j];
					else
					{
						Snow[i][j].xTran = rand() % 800 - 400;
						Snow[i][j].yTran = rand() % 800 - 400;
						Snow[i][j].zTran = rand() % 800 - 400;
					}
				}
				else if (weather == 2)
				{
					if (Snow[i][j].yTran > -50)
						Snow[i][j].yTran -= moveY[i][j];
					else
					{
						Snow[i][j].xTran = rand() % 1600 - 800;
						Snow[i][j].yTran = rand() % 1600 - 800;
						Snow[i][j].zTran = rand() % 1600 - 800;
					}
				}
			}
		}

		glutPostRedisplay();
		glutTimerFunc(10, TimerFunction, 1);
	}

	if (value == 2)
	{
		if (fire[0].ani1 == true)
		{
			fire[0].fireSize += 1;
			if (fire[0].fireSize >= 40)
			{
				fire[0].fireSize = 0;
				fire[0].ani1 = false;
			}
		}
		else
			fire[0].lineSize += 10;

		if (fire[0].lineSize >= 400)
		{
			fire[0].lineSize = 0;
			fire[0].ani1 = true;
		}

		if (fire[1].ani1 == true)
		{
			fire[1].fireSize += 1;
			if (fire[1].fireSize >= 40)
			{
				fire[1].fireSize = 0;
				fire[1].ani1 = false;
			}
		}
		else
			fire[1].lineSize += 5;
		if (fire[1].lineSize >= 500)
		{
			fire[1].lineSize = 0;
			fire[1].ani1 = true;
		}
		if (fire[2].ani1 == true)
		{
			fire[2].fireSize += 2;
			if (fire[2].fireSize >= 30)
			{
				fire[2].fireSize = 0;
				fire[2].ani1 = false;
			}
		}
		else
			fire[2].lineSize += 15;

		if (fire[2].lineSize >= 300)
		{
			fire[2].lineSize = 0;
			fire[2].ani1 = true;
		}

		glutPostRedisplay();
		glutTimerFunc(30, TimerFunction, 2);
	}
}


void init()
{
	currentlymoving = false;
	selectedvert = -1;
	drawpoly = false;
	drawverts = true;

	tension = 0.5;
	int minX = 0;
	for (int i = 0; i < 8; ++i){
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

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glGenTextures(2, textures);

	LoadTexture("res/floor.bmp", 1);

	glEnable(GL_LIGHTING); // 빛을 사용한다.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0번빛을 사용한다.

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT1); // 1번빛을 사용한다.

	//Ambient(물체가 은은하게 나타내는색), Diffuse(물체의 주된 색상), Specular(물체의 면이 띄게 될 색), Emission(발광색), Shiness(빛나는정도)
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			Snow[i][j].xTran = rand() % 800 - 400;
			Snow[i][j].yTran = rand() % 800 - 400;
			Snow[i][j].zTran = rand() % 800 - 400;

			moveY[i][j] = rand() % 5 + 1;
		}
	}
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

void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		weather = 1; // default
		break;
	case 2:
		weather = 2; // rain
		break;
	case 3:
		weather = 3; // snow
		break;
	}
}

void bresenhamLine(int x1, int y1, int x2, int y2)
{
	int dx, dy;
	int p_value;
	int minus, plus, value;
	int ndx;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	if (dy <= dx){
		minus = 2 * dy;
		plus = 2 * (dy - dx);

		if (x2<x1){
			ndx = x1;
			x1 = x2;
			x2 = ndx;

			ndx = y1;
			y1 = y2;
			y2 = ndx;
		}
		if (y1 < y2){
			value = 1;
		}
		else {
			value = -1;
		}
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);

		p_value = 2 * dy - dx;
		for (ndx = x1; ndx<x2; ++ndx){
			if (0>p_value){
				p_value += minus;
			}
			else {
				p_value += plus;
				y1 += value;
			}
			glVertex2f(ndx, y1);
		}
		glEnd();
	}
	else
	{
		minus = 2 * dx;
		plus = 2 * (dx - dy);

		if (y2 < y1){
			ndx = y1;
			y1 = y2;
			y2 = ndx;

			ndx = x1;
			x1 = x2;
			x2 = ndx;
		}

		if (x1<x2){
			value = 1;
		}
		else {
			value = -1;
		}
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		p_value = 2 * dx - dy;

		for (ndx = y1; ndx < y2; ++ndx){
			if (0>p_value){
				p_value += minus;
			}
			else {
				p_value += plus;
				x1 += value;
			}
			glVertex2f(x1, ndx);
		}
		glEnd();
	}
}



int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(startwinsize, startwinsize);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("숙제2");

	init();
	glutDisplayFunc(DrawScene);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(30, TimerFunction, 2);
	glutMouseFunc(Mouse);
	glutMotionFunc(Mousemotion);

	int SubMenu1;
	int MainMenu;

	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("맑음", 1);
	glutAddMenuEntry("비", 2);
	glutAddMenuEntry("눈", 3);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("날씨", SubMenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}
