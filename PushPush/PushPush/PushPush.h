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


enum MapState//mapcheck 관련
{
	NONE = 0,      // 아무것도 없는 빈 상태

	BOX_1 = 1,      // 1층 박스
	BOX_2 = 2,      // 2층 박스
	BOX_3 = 3,      // 3층 박스

	INPUSH_BOX = 4,   //푸시 박스
	END_POS = 5,   //목적지
	START = 6,      //캐릭터

	MUK = 7, //묵
	GEE = 8, //찌
	BAR = 9, //빠

	END_MUK = 10, //목적지 묵
	END_GEE = 11, //목적지 찌
	END_BAR = 12, //목적지 빠

};

enum Crash//충돌상황
{
	NO_CRASH = 0, //충돌안함 이동가능
	NO_PUSH = 1, //1~3층블럭이랑 충돌하지만 블록이 밀리지는 않음
	PUSH_OK = 2, //밀수 있는 블록과 충돌하여 밀기 가능
};


enum Image//텍스쳐 이름
{
	BMP_FLOOR = 0, // 비트맵 박스
	BMP_MUK = 1, // 비트맵 묵
	BMP_GEE = 2, //비트맵 찌
	BMP_BAR = 3, //비트맵 빠
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

enum VERSUS //가위바위보
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

#define Width 15 //가로 박스 오브젝트 최대 개수
#define Height 15 //세로 박스 오브젝트 최대 개수
#define BoxSize 50 //박스 크기
#define Boxinitpos 350 //좌측상단 기준점을 잡아준다


Object box[Height][Width] = { 0, }; //전체 오브젝트들의 좌표 (목적지, 캐릭터 제외)
int mapcheck[Height][Width] = { 0, }; //전체 오브젝트들의 인덱스

Object hero = { 0, };  //캐릭터 좌표



Object torus = { 0, }; //관람차 좌표
Object Screen = { 0, }; //카메라 좌표

int Stage_number = 1; //현재 스테이지 번호
int hat_stateCount = 0; // 캐릭터 모자애니메이션 체크 변수
int win_count = 0; //목적지에 골인하여 이긴 횟수
int draw_count = 0; //목적지에 골인하여 비긴 횟수
int lose_count = 0; //목적지에 골인하여 진 횟수

int max_endcount = 0; //총 목적지의 개수


float end_r[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //총 목적지의 개수
float end_g[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //총 목적지의 개수
float end_b[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //총 목적지의 개수

Object end_box[10] = { 0, }; //목적지들의 좌표

Object Snow[30][30] = { 0, 0, 0, 0, 0, 0 };

float moveY[30][30] = { 0, };



/* 콜백함수 */

void DrawScene();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
void SpecialKeyboardDown(int key, int x, int y);
void SpecialKeyboardUp(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void TimerFunctionFromBoard(int value);

/* 콜백함수 */


/* 텍스쳐 매핑 */

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
void LoadTexture(const char* filename, unsigned int sizeX, unsigned int sizeY, int count);
GLubyte *pBytes; // 데이터를 가리킬 포인터

BITMAPINFO *info; // 비트맵 헤더 저장핛 변수
GLuint textures[BMP_END];

/* 텍스쳐 매핑 */


/* 충돌 처리 */

bool collision(Object Circle, Object Rect);
int Leftcollision(Object Circle, Object(*Rect)[Width]);
int Rightcollision(Object Circle, Object(*Rect)[Width]);
int Upcollision(Object Circle, Object(*Rect)[Width]);
int Downcollision(Object Circle, Object(*Rect)[Width]);

void swap(int* a, int* b); // 정수 두개를 스왑
void Whowin(int in, int end, int index); //가위바위보 승패를 결정
void MoveBox(char str[]); //박스를 이동시킨다
void DownBox(int saveX, int saveZ);

int left_saveX = -1, left_saveZ = -1; // 부딪힌 박스의 인덱스 넘버를 기억하는 변수
int right_saveX = -1, right_saveZ = -1;
int up_saveX = -1, up_saveZ = -1;
int down_saveX = -1, down_saveZ = -1;

int left_dsaveX = -1, left_dsaveZ = -1; // 부딪힌 박스의 인덱스 넘버를 기억하는 변수
int right_dsaveX = -1, right_dsaveZ = -1;
int up_dsaveX = -1, up_dsaveZ = -1;
int down_dsaveX = -1, down_dsaveZ = -1;

bool LeftDowncheck = false; //목적지에 도달한 박스를 밑으로 내린다
bool RightDowncheck = false; //목적지에 도달한 박스를 밑으로 내린다
bool UpDowncheck = false; //목적지에 도달한 박스를 밑으로 내린다
bool DownDowncheck = false; //목적지에 도달한 박스를 밑으로 내린다
bool StarShineCheck = false;
bool MenuStateCheck = false;
void ChangeColor(int index);


/* 충돌 처리 */


/* 맵 로딩 */

char* ReplaceAll(char *s, const char *olds, const char *news);
void LoadMap(int Stage);

bool start = false;

/* 맵 로딩 */

/* 조명 */
GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //물체가 은은하게 나타내는 색
GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //물체의 주된 색상
GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //물체의 면이 띄게 될 색
GLfloat lightPos[] = { 0.0f, 1000.0f, 0.0f, 1.0f }; //조명위치
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* 조명 */



/* 기타 등등 */

void Camera_init(); //카메라 초기 좌표
void Drawcody(); //뒷배경 관람차 그려주는 함수

void DrawVanbgm(int texture_number); //반시계방향 배경화면
void Drawbgm(int texture_number); //시계방향 배경화면

void DrawBottom(int texture_number);


void DrawVanQuad(int texture_number); // 쿼드를 그림
void DrawCube(int texture_number); //큐브를 그림
void DrawMenu(int texture_number); //메인 메뉴를 그림


/* 기타 등등 */


/* 캐릭터 이동*/

void pongpong();
int hero_ycount = 0; //히어로 점프


bool Left_button = false;
bool Right_button = false;
bool Up_button = false;
bool Down_button = false;

bool LeftMovecheck = false; //박스 이동하고 있는 상태인지?
bool RightMovecheck = false; //박스 이동하고 있는 상태인지?
bool UpMovecheck = false; //박스 이동하고 있는 상태인지?
bool DownMovecheck = false; //박스 이동하고 있는 상태인지?


bool Camera_move = false;
bool Camera_ok = false;


void LeftMoveCamera(); //카메라를 y축 왼쪽으로 회전 
void RightMoveCamera(); //카메라를 y축 오른쪽으로 회전



void Movestart();
bool Movecheck = false;


/* 캐릭터 이동*/

/* 사운드 */


FMOD_SYSTEM *g_System;      // 시스템 포인터 변수
FMOD_SOUND *g_Sound[SOUND_END];     // 사운드 포인터 변수
FMOD_CHANNEL *g_Channel[SOUND_END]; // 채널   포인터 변수



void Soundinit();

/* 사운드*/