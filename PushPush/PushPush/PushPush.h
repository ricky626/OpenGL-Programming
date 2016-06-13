#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "inc/fmod.hpp"
#pragma comment (lib, "lib/fmodex_vc.lib")

typedef struct Object
{
	float xTran;
	float yTran;
	float zTran;

	float xRot;
	float yRot;
	float zRot;

	int check;

}Object;


enum MapState//mapcheck ����
{
	NONE = 0,      // �ƹ��͵� ���� �� ����

	BOX_1 = 1,      // 1�� �ڽ�
	BOX_2 = 2,      // 2�� �ڽ�
	BOX_3 = 3,      // 3�� �ڽ�

	INPUSH_BOX = 4,   //Ǫ�� �ڽ�
	END_POS = 5,   //������
	START = 6,      //ĳ����

	MUK = 7, //��
	GEE = 8, //��
	BAR = 9, //��

	END_MUK = 10, //������ ��
	END_GEE = 11, //������ ��
	END_BAR = 12, //������ ��

};

enum Crash//�浹��Ȳ
{
	NO_CRASH = 0, //�浹���� �̵�����
	NO_PUSH = 1, //1~3�����̶� �浹������ ����� �и����� ����
	PUSH_OK = 2, //�м� �ִ� ��ϰ� �浹�Ͽ� �б� ����
};


enum Image//�ؽ��� �̸�
{
	BMP_FLOOR = 0, // ��Ʈ�� �ڽ�
	BMP_MUK = 1, // ��Ʈ�� ��
	BMP_GEE = 2, //��Ʈ�� ��
	BMP_BAR = 3, //��Ʈ�� ��
	BMP_END_MUK = 4,
	BMP_END_GEE = 5,
	BMP_END_BAR = 6,
	BMP_BOTTOM = 7,
	BMP_BACKGROUND = 8,
	BMP_STAR1 = 9,
	BMP_STAR2 = 10,
	BMP_MENU1 = 11,
	BMP_MENU2 = 12,
	BMP_END,

};

enum VERSUS //����������
{
	WIN = 0,
	LOSE = 1,
	DRAW = 2,
};


enum SOUND
{
	SOUND_MAIN = 0,
	SOUND_MENU = 1,
	SOUND_WIN = 2,
	SOUND_DRAW = 3,
	SOUND_LOSE = 4,
	SOUND_SWAP = 5,
	SOUND_WALK = 6,
	SOUND_SCENECHANGE = 7,
	SOUND_RESET = 8,
	SOUND_END,
};

enum DIR
{
	NOPE = 0,
	DOWN = 1,
	LEFT = 2,
	UP = 3,
	RIGHT = 4,
};

enum GAME
{
	GAME_MENU = 0,
	GAME_MAIN = 1,
};

int GAME_STATE = GAME_MENU;

#define Width 15 //���� �ڽ� ������Ʈ �ִ� ����
#define Height 15 //���� �ڽ� ������Ʈ �ִ� ����
#define BoxSize 50 //�ڽ� ũ��
#define Boxinitpos 350 //������� �������� ����ش�


Object box[Height][Width] = { 0, }; //��ü ������Ʈ���� ��ǥ (������, ĳ���� ����)
int mapcheck[Height][Width] = { 0, }; //��ü ������Ʈ���� �ε���

Object hero = { 0, };  //ĳ���� ��ǥ



Object torus = { 0, }; //������ ��ǥ
Object Screen = { 0, }; //ī�޶� ��ǥ

int Stage_number = 1; //���� �������� ��ȣ
int hat_stateCount = 0; // ĳ���� ���ھִϸ��̼� üũ ����
int win_count = 0; //�������� �����Ͽ� �̱� Ƚ��
int draw_count = 0; //�������� �����Ͽ� ��� Ƚ��
int lose_count = 0; //�������� �����Ͽ� �� Ƚ��

int max_endcount = 0; //�� �������� ����


float end_r[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //�� �������� ����
float end_g[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //�� �������� ����
float end_b[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //�� �������� ����

Object end_box[10] = { 0, }; //���������� ��ǥ

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0 };

float moveY[30][30] = { 0, };



/* �ݹ��Լ� */

void DrawScene();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void TimerFunctionFromBoard(int value);

/* �ݹ��Լ� */


/* �ؽ��� ���� */

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
void LoadTexture(const char* filename, unsigned int sizeX, unsigned int sizeY, int count);
GLubyte *pBytes; // �����͸� ����ų ������

BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLuint textures[BMP_END];

/* �ؽ��� ���� */


/* �浹 ó�� */

bool collision(Object Circle, Object Rect);
int Leftcollision(Object Circle, Object(*Rect)[Width]);
int Rightcollision(Object Circle, Object(*Rect)[Width]);
int Upcollision(Object Circle, Object(*Rect)[Width]);
int Downcollision(Object Circle, Object(*Rect)[Width]);

void swap(int* a, int* b); // ���� �ΰ��� ����
void Whowin(int in, int end, int index); //���������� ���и� ����
void MoveBox(char str[]); //�ڽ��� �̵���Ų��
void DownBox(int saveX, int saveZ);

int left_saveX = -1, left_saveZ = -1; // �ε��� �ڽ��� �ε��� �ѹ��� ����ϴ� ����
int right_saveX = -1, right_saveZ = -1;
int up_saveX = -1, up_saveZ = -1;
int down_saveX = -1, down_saveZ = -1;

int left_dsaveX = -1, left_dsaveZ = -1; // �ε��� �ڽ��� �ε��� �ѹ��� ����ϴ� ����
int right_dsaveX = -1, right_dsaveZ = -1;
int up_dsaveX = -1, up_dsaveZ = -1;
int down_dsaveX = -1, down_dsaveZ = -1;

bool LeftDowncheck = false; //�������� ������ �ڽ��� ������ ������
bool RightDowncheck = false; //�������� ������ �ڽ��� ������ ������
bool UpDowncheck = false; //�������� ������ �ڽ��� ������ ������
bool DownDowncheck = false; //�������� ������ �ڽ��� ������ ������
bool StarShineCheck = false;
bool MenuStateCheck = false;
void ChangeColor(int index);


/* �浹 ó�� */


/* �� �ε� */

char* ReplaceAll(char *s, const char *olds, const char *news);
void LoadMap(int Stage);

bool start = false;

/* �� �ε� */

/* ���� */
GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��
GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //��ü�� �ֵ� ����
GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //��ü�� ���� ��� �� ��
GLfloat lightPos[] = { 0.0f, 1000.0f, 0.0f, 1.0f }; //������ġ
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* ���� */



/* ��Ÿ ��� */

void Camera_init(); //ī�޶� �ʱ� ��ǥ
void Drawcody(); //�޹�� ������ �׷��ִ� �Լ�

void DrawVanbgm(int texture_number); //�ݽð���� ���ȭ��
void Drawbgm(int texture_number); //�ð���� ���ȭ��

void DrawBottom(int texture_number);


void DrawVanQuad(int texture_number); // ���带 �׸�
void DrawCube(int texture_number); //ť�긦 �׸�
void DrawMenu(int texture_number); //���� �޴��� �׸�


/* ��Ÿ ��� */


/* ĳ���� �̵�*/

void pongpong();
int hero_ycount = 0; //����� ����


bool Left_button = false;
bool Right_button = false;
bool Up_button = false;
bool Down_button = false;

bool LeftMovecheck = false; //�ڽ� �̵��ϰ� �ִ� ��������?
bool RightMovecheck = false; //�ڽ� �̵��ϰ� �ִ� ��������?
bool UpMovecheck = false; //�ڽ� �̵��ϰ� �ִ� ��������?
bool DownMovecheck = false; //�ڽ� �̵��ϰ� �ִ� ��������?


bool Camera_move = false;
bool Camera_ok = false;


void LeftMoveCamera(); //ī�޶� y�� �������� ȸ�� 
void RightMoveCamera(); //ī�޶� y�� ���������� ȸ��



void Movestart();
bool Movecheck = false;


/* ĳ���� �̵�*/

/* ���� */


FMOD_SYSTEM *g_System;      // �ý��� ������ ����
FMOD_SOUND *g_Sound[SOUND_END];     // ���� ������ ����
FMOD_CHANNEL *g_Channel[SOUND_END]; // ä��   ������ ����



void Soundinit();

/* ����*/