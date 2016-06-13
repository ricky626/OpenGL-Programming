#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

void LoadTexture(const char* filename, int count);
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

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

Object box = { 0, };

Object torus = { 0, };

Object snow = { 0, };
float moveZ = 1;
bool check = true;

Object hamuk = { 0, };

GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //��ü�� �����ϰ� ��Ÿ���� ��

GLfloat diffuseLight[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //��ü�� �ֵ� ����

GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��ü�� ���� ��� �� ��

GLfloat lightPos[] = { 0.0f, 500.0f, 0.0f, 1.0f }; //������ġ
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�
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


		glPushMatrix(); //���ư��� ť�� ������

			glTranslated(-130, 20, -100);
			glRotated(120, 0, 1.5, 1);
			glRotated(box.yRot, 1, 0, 0);

			glBlendFunc(GL_ONE, GL_ZERO);
			glColor3f(0, 0, 1);

			glutSolidCube(20);

		glPopMatrix();

		glPushMatrix(); //���ư��� ť�� ����

			glTranslated(-130, 30, -100);

			glRotated(120, 0, 1.5, 1);
			glRotated(box.yRot, 1, 0, 1);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(1, 1, 0, 0.5);
					glutSolidCube(60);

		glPopMatrix();

		glPushMatrix(); //������ �䷯��

			glBlendFunc(GL_ONE, GL_ZERO);

			glColor3f(1, 1, 1);

			glTranslated(100, 130, -150);

			glutSolidTorus(5, 100, 30, 30);
			
		glPopMatrix();

		glPushMatrix(); //������ �����

			glColor3f(1, 1, 1);

			glTranslated(100, 130, -150);
			glRotated(torus.zTran, 0, 0, 1);

			glScaled(0.5f, 9.0f, 0.5f);
			glutSolidCube(30);

		glPopMatrix();

		glPushMatrix(); //������ �����

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



			glPushMatrix(); //������

			

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

			glPushMatrix(); //������

				glTranslated(100, 130, -150);

				glColor3f(0, 1, 0);
				glutSolidCube(25);

			glPopMatrix();
			////////////////////////////////////////////////////



			////////////////////////���� �ظ�
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


			/////////////////////������ �ظ�
	
			

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
				glPushMatrix(); //�����

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
				glPushMatrix(); //�����

					glTranslated(snow.xTran, 150, 100);

					glRotated(-hamuk.zRot, 0, 0, 1);
					glTranslated(0, -75, 0);

					glColor3f(1, 1, 0);

					glutSolidSphere(20, 20, 20);

					glTranslated(0, 25, 0);

					glutSolidSphere(10, 20, 20);


				glPopMatrix();
			}
			



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

	glEnable(GL_LIGHTING); // ���� ����Ѵ�.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0); // 0������ ����Ѵ�.

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
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó ��� ����

	glBindTexture(GL_TEXTURE_2D, textures[count]); //�ؽ�ó�� ��ü�� �����Ѵ�.
	pBytes = LoadDIBitmap(filename, &info); //�̹��� �ε��� �Ѵ�.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //�ؽ�ó ���� ���Ǹ� �Ѵ�.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //�ؽ�ó �Ķ���� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //�ؽ�ó �Ķ���� ����

	//	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó ��� ����
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
