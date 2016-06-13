#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <Digitalv.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

struct _POINT
{
	int x;
	int y;
};

typedef struct OBJECT{
	_POINT point;
	_POINT Rect2;
	_POINT Rect3;
	_POINT Rect4;
	int check; // 0:아무것도 아닐때, 1:밑면충돌, 2:왼면충돌, 3:오른면충돌
	bool inWater; //전체가 물속에 담겨있으면 True 아니면 False

}OBJECT;

typedef struct DISH
{
	_POINT point;
	_POINT Rect2;
	_POINT Rect3;
	_POINT Rect4;

}DISH;

typedef struct WATER
{
	_POINT point;
	_POINT Rect2;
	_POINT Rect3;
	_POINT Rect4;
}WATER;

typedef struct LINE
{
	_POINT Start;
	_POINT End;

	int check;
}LINE;


GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);

void Timerfunction(int value);

void MoveBox();
int GetDir(int _x);
bool GetBox(LINE A, LINE B, _POINT* outputLine);
bool inWaterRect(WATER water, LINE B, _POINT* outputLine);

void CreateBox();
void CreateBox2();	

void Create();
int GetSmall();

bool BotCrash(OBJECT* Rect, DISH* Rect2);//아래면 충돌
bool LeftCrash(OBJECT* Rect, DISH* Rect2);//왼면 충돌
bool RightCrash(OBJECT* Rect, DISH* Rect2);//오른면 충돌


OBJECT* Object[100][3];
LINE* Line = NULL;
int DishmoveX = 2;
int WaterScale = 1;


DISH Dish = { 300, 450, 300, 550, 500, 550, 500, 450 };
WATER Water = { 300, 490, 500, 490, 500, 550, 300, 550};//-10


bool cutState = false;
int MoveDir = 0;
int Small = 0;
int count = 0;


int RIGHT = 0;
int LEFT = 1;


MCI_OPEN_PARMS      mciOpenbgm; //파일을 로드
MCI_OPEN_PARMS      mciOpenget; //파일을 로드
MCI_OPEN_PARMS      mciOpenclick; //파일을 로드
MCI_OPEN_PARMS      mciOpenslice; //파일을 로드

MCI_PLAY_PARMS       mciPlaybgm; //파일을 재생
MCI_PLAY_PARMS       mciPlayget; //파일을 재생
MCI_PLAY_PARMS       mciPlayclick; //파일을 재생
MCI_PLAY_PARMS       mciPlayslice; //파일을 재생

UINT wDeviceIDbgm = 0;
UINT wDeviceIDget = 0;
UINT wDeviceIDclick = 0;
UINT wDeviceIDslice = 0;


void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example4");
	glutReshapeFunc(Reshape);
	glutTimerFunc(15, Timerfunction, 1);
	glutTimerFunc(30, Timerfunction, 2);
	Create();

	glutDisplayFunc(DrawScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);

	LPCWSTR bgm = L"mainsound.mp3";
	LPCWSTR get = L"get.mp3";
	LPCWSTR slice = L"slice.mp3";
	LPCWSTR click = L"click.mp3";

	mciOpenbgm.lpstrDeviceType = L"MPEGVideo"; //파일 형식
	mciOpenget.lpstrDeviceType = L"MPEGVideo"; //파일 형식
	mciOpenclick.lpstrDeviceType = L"MPEGVideo"; //파일 형식
	mciOpenslice.lpstrDeviceType = L"MPEGVideo"; //파일 형식

	mciOpenbgm.lpstrElementName = bgm;// 파일이름
	mciOpenget.lpstrElementName = get; // 파일이름
	mciOpenclick.lpstrElementName = click; // 파일이름
	mciOpenslice.lpstrElementName = slice; // 파일이름

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenbgm);
	mciSendCommand(1, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenget);
	mciSendCommand(2, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenclick);
	mciSendCommand(3, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenslice);

	wDeviceIDbgm = mciOpenbgm.wDeviceID;
	wDeviceIDget = mciOpenget.wDeviceID;
	wDeviceIDclick = mciOpenclick.wDeviceID;
	wDeviceIDslice = mciOpenslice.wDeviceID;
	//MCI_NOTIFY
	mciSendCommand(wDeviceIDbgm, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	mciSendCommand(wDeviceIDbgm, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlaybgm);
	//1000 = 1초
	//64초
	glutTimerFunc(64500, Timerfunction, 3);
	
	
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);

	if (Line == NULL)
	{
		Line = new LINE();
		Line->Start.x = 0;
		Line->Start.y = 0;
		Line->End.x = 0;
		Line->End.y = 0;
		Line->check = 0;
	}
}

void Create()
{
	for (int i = 0; i < 3; i++)
		Object[count][i] = NULL;

	if (Object[count][0] == NULL)
	{
		Object[count][0] = new OBJECT();
		Object[count][0]->point.x = 100;
		Object[count][0]->point.y = 100;
		Object[count][0]->Rect2.x = 200;
		Object[count][0]->Rect2.y = 100;
		Object[count][0]->Rect3.x = 200;
		Object[count][0]->Rect3.y = 200;
		Object[count][0]->Rect4.x = 100;
		Object[count][0]->Rect4.y = 200;
		Object[count][0]->check = 0;
		Object[count][0]->inWater = false;
	}
}

GLvoid DrawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	glColor3ub(0, 0, 0);

	glPushMatrix();

		glBegin(GL_LINES);
			glVertex2d(Dish.point.x, Dish.point.y);
			glVertex2d(Dish.Rect2.x, Dish.Rect2.y);

			glVertex2d(Dish.Rect2.x, Dish.Rect2.y);
			glVertex2d(Dish.Rect3.x, Dish.Rect3.y);

			glVertex2d(Dish.Rect3.x, Dish.Rect3.y);
			glVertex2d(Dish.Rect4.x, Dish.Rect4.y);
		glEnd();

	glPopMatrix();

	glColor3f(0, 0, 1.0);

	glPushMatrix();
		
		glBegin(GL_POLYGON);

			glVertex2d(Water.point.x, Water.point.y);
			glVertex2d(Water.Rect2.x, Water.Rect2.y);

			glVertex2d(Water.Rect3.x, Water.Rect3.y);
			glVertex2d(Water.Rect4.x, Water.Rect4.y);
			
		glEnd();
		
	glPopMatrix();

	glPushMatrix();

		for (int j = 0; j <= count; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				if (Object[j][i] != NULL)
				{
					glColor3f(1, 0, 0);

					glBegin(GL_POLYGON);

						glVertex2d(Object[j][i]->point.x, Object[j][i]->point.y);
						glVertex2d(Object[j][i]->Rect2.x, Object[j][i]->Rect2.y);
						glVertex2d(Object[j][i]->Rect3.x, Object[j][i]->Rect3.y);
						glVertex2d(Object[j][i]->Rect4.x, Object[j][i]->Rect4.y);

					glEnd();

				}
			}
		}

	glPopMatrix();

	glPushMatrix();

		for (int j = 0; j <= count; j++)
		{
			if (Object[j][2] != NULL)
			{
				glColor3f(0.5, 0, 0);
				
				glBegin(GL_POLYGON);

					glVertex2d(Object[j][2]->point.x, Object[j][2]->point.y);
					glVertex2d(Object[j][2]->Rect2.x, Object[j][2]->Rect2.y);
					glVertex2d(Object[j][2]->Rect3.x, Object[j][2]->Rect3.y);
					glVertex2d(Object[j][2]->Rect4.x, Object[j][2]->Rect4.y);

				glEnd();

				glLineWidth(3);

				glColor3f(1, 1, 0);

				glBegin(GL_LINE_STRIP);

					glVertex2d(Object[j][2]->point.x, Object[j][2]->point.y);
					glVertex2d(Object[j][2]->Rect2.x, Object[j][2]->Rect2.y);
					glVertex2d(Object[j][2]->Rect3.x, Object[j][2]->Rect3.y);
					glVertex2d(Object[j][2]->Rect4.x, Object[j][2]->Rect4.y);
					glVertex2d(Object[j][2]->point.x, Object[j][2]->point.y);
				glEnd();

			}
		}

	glPopMatrix();

	glLineWidth(1);
	glPushMatrix();

		if (Line->check == 2)
		{
			glColor3f(0, 0, 0);

			glBegin(GL_LINES);
				glVertex2d(Line->Start.x, Line->Start.y);
				glVertex2d(Line->End.x, Line->End.y);
			glEnd();
		}
	glPopMatrix();

	glutSwapBuffers();
}

void Mouse(int button, int state, int _x, int _y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Line->Start.x = _x;
		Line->Start.y = _y;
		Line->check = 1;
		mciSendCommand(wDeviceIDclick, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDclick, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayclick);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (cutState == false && Line->End.x != 0 && Line->End.y != 0)
			CreateBox();

		Line->check = 0;
		Line->Start.x = 0;
		Line->Start.y = 0;
		Line->End.x = 0;
		Line->End.y = 0;

		mciSendCommand(wDeviceIDclick, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDclick, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayclick);
		
	}

	glutPostRedisplay();
}

void MouseMove(int _x, int _y)
{
	if (Line->check == 1 || Line->check == 2)
	{
		Line->End.x = _x;
		Line->End.y = _y;
		Line->check = 2;
	}

	glutPostRedisplay();
}

void Timerfunction(int value)
{
	if (value == 1)
	{
		if (Dish.point.x == 590 || Dish.point.x == 10)
		{
			DishmoveX *= -1;
		}

		Dish.point.x += DishmoveX;
		Dish.Rect2.x += DishmoveX;
		Dish.Rect3.x += DishmoveX;
		Dish.Rect4.x += DishmoveX;

		Water.point.x += DishmoveX;
		Water.Rect2.x += DishmoveX;
		Water.Rect3.x += DishmoveX;
		Water.Rect4.x += DishmoveX;

		for (int j = 0; j <= count; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (Object[j][i] != NULL && Object[j][i]->check == 1)
				{
					Object[j][i]->point.x += DishmoveX;
					Object[j][i]->Rect2.x += DishmoveX;
					Object[j][i]->Rect3.x += DishmoveX;
					Object[j][i]->Rect4.x += DishmoveX;
				}
			}
		}

		if (Object[count][Small] != NULL && Object[count][Small]->check == 2)
		{
			Object[count][Small]->point.x -= 12;
			Object[count][Small]->point.y += 10;

			Object[count][Small]->Rect2.x -= 12;
			Object[count][Small]->Rect2.y += 10;

			Object[count][Small]->Rect3.x -= 12;
			Object[count][Small]->Rect3.y += 10;

			Object[count][Small]->Rect4.x -= 12;
			Object[count][Small]->Rect4.y += 10;
		}

		if (Object[count][Small] != NULL && Object[count][Small]->check == 3)
		{
			Object[count][Small]->point.x += 12;
			Object[count][Small]->point.y += 10;

			Object[count][Small]->Rect2.x += 12;
			Object[count][Small]->Rect2.y += 10;

			Object[count][Small]->Rect3.x += 12;
			Object[count][Small]->Rect3.y += 10;

			Object[count][Small]->Rect4.x += 12;
			Object[count][Small]->Rect4.y += 10;
		}

		MoveBox();
		glutTimerFunc(10, Timerfunction, 1);
		glutPostRedisplay();
	}

	if (value == 2)
	{
		if (Water.point.y == 485 || Water.Rect2.y == 495)
		{
			WaterScale *= -1;
		}
			

		Water.point.y -= WaterScale;
		Water.Rect2.y -= WaterScale;

		for (int i = 0; i <= count; i++)
		{
			if (Object[i][2] != NULL && Object[i][2]->check == 1 && Object[i][2]->inWater != true)
			{
				
				Object[i][Small]->Rect3.y -= WaterScale;
				Object[i][Small]->Rect4.y -= WaterScale;
				Object[i][!Small]->Rect3.y -= WaterScale;
				Object[i][!Small]->Rect4.y -= WaterScale;
				Object[i][2]->point.y -= WaterScale;
				Object[i][2]->Rect2.y -= WaterScale;
			}
		}
		glutTimerFunc(30, Timerfunction, 2);
		glutPostRedisplay();
	}

	if (value == 3)
	{
		mciSendCommand(wDeviceIDbgm, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDbgm, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlaybgm);
		glutTimerFunc(64500, Timerfunction, 3);
	}
}
bool abc = false;

void MoveBox()
{
	if (!cutState)
	{
		for (int i = 0; i < 2; i++)
		{
			if (Object[count][i] != NULL)
			{
				if (MoveDir == LEFT)
				{
					Object[count][i]->point.x -= 4;
					Object[count][i]->Rect2.x -= 4;
					Object[count][i]->Rect3.x -= 4;
					Object[count][i]->Rect4.x -= 4;

				}

				else if (MoveDir == RIGHT)
				{
					Object[count][i]->point.x += 4;
					Object[count][i]->Rect2.x += 4;
					Object[count][i]->Rect3.x += 4;
					Object[count][i]->Rect4.x += 4;
				}

				MoveDir = GetDir(Object[count][i]->point.x);
			}
		}
		
	}
	else
	{
		if (BotCrash(Object[count][Small], &Dish) && Object[count][Small]->check != 2 && Object[count][Small]->check != 3 && abc == false) // 밑면 충돌
		{
			Object[count][Small]->check = 1;
			CreateBox2();
			abc = true;
		}

		if (LeftCrash(Object[count][Small], &Dish) && Object[count][Small]->check != 1) //왼면 충돌
		{
			Object[count][Small]->check = 2;
			//mciSendCommand(wDeviceIDfail, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			//mciSendCommand(wDeviceIDfail, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayfail);
		}

		if (RightCrash(Object[count][Small], &Dish) && Object[count][Small]->check != 1) // 오른면 충돌
		{
			Object[count][Small]->check = 3;
			//mciSendCommand(wDeviceIDfail, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			//mciSendCommand(wDeviceIDfail, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayfail);
		}

		if (Object[count][!Small]->point.x >= 1000 || Object[count][!Small]->point.x <= -300) //초기화
		{
			count++;
			Create();
			cutState = false;
			abc = false;
			return;
		}

		if (Object[count][Small]->point.y < 800)
		{
			if (Object[count][Small]->check == 0)
			{
				Object[count][Small]->point.y += 12;
				Object[count][Small]->Rect2.y += 12;
				Object[count][Small]->Rect3.y += 12;
				Object[count][Small]->Rect4.y += 12;
			}
			else if (Object[count][Small]->check == 2 || Object[count][Small]->check == 3)
			{
				Object[count][Small]->point.y += 3;
				Object[count][Small]->Rect2.y += 3;
				Object[count][Small]->Rect3.y += 3;
				Object[count][Small]->Rect4.y += 3;
			}
		}

		if (MoveDir == RIGHT)
		{
			Object[count][!Small]->point.x += 4;
			Object[count][!Small]->Rect2.x += 4;
			Object[count][!Small]->Rect3.x += 4;
			Object[count][!Small]->Rect4.x += 4;
		}

		else if (MoveDir == LEFT)
		{
			Object[count][!Small]->point.x -= 4;
			Object[count][!Small]->Rect2.x -= 4;
			Object[count][!Small]->Rect3.x -= 4;
			Object[count][!Small]->Rect4.x -= 4;
		}
	}
}

int GetDir(int _x)
{
	if (_x < 625 && _x > 75)
		return MoveDir;
	return (_x >= 625) ? LEFT : RIGHT;
}

bool GetBox(LINE A, LINE B, _POINT* outputLine)
{
	double check = ((B.End.y - B.Start.y)*(A.End.x - A.Start.x)) - ((B.End.x - B.Start.x)*(A.End.y - A.Start.y));

	double _t = (B.End.x - B.Start.x)*(A.Start.y - B.Start.y) - (B.End.y - B.Start.y)*(A.Start.x - B.Start.x);
	double _s = (A.End.x - A.Start.x)*(A.Start.y - B.Start.y) - (A.End.y - A.Start.y)*(A.Start.x - B.Start.x);

	double t = _t / check;
	double s = _s / check;
	if (t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if (t == 0.0 && s == 0.0) return false;
	outputLine->x = A.Start.x + t * (A.End.x - A.Start.x);
	outputLine->y = A.Start.y + t * (A.End.y - A.Start.y);
	return true;
}

bool inWaterRect(WATER water, LINE B, _POINT* outputLine2)
{
	double check = ((B.End.y - B.Start.y)*(water.Rect2.x - water.point.x)) - ((B.End.x - B.Start.x)*(water.Rect2.y - water.point.y));

	double _t = (B.End.x - B.Start.x)*(water.point.y - B.Start.y) - (B.End.y - B.Start.y)*(water.point.x - B.Start.x);
	double _s = (water.Rect2.x - water.point.x)*(water.point.y - B.Start.y) - (water.Rect2.y - water.point.y)*(water.point.x - B.Start.x);

	double t = _t / check;
	double s = _s / check;
	if (t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if (t == 0.0 && s == 0.0) return false;

	outputLine2->x = water.point.x + t * (water.Rect2.x - water.point.x);
	outputLine2->y = water.point.y + t * (water.Rect2.y - water.point.y);
	return true;
}


void CreateBox()
{
	LINE TempLine[4];
	for (int i = 0; i <4; i++) 
	{
		TempLine[i].Start.x = TempLine[i].End.x = Object[count][0]->point.x;
		TempLine[i].Start.y = TempLine[i].End.y = Object[count][0]->point.y;
		if (i == 0)
			TempLine[i].End.y = Object[count][0]->Rect4.y;
		else if (i == 1)
			TempLine[i].End.x = Object[count][0]->Rect2.x;
		else if (i == 2)
		{
			TempLine[i].End.y = Object[count][0]->Rect3.y;
			TempLine[i].Start.x = Object[count][0]->Rect2.x;
			TempLine[i].End.x = Object[count][0]->Rect3.x;

		}
		else if (i == 3)
		{
			TempLine[i].Start.y = Object[count][0]->Rect4.y;
			TempLine[i].End.y = Object[count][0]->Rect4.y;
			TempLine[i].End.x = Object[count][0]->Rect3.x;
		}
	}

	_POINT OutPutLine[2];
	int CollDir[2];
	int Count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (GetBox(*Line, TempLine[i], &OutPutLine[Count]))
		{
			CollDir[Count] = i;
			Count++;
		}
		if (Count == 2)
			break;
	}
	if (Count == 2)
	{

		Object[count][1] = new OBJECT;
		Object[count][1]->point = Object[count][0]->point;
		Object[count][1]->Rect2 = Object[count][0]->Rect2;
		Object[count][1]->Rect3 = Object[count][0]->Rect3;
		Object[count][1]->Rect4 = Object[count][0]->Rect4;
		Object[count][1]->check = 0;
		Object[count][1]->inWater = false;

		mciSendCommand(wDeviceIDslice, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDslice, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayslice);

		for (int i = 0; i< 2; i++)
		{
			if (CollDir[i] == 0)
			{
				Object[count][0]->Rect4.y = OutPutLine[i].y;
				Object[count][0]->Rect4.x = OutPutLine[i].x;

				Object[count][1]->point.y = OutPutLine[i].y;
				Object[count][1]->point.x = OutPutLine[i].x;

			}
			else if (CollDir[i] == 2)
			{
				Object[count][0]->Rect3.y = OutPutLine[i].y;
				Object[count][0]->Rect3.x = OutPutLine[i].x;
				Object[count][1]->Rect2.y = OutPutLine[i].y;
				Object[count][1]->Rect2.x = OutPutLine[i].x;

			}
			else if (CollDir[i] == 1)
			{
				Object[count][0]->Rect2.x = OutPutLine[i].x;
				Object[count][0]->Rect2.y = OutPutLine[i].y;

				Object[count][1]->point.x = OutPutLine[i].x;
				Object[count][1]->point.y = OutPutLine[i].y;

			}
			else if (CollDir[i] == 3)
			{
				Object[count][0]->Rect3.x = OutPutLine[i].x;
				Object[count][0]->Rect3.y = OutPutLine[i].y;

				Object[count][1]->Rect4.x = OutPutLine[i].x;
				Object[count][1]->Rect4.y = OutPutLine[i].y;
			}
		}
		Small = GetSmall();
		cutState = true;

	}
}

void CreateBox2()
{
	int Smalls = GetSmall();

	LINE TempLine[4];
	for (int i = 0; i <4; i++)
	{
		TempLine[i].Start.x = TempLine[i].End.x = Object[count][Smalls]->point.x;
		TempLine[i].Start.y = TempLine[i].End.y = Object[count][Smalls]->point.y;
		if (i == 0)
			TempLine[i].End.y = Object[count][Smalls]->Rect4.y;
		else if (i == 1)
			TempLine[i].End.x = Object[count][Smalls]->Rect2.x;
		else if (i == 2)
		{
			TempLine[i].End.y = Object[count][Smalls]->Rect3.y;
			TempLine[i].Start.x = Object[count][Smalls]->Rect2.x;
			TempLine[i].End.x = Object[count][Smalls]->Rect3.x;

		}
		else if (i == 3)
		{
			TempLine[i].Start.y = Object[count][Smalls]->Rect4.y;
			TempLine[i].End.y = Object[count][Smalls]->Rect4.y;
			TempLine[i].End.x = Object[count][Smalls]->Rect3.x;
		}
	}

	_POINT OutPutLine2[2];
	int CollDir[2];
	int Count = 0;

	for (int i = 0; i < 4; i++)
	{
		if (inWaterRect(Water, TempLine[i], &OutPutLine2[Count]))
		{
			CollDir[Count] = i;
			Count++;
		}

		if (Count == 2)
			break;

		if (Count == 0)
			break;
	}

	if (Count == 0 && Object[count][Smalls]->check == 1)
	{
		Object[count][2] = new OBJECT;
		
		Object[count][2]->point = Object[count][Smalls]->point;
		Object[count][2]->Rect2 = Object[count][Smalls]->Rect2;
		Object[count][2]->Rect3 = Object[count][Smalls]->Rect3;
		Object[count][2]->Rect4 = Object[count][Smalls]->Rect4;
		Object[count][2]->check = 1;
		Object[count][2]->inWater = true;

		mciSendCommand(wDeviceIDget, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDget, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayget);

		cutState = true;
		return;
	}

	if (Count == 2)
	{

		Object[count][2] = new OBJECT;
		Object[count][2]->point = Object[count][Smalls]->point;
		Object[count][2]->Rect2 = Object[count][Smalls]->Rect2;
		Object[count][2]->Rect3 = Object[count][Smalls]->Rect3;
		Object[count][2]->Rect4 = Object[count][Smalls]->Rect4;
		Object[count][2]->check = 1;
		mciSendCommand(wDeviceIDget, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(wDeviceIDget, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayget);
		for (int i = 0; i< 2; i++)
		{
			if (CollDir[i] == 0)
			{
				Object[count][Smalls]->Rect4.x = OutPutLine2[i].x;
				Object[count][Smalls]->Rect4.y = OutPutLine2[i].y;
				
				Object[count][2]->point.x = OutPutLine2[i].x;
				Object[count][2]->point.y = OutPutLine2[i].y;

			}

			else if (CollDir[i] == 2)
			{
				Object[count][Smalls]->Rect3.x = OutPutLine2[i].x;
				Object[count][Smalls]->Rect3.y = OutPutLine2[i].y;
				
				Object[count][2]->Rect2.x = OutPutLine2[i].x;
				Object[count][2]->Rect2.y = OutPutLine2[i].y;
			}

			else if (CollDir[i] == 1)
			{
				Object[count][Smalls]->Rect2.x = OutPutLine2[i].x;
				Object[count][Smalls]->Rect2.y = OutPutLine2[i].y;

				Object[count][2]->point.x = OutPutLine2[i].x;
				Object[count][2]->point.y = OutPutLine2[i].y;

			}
			else if (CollDir[i] == 3)
			{
				Object[count][Smalls]->Rect3.x = OutPutLine2[i].x;
				Object[count][Smalls]->Rect3.y = OutPutLine2[i].y;

				Object[count][2]->Rect4.x = OutPutLine2[i].x;
				Object[count][2]->Rect4.y = OutPutLine2[i].y;
			}
		}
		cutState = true;
	}
}


int GetSmall()
{
	long Wh = (Object[count][0]->Rect3.x - Object[count][0]->point.x) * (Object[count][0]->Rect3.y - Object[count][0]->point.y);
	long Wh1 = (Object[count][1]->Rect3.x - Object[count][1]->point.x) * (Object[count][1]->Rect3.y - Object[count][1]->point.y);

	if (abs(Wh) > abs(Wh1))
		return 1;
	else
		return 0;
}

bool BotCrash(OBJECT* Rect, DISH* Rect2) //밑면 충돌
{
	float Left = Rect->point.x + 1;
	float Top = Rect->point.y;
	float Right = Rect->Rect3.x - 1;
	float Bottom = Rect->Rect3.y;

	if (Rect->Rect3.y < Rect->Rect4.y)
		Bottom = Rect->Rect4.y + 4;
		

	float Left2 = Rect2->Rect2.x;
	float Top2 = Rect2->Rect2.y  - 4;
	float Right2 = Rect2->Rect3.x;
	float Bottom2 = Rect2->Rect3.y - 4 ;

	if (Left <= Right2 && Right >= Left2 && Top <= Bottom2 && Bottom >= Top2)
		return true;
	else
		return false;
}

bool LeftCrash(OBJECT* Rect, DISH* Rect2) //왼면 충돌
{
	float Left = Rect->point.x;
	float Top = Rect->point.y - 4;
	float Right = Rect->Rect3.x;
	float Bottom = Rect->Rect3.y - 4;

	float Left2 = Rect2->point.x;
	float Top2 = Rect2->point.y;
	float Right2 = Rect2->Rect2.x;
	float Bottom2 = Rect2->Rect2.y;

	if (Left <= Right2 && Right >= Left2 && Top <= Bottom2 && Bottom >= Top2)
		return true;
	else
		return false;
}

bool RightCrash(OBJECT* Rect, DISH* Rect2) //오른면 충돌
{
	float Left = Rect->point.x;
	float Top = Rect->point.y - 4;
	float Right = Rect->Rect3.x;
	float Bottom = Rect->Rect4.y - 4;

	float Left2 = Rect2->Rect4.x;
	float Top2 = Rect2->Rect4.y;
	float Right2 = Rect2->Rect3.x;
	float Bottom2 = Rect2->Rect3.y;

	if (Left <= Right2 && Right >= Left2 && Top <= Bottom2 && Bottom >= Top2)
		return true;
	else
		return false;
}