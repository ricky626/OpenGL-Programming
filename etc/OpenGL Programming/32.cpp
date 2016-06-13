#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>


GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

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
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	glutMainLoop();

}

Object Screen = { 0, };

GLuint textures[6];

// ������ ��� �Լ�
void DrawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();//ī�޶�

		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot + 30, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);
		
		glPushMatrix();
		
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glBegin(GL_QUADS);
		{
			//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			//�ո�
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
			//�޸�
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
			//����
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
			//�Ʒ���
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
			//�޸�
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
			//������
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

	glPopMatrix();//ī�޶�

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳�� // �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glGenTextures(6, textures); // n���� �̹��� �ؽ�ó ������ �Ѵ�

	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]); //�ؽ�ó�� ��ü�� �����Ѵ�.
		pBytes = LoadDIBitmap("res/blue.bmp", &info); //�̹��� �ε��� �Ѵ�.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //�ؽ�ó ���� ���Ǹ� �Ѵ�.

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //�ؽ�ó �Ķ���� ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //�ؽ�ó �Ķ���� ����

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE); // �ؽ�ó ��� ����
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
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}