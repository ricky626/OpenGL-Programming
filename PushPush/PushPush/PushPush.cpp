#include "PushPush.h"

/*mapcheck ������Ʈ �ѹ�*/
// 0 : ���
// 1 : 1��
// 2 : 2��
// 3 : 3��
// 4 : �о�ߵǴ°�
// 5 : ������
// 6 : ĳ����
// 7 : ��
// 8 : ��
// 9 : ��
// 10 : �ص� ��
// 11 : �ص� ��
// 12 : �ص� ��
/*mapcheck ������Ʈ �ѹ�*/

void init()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			Snow[i][j].xTran = rand() % 1000 - 500;
			Snow[i][j].yTran = rand() % 200 + 400;
			Snow[i][j].zTran = rand() % 800 - 400;

			moveY[i][j] = rand() % 5 + 1;
		}
	}

	Screen.xRot = 0;
	Screen.yRot = 0;
	Screen.zRot = 0;

	LoadMap(Stage_number);

}


void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(500, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Push Push"); // ������ ���� (������ �̸�)

	Soundinit();
	glutTimerFunc(300, TimerFunctionFromBoard, 1);

	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboardDown);
	glutSpecialUpFunc(SpecialKeyboardUp);

	glutDisplayFunc(DrawScene);

	glutMainLoop();
}

void Camera_init() //�ʱ� ī�޶� ��ġ�� ������ ��������
{
	glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

	glRotated(Screen.xRot, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);

}

void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (GAME_STATE == GAME_MENU)
	{
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);

		if (MenuStateCheck)
			glBindTexture(GL_TEXTURE_2D, textures[BMP_MENU1]);
		else
			glBindTexture(GL_TEXTURE_2D, textures[BMP_MENU2]);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex3f(-400, 400, 0);
		glTexCoord2d(0, 0);
		glVertex3f(-400, -400, 0);
		glTexCoord2d(1, 0);
		glVertex3f(400, -400, 0);
		glTexCoord2d(1, 1);
		glVertex3f(400, 400, -0);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	
	else if (GAME_STATE == GAME_MAIN)
	{
		glPushMatrix();//ī�޶�

		Camera_init();

		glPushMatrix();


		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslated(0, -25, 0);

		DrawBottom(BMP_BOTTOM);

		//for (int i = -(Height / 2); i < Height / 2; i++)   //���� Height X Width
		//{
		//	for (int j = -(Width / 2); j < Width / 2; j++)
		//	{
		//		glVertex3f(i * BoxSize,			  -BoxSize + (BoxSize / 2), j * BoxSize);
		//		glVertex3f(i * BoxSize,           -BoxSize + (BoxSize / 2), j * BoxSize + BoxSize);
		//		glVertex3f(i * BoxSize + BoxSize, -BoxSize + (BoxSize / 2), j * BoxSize + BoxSize);
		//		glVertex3f(i * BoxSize + BoxSize, -BoxSize + (BoxSize / 2), j * BoxSize);
		//	}
		//}


		glPopMatrix();

		glPushMatrix();	 //�޸�

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[BMP_BACKGROUND]);

		glColor3f(1, 1, 1);

		glTranslated(-375, 375, 0);

		glRotated(90, 0, 0, 1);
		Drawbgm(BMP_BACKGROUND);

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();


		glPushMatrix(); //�޸�

		glEnable(GL_TEXTURE_2D);

		/*if(StarShineCheck)
		glBindTexture(GL_TEXTURE_2D, textures[BMP_STAR2]);
		else
		glBindTexture(GL_TEXTURE_2D, textures[BMP_STAR1]);*/

		glColor3f(1, 1, 1);

		glTranslated(0, 375, -375);

		glRotated(90, 1, 0, 0);

		if (StarShineCheck){
			DrawVanbgm(BMP_STAR2);
		}
		else if (!StarShineCheck) {
			DrawVanbgm(BMP_STAR1);
		}


		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //������

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[BMP_BACKGROUND]);

		glColor3f(1, 1, 1);

		glTranslated(375, 375, 0);


		glRotated(90, 0, 0, 1);
		DrawVanbgm(BMP_BACKGROUND);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		glPushMatrix(); //�ո�

		glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures[BMP_BACKGROUND]);

		glColor3f(1, 1, 1);

		glTranslated(0, 375, 375);

		glRotated(90, 1, 0, 0);
		glRotated(270, 0, 1, 0);


		if (StarShineCheck){
			Drawbgm(BMP_STAR2);
		}
		else if (!StarShineCheck) {
			Drawbgm(BMP_STAR1);
		}

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();


		glPushMatrix(); //ĳ����

		glTranslated(hero.xTran, hero.yTran, hero.zTran);
		glRotated(hero.xRot, 1, 0, 0);
		glRotated(hero.yRot, 0, 1, 0);
		glRotated(hero.zRot, 0, 0, 1);



		glColor3ub(67, 218, 236);

		glutSolidSphere(20, 50, 50);

		glTranslated(0, 25, 0);

		glutSolidSphere(15, 50, 50);

		glPushMatrix();

		if (hat_stateCount > 0 && (Left_button && !Camera_move) || (Right_button && Camera_move))
		{
			glRotated(-200, 0, 0, 1);
			glRotated(-160, 1, 0, 0);
		}
		else if (hat_stateCount > 0 && (Left_button && Camera_move) || (Right_button && !Camera_move))
		{
			glRotated(200, 0, 0, 1);
			glRotated(180, 1, 0, 0);
		}

		else if (hat_stateCount > 0 && (Up_button && !Camera_move) || (Down_button && Camera_move))
		{
			glRotated(40, 1, 0, 0);

		}
		else if (hat_stateCount > 0 && (Up_button && Camera_move) || (Down_button && !Camera_move))
		{
			glTranslated(0, -7, 0);
			glRotated(-40, 1, 0, 0);

		}

		glColor3ub(255, 0, 0);
		glTranslated(0, 20, 0);
		glRotated(-90, 1, 0, 0);


		glutSolidCone(10, 20, 10, 10);

		glColor3ub(255, 255, 255);
		glTranslated(0, 0, 20);
		glutSolidSphere(2, 10, 10);
		glPopMatrix();



		glPopMatrix();



		glPushMatrix(); //������ �����

		for (int i = 0; i < max_endcount; i++)
		{
			glColor3f(end_r[i], end_g[i], end_b[i]);

			glLoadIdentity();
			Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

			glTranslated(end_box[i].xTran, end_box[i].yTran - 40, end_box[i].zTran);

			if (end_box[i].check == END_MUK)
			{
				DrawCube(BMP_END_MUK);
			}
			else if (end_box[i].check == END_GEE)
			{
				DrawCube(BMP_END_GEE);
			}
			else if (end_box[i].check == END_BAR)
			{
				DrawCube(BMP_END_BAR);
			}

		}

		glPopMatrix();


		glPushMatrix(); // ���� ��� 1��~3��

		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				if (mapcheck[i][j] == BOX_1) //1��
				{
					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);

					glColor3f(1, 1, 1);

					DrawCube(BMP_FLOOR); //1��

				}

				else if (mapcheck[i][j] == BOX_2) //2��
				{
					glColor3f(1, 1, 1);

					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);

					DrawCube(BMP_FLOOR); //1��

					glTranslated(0, 50, 0);

					DrawCube(BMP_FLOOR); //2��
				}

				else if (mapcheck[i][j] == BOX_3) //3��
				{
					glColor3f(1, 1, 1);

					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);

					DrawCube(BMP_FLOOR); //1��

					glTranslated(0, 50, 0);

					DrawCube(BMP_FLOOR); //2��

					glTranslated(0, 50, 0);

					DrawCube(BMP_FLOOR); //3��
				}

				else if (mapcheck[i][j] == MUK)
				{
					glColor3f(1, 1, 1);

					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);
					glRotated(box[i][j].xRot, 1, 0, 0);
					glRotated(box[i][j].yRot, 0, 1, 0);
					glRotated(box[i][j].zRot, 0, 0, 1);

					DrawCube(BMP_MUK);
				}
				else if (mapcheck[i][j] == GEE)
				{
					glColor3f(1, 1, 1);

					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);
					glRotated(box[i][j].xRot, 1, 0, 0);
					glRotated(box[i][j].yRot, 0, 1, 0);
					glRotated(box[i][j].zRot, 0, 0, 1);

					DrawCube(BMP_GEE);
				}
				else if (mapcheck[i][j] == BAR)
				{
					glColor3f(1, 1, 1);

					glLoadIdentity();
					Camera_init(); //�ʱ� ī�޶� ��ġ�� ������ ��������

					glTranslated(box[i][j].xTran, box[i][j].yTran, box[i][j].zTran);
					glRotated(box[i][j].xRot, 1, 0, 0);
					glRotated(box[i][j].yRot, 0, 1, 0);
					glRotated(box[i][j].zRot, 0, 0, 1);

					DrawCube(BMP_BAR);
				}
			}
		}
		glEnd();

		glPopMatrix();

		glPushMatrix(); //�������� �׷��ش�

		glTranslated(100, 200, 0);

		glScaled(0.3, 0.3, 0.3);
		Drawcody();

		glPopMatrix();



		//��
		glPushMatrix();

		glColor3f(1, 1, 1);


		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				glLoadIdentity();

				glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran);

				glRotated(Screen.xRot + 30, 1, 0, 0);
				glRotated(Screen.yRot, 0, 1, 0);
				glRotated(Screen.zRot, 0, 0, 1);

				glTranslatef(Snow[i][j].xTran, Snow[i][j].yTran, Snow[i][j].zTran);


				glutSolidCube(2);
			}
		}


		glPopMatrix();


		glPopMatrix();//ī�޶�
	}

	

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
	glEnable(GL_CULL_FACE);

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

	glGenTextures(BMP_END, textures);

	/* �ؽ�ó�� �ε�*/
	LoadTexture("res/Bitmap/Cube.bmp", 275, 183, BMP_FLOOR);
	LoadTexture("res/Bitmap/Rock.bmp", 297, 300, BMP_MUK);
	LoadTexture("res/Bitmap/Scissors.bmp", 298, 301, BMP_GEE);
	LoadTexture("res/Bitmap/Paper.bmp", 294, 294, BMP_BAR);

	LoadTexture("res/Bitmap/EndRock.bmp", 300, 300, BMP_END_MUK);
	LoadTexture("res/Bitmap/EndScissors.bmp", 300, 300, BMP_END_GEE);
	LoadTexture("res/Bitmap/EndPaper.bmp", 300, 300, BMP_END_BAR);

	LoadTexture("res/Bitmap/Tile.bmp", 225, 225, BMP_BOTTOM);
	LoadTexture("res/Bitmap/Background.bmp", 226, 223, BMP_BACKGROUND);

	LoadTexture("res/Bitmap/star1.bmp", 640, 200, BMP_STAR1);
	LoadTexture("res/Bitmap/star2.bmp", 640, 200, BMP_STAR2);

	LoadTexture("res/Bitmap/MenuNon.bmp", 840, 1124, BMP_MENU1);
	LoadTexture("res/Bitmap/MenuKey.bmp", 840, 1124, BMP_MENU2);


}

void SpecialKeyboardDown(int key, int x, int y)
{
	if (GAME_STATE == GAME_MAIN)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if (!Left_button)
			{
				Left_button = true;
			}
		}

		if (key == GLUT_KEY_RIGHT)
		{
			if (!Right_button)
			{
				Right_button = true;
			}

		}
		if (key == GLUT_KEY_UP)
		{
			if (!Up_button)
			{
				Up_button = true;
			}

		}
		if (key == GLUT_KEY_DOWN)
		{
			if (!Down_button)
			{
				Down_button = true;
			}
		}

		if (key == GLUT_KEY_F1) //ġƮŰ �� ����������
		{
			LoadMap(--Stage_number);
		}
		else if (key == GLUT_KEY_F2) //ġƮŰ �� ����������
		{
			LoadMap(++Stage_number);
		}
		glutPostRedisplay();
	}
	

	
}

void SpecialKeyboardUp(int key, int x, int y)
{
	if (GAME_STATE == GAME_MAIN)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if (Left_button)
			{
				Left_button = false;
			}

		}

		if (key == GLUT_KEY_RIGHT)
		{
			if (Right_button)
			{
				Right_button = false;
			}

		}
		if (key == GLUT_KEY_UP)
		{
			if (Up_button)
			{
				Up_button = false;
			}

		}
		if (key == GLUT_KEY_DOWN)
		{
			if (Down_button)
			{
				Down_button = false;
			}

		}
		glutPostRedisplay();
	}
}

void LeftMoveCamera() //ī�޶� y�� �������� ȸ�� 
{
	static int count = 0;

	if (count < 90)
	{
		count += 1;

		Screen.xRot -= 4;
		Screen.zRot -= 4;

		Screen.yRot -= 2;

	}
	else
	{
		count = 0;
		//Screen.xRot = -675;
		//Screen.zRot = -720;
		Camera_move = !Camera_move;
		Screen.xTran = ((int)((hero.xTran + 350) / 50) - 7) * BoxSize;
		Camera_ok = false;


	}

}

void RightMoveCamera() //ī�޶� y�� �������� ȸ�� 
{
	static int count = 0;

	if (count < 90)
	{
		count += 1;

		Screen.xRot += 4;
		Screen.zRot += 4;
		Screen.yRot += 2;
	}
	else
	{
		count = 0;

		//Screen.xRot = -315;
		//Screen.zRot = -360;
		Camera_move = !Camera_move;
		Screen.xTran = ((int)((hero.xTran + 350) / 50) - 7) * -BoxSize;
		Camera_ok = false;
	}
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0); //Esc ������ ����
	static int counting = 0;
	static int count = 0;

	if (GAME_STATE == GAME_MENU)
	{
		FMOD_Channel_Stop(g_Channel[SOUND_MENU]);
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_MAIN], 0, &g_Channel[SOUND_MAIN]);
		init();
		glutTimerFunc(10, TimerFunction, 1);
		GAME_STATE = GAME_MAIN;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_RESET], 0, &g_Channel[SOUND_RESET]);
	}
	else if (GAME_STATE == GAME_MAIN)
	{
		if (key == '1')	Screen.xRot -= 1; // ������ ī�޶� ȸ��
		if (key == '2') Screen.xRot += 1;
		if (key == '3') Screen.yRot -= 1;
		if (key == '4') Screen.yRot += 1;
		if (key == '5') Screen.zRot -= 1;
		if (key == '6') Screen.zRot += 1;
		else if (key == '9')
		{
			Screen.zTran -= 1;
		}

		else if (key == '0')
		{
			Screen.zTran += 1;
		}
		else if (key == 'q') LoadMap(--Stage_number);
		else if (key == 'w') LoadMap(++Stage_number);
		else if (key == 'e') Screen.yTran += 1;
		else if (key == 'r' || key == 'R')
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_RESET], 0, &g_Channel[SOUND_RESET]);
			LoadMap(Stage_number);
		}


		else if (key == 32) //�����̽� ��  Space Bar //ī�޶� �������� ȸ��
		{
			if (!Camera_ok)
			{
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_SCENECHANGE], 0, &g_Channel[SOUND_SCENECHANGE]);
				Camera_ok = true;
			}
		}


		else if (key == 'z')
		{
			system("cls");
			for (int i = 0; i < max_endcount; i++)
			{
				printf("%f %f %f\n", end_r[i], end_g[i], end_b[i]);
			}
		}

		else if (key == 'o')    //������
		{
			system("cls");
			printf("hero : %f %f %f \n", hero.xTran, hero.yTran, hero.zTran);
			printf("Screen Trans: x %f y %f z %f\n", Screen.xTran, Screen.yTran, Screen.zTran);
			printf("Screen Rot: x %f y %f z %f\n", Screen.xRot, Screen.yRot, Screen.zRot);
		}

		else if (key == 'p') //������
		{
			system("cls");
			printf("wincount : %d\n", win_count);
			printf("drawcount : %d\n", draw_count);
			printf("losecount : %d\n", lose_count);
			printf("max_endcount : %d\n", max_endcount);
		}

		else if (key == 'i') //������
		{
			system("cls");

			for (int i = 0; i < max_endcount; i++)
				printf("%d\n", end_box[i].check);
		}

		else if (key == 'c') //������
		{
			system("cls");

			for (int i = 0; i < Height; i++)
			{
				for (int j = 0; j < Width; j++)
				{
					if (mapcheck[i][j] == 1 || mapcheck[i][j] == 2 || mapcheck[i][j] == 3)
					{
						counting++;
					}
				}
			}
			printf("%d\n", counting);
			counting = 0;
		}
	}
	

	glutPostRedisplay();
}

void swap(int* a, int* b) //������ ���� �ΰ��� �ٲ��� ü����
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void ChangeColor(char str[], int index)
{
	if (str == "WIN")
	{
		end_r[index] = 0;
		end_g[index] = 1;
		end_b[index] = 1;
	}

	else if (str == "DRAW")
	{
		end_r[index] = 1;
		end_g[index] = 1;
		end_b[index] = 0;
	}

	else if (str == "LOSE")
	{
		end_r[index] = 1;
		end_g[index] = 0;
		end_b[index] = 0;
	}
}

void Whowin(int in, int end, int index) //���������� ���и� ����
{
	if (in == MUK)
	{
		if (end == GEE)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_WIN], 0, &g_Channel[SOUND_WIN]);
			win_count++;
			ChangeColor("WIN", index);
		}
		else if (end == MUK)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_DRAW], 0, &g_Channel[SOUND_DRAW]);
			draw_count++;
			ChangeColor("DRAW", index);

		}
		else if (end == BAR)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_LOSE], 0, &g_Channel[SOUND_LOSE]);
			lose_count++;
			ChangeColor("LOSE", index);

		}
	}
	else if (in == GEE)
	{
		if (end == BAR)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_WIN], 0, &g_Channel[SOUND_WIN]);
			win_count++;
			ChangeColor("WIN", index);
		}
		else if (end == GEE)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_DRAW], 0, &g_Channel[SOUND_DRAW]);
			draw_count++;
			ChangeColor("DRAW", index);
		}
		else if (end == MUK)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_LOSE], 0, &g_Channel[SOUND_LOSE]);
			lose_count++;
			ChangeColor("LOSE", index);
		}
	}
	else if (in == BAR)
	{
		if (end == MUK)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_WIN], 0, &g_Channel[SOUND_WIN]);
			win_count++;
			ChangeColor("WIN", index);
		}
		else if (end == BAR)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_DRAW], 0, &g_Channel[SOUND_DRAW]);
			draw_count++;
			ChangeColor("DRAW", index);
		}
		else if (end == GEE)
		{
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_LOSE], 0, &g_Channel[SOUND_LOSE]);
			lose_count++;
			ChangeColor("LOSE", index);
		}
	}
	if ((win_count + draw_count + lose_count) == max_endcount)
	{
		LoadMap(++Stage_number);
	}
}

void DownBox(int saveZ, int saveX)
{
	static int count = 0;

	if (count < 50)
	{
		count += 2;
		box[saveZ][saveX].yTran -= 2;
	}

	else
	{
		count = 0;

		mapcheck[saveZ][saveX] = INPUSH_BOX;

		left_dsaveZ = left_dsaveX = -1;
		right_dsaveZ = right_dsaveX = -1;
		up_dsaveZ = up_dsaveX = -1;
		down_dsaveZ = down_dsaveX = -1;

		LeftDowncheck = false;
		RightDowncheck = false;
		UpDowncheck = false;
		DownDowncheck = false;
	}

}

void MoveBox(char str[]) //�ڽ��� �̵������ִ� �Լ�
{
	static int Leftcount = 0; //��� ȣ��Ǿ�� �ϱ� ������ ������ �������� ������
	static int Rightcount = 0;
	static int Upcount = 0;
	static int Downcount = 0;

	if (str == "LEFT")
	{
		if (Leftcount < BoxSize) //�ڽ��� 50��ŭ õõ�� �̵� (ť�� ũ�⸸ŭ �̵���Ű��)
		{
			Leftcount += 2; //ī��Ʈ�� ���� �ڽ��� ��ŭ �̵��ߴ����� �Ǵ�
			box[left_saveZ][left_saveX].xTran -= 2; // �ڽ��� õõ�� �̵���Ų��
			box[left_saveZ][left_saveX].zRot += 3.6f; //�ڽ��� �������ְ� ȸ����Ų��
		}
		else
		{
			box[left_saveZ][left_saveX].xTran += BoxSize; //�ؿ� �ڽ��� ���°��� �ٲ��ִ°��� ��¥ �ٲٴ°�


			if (mapcheck[left_saveZ][left_saveX] == BAR) //������ Ŀ����
				mapcheck[left_saveZ][left_saveX] = MUK; //������ �ٽ� �ǵ�����
			else
				mapcheck[left_saveZ][left_saveX]++; // ��->��->��


			for (int i = 0; i < max_endcount; i++) //���������� ���� ������ ���ش�
			{
				if (end_box[i].xTran == box[left_saveZ][left_saveX - 1].xTran && end_box[i].zTran == box[left_saveZ][left_saveX - 1].zTran) //�������� Ǫ�� ����� ����
				{
					Whowin(mapcheck[left_saveZ][left_saveX], end_box[i].check - 3, i);
					left_dsaveZ = left_saveZ;
					left_dsaveX = left_saveX;
					LeftDowncheck = true;
					break;
				}
			}

			swap(&mapcheck[left_saveZ][left_saveX], &mapcheck[left_saveZ][left_saveX - 1]); //�ڽ��� ���°��� �ٲ��ش� (����� ���� ť����ġ�� ���°��� ��������)
			
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_SWAP], 0, &g_Channel[SOUND_SWAP]);
			box[left_saveZ][left_saveX].zRot = 0; //�ڽ� ȸ���ߴ� �� �ʱ�ȭ
			Leftcount = 0; //ī��Ʈ �ʱ�ȭ
			left_saveZ = left_saveX = -1; //�ε����� �����ߴ� ���� �ʱ�ȭ
			LeftMovecheck = false;

			
			
		}

	}

	else if (str == "RIGHT")
	{
		if (Rightcount < BoxSize)
		{
			Rightcount += 2; //ī��Ʈ�� ���� �ڽ��� ��ŭ �̵��ߴ����� �Ǵ�
			box[right_saveZ][right_saveX].xTran += 2; // �ڽ��� õõ�� �̵���Ų��
			box[right_saveZ][right_saveX].zRot -= 3.6f; //�ڽ��� ������ �ְ� ȸ����Ų��
		}
		else
		{
			box[right_saveZ][right_saveX].xTran -= BoxSize; //�ؿ� �ڽ��� ���°��� �ٲ��ִ°��� ��¥ �ٲٴ°�

			if (mapcheck[right_saveZ][right_saveX] == BAR) //������ Ŀ����
				mapcheck[right_saveZ][right_saveX] = MUK; //������ �ٽ� �ǵ�����
			else
				mapcheck[right_saveZ][right_saveX]++; // ��->��->��


			for (int i = 0; i < max_endcount; i++) //���������� ���� ������ ���ش�
			{
				if (end_box[i].xTran == box[right_saveZ][right_saveX + 1].xTran && end_box[i].zTran == box[right_saveZ][right_saveX + 1].zTran) //�������� Ǫ�� ����� ����
				{
					Whowin(mapcheck[right_saveZ][right_saveX], end_box[i].check - 3, i);

					right_dsaveZ = right_saveZ;
					right_dsaveX = right_saveX;
					RightDowncheck = true;
					break;
				}
			}

			swap(&mapcheck[right_saveZ][right_saveX], &mapcheck[right_saveZ][right_saveX + 1]); //�ڽ��� ���°��� �ٲ��ش� (����� ���� ť����ġ�� ���°��� ��������)
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_SWAP], 0, &g_Channel[SOUND_SWAP]);
			box[right_saveZ][right_saveX].zRot = 0; //�ڽ� ȸ���ߴ� �� �ʱ�ȭ
			Rightcount = 0; // ī��Ʈ �ʱ�ȭ
			right_saveZ = right_saveX = -1; //�ε����� �����ߴ� ���� �ʱ�ȭ
			RightMovecheck = false;




		}

	}

	else if (str == "UP")
	{
		if (Upcount < BoxSize)
		{
			Upcount += 2; //ī��Ʈ�� ���� �ڽ��� ��ŭ �̵��ߴ����� �Ǵ�
			box[up_saveZ][up_saveX].zTran -= 2; // �ڽ��� õõ�� �̵���Ų��
			box[up_saveZ][up_saveX].xRot -= 3.6f; //�ڽ��� �������ְ� ȸ����Ų��
		}
		else
		{
			box[up_saveZ][up_saveX].zTran += BoxSize; //�ؿ� �ڽ��� ���°��� �ٲ��ִ°��� ��¥ �ٲٴ°�

			if (mapcheck[up_saveZ][up_saveX] == BAR) //������ Ŀ����
				mapcheck[up_saveZ][up_saveX] = MUK; //������ �ٽ� �ǵ�����
			else
				mapcheck[up_saveZ][up_saveX]++; // ��->��->��

			for (int i = 0; i < max_endcount; i++) //���������� ���� ������ ���ش�
			{
				if (end_box[i].xTran == box[up_saveZ - 1][up_saveX].xTran && end_box[i].zTran == box[up_saveZ - 1][up_saveX].zTran) //�������� Ǫ�� ����� ����
				{
					Whowin(mapcheck[up_saveZ][up_saveX], end_box[i].check - 3, i);
					up_dsaveZ = up_saveZ;
					up_dsaveX = up_saveX;
					UpDowncheck = true;
					break;
				}
			}

			swap(&mapcheck[up_saveZ][up_saveX], &mapcheck[up_saveZ - 1][up_saveX]); //�ڽ��� ���°��� �ٲ��ش� (����� ���� ť����ġ�� ���°��� ��������)
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_SWAP], 0, &g_Channel[SOUND_SWAP]);
			box[up_saveZ][up_saveX].xRot = 0; //�ڽ� ȸ���ߴ� �� �ʱ�ȭ
			Upcount = 0; // ī��Ʈ �ʱ�ȭ
			up_saveZ = up_saveX = -1; //�ε����� �����ߴ� ���� �ʱ�ȭ
			UpMovecheck = false;



		}

	}

	else if (str == "DOWN")
	{
		if (Downcount < BoxSize)
		{
			Downcount += 2; //ī��Ʈ�� ���� �ڽ��� ��ŭ �̵��ߴ����� �Ǵ�
			box[down_saveZ][down_saveX].zTran += 2; // �ڽ��� õõ�� �̵���Ų��
			box[down_saveZ][down_saveX].xRot += 3.6f; //�ڽ��� �������ְ� ȸ����Ų��
		}
		else
		{
			box[down_saveZ][down_saveX].zTran -= BoxSize; //�ؿ� �ڽ��� ���°��� �ٲ��ִ°��� ��¥ �ٲٴ°�

			if (mapcheck[down_saveZ][down_saveX] == BAR) //������ Ŀ����
				mapcheck[down_saveZ][down_saveX] = MUK; //������ �ٽ� �ǵ�����
			else
				mapcheck[down_saveZ][down_saveX]++; // ��->��->��

			for (int i = 0; i < max_endcount; i++) //���������� ���� ������ ���ش�
			{
				if (end_box[i].xTran == box[down_saveZ + 1][down_saveX].xTran && end_box[i].zTran == box[down_saveZ + 1][down_saveX].zTran) //�������� Ǫ�� ����� ����
				{
					Whowin(mapcheck[down_saveZ][down_saveX], end_box[i].check - 3, i);
					down_dsaveZ = down_saveZ;
					down_dsaveX = down_saveX;
					DownDowncheck = true;
					break;
				}
			}

			swap(&mapcheck[down_saveZ][down_saveX], &mapcheck[down_saveZ + 1][down_saveX]); //�ڽ��� ���°��� �ٲ��ش� (����� ���� ť����ġ�� ���°��� ��������)
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_SWAP], 0, &g_Channel[SOUND_SWAP]);
			box[down_saveZ][down_saveX].xRot = 0; //�ڽ� ȸ���ߴ� �� �ʱ�ȭ
			Downcount = 0; // ī��Ʈ �ʱ�ȭ
			down_saveZ = down_saveX = -1; //�ε����� �����ߴ� ���� �ʱ�ȭ
			DownMovecheck = false;



		}

	}

}


void pongpong() //ĳ���� ����Ƣ�� �̵�
{
	if (hero_ycount < 15)
	{
		hero.yTran += 1;
		hero_ycount++;
		++hat_stateCount;
	}
	else
	{
		hero.yTran = 0;
		hero_ycount = 0;
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_REUSE, g_Sound[SOUND_WALK], 0, &g_Channel[SOUND_WALK]);
	}
}

void Moverot()
{
	static int count = 0;
	if (count < 45)
	{
		count += 1;

		Screen.yTran += 5.0;
		Screen.xRot += 1;
	}
	else
	{
		count = 0;
		start = true;
		Movecheck = false;
	}
}

void Movestart()
{
	static int count = 0;

	if (count < 50 && Movecheck == false)
	{
		count += 1;
		Screen.zTran += 10;

	}
	else
	{
		Movecheck = true;
		count = 0;
		Moverot();
	}
}

void TimerFunctionFromBoard(int value) //Ÿ�̸�
{
	if (GAME_STATE == GAME_MAIN)
		StarShineCheck = !StarShineCheck;
	else if (GAME_STATE == GAME_MENU)
		MenuStateCheck = !MenuStateCheck;
	glutTimerFunc(300, TimerFunctionFromBoard, 1);
}

void TimerFunction(int value) //Ÿ�̸�
{
	if (value == 1)
	{
		if (start == false)
		{
			Movestart();
		}

		if (Camera_ok)
		{
			if (!Camera_move)
				LeftMoveCamera();
			else
				RightMoveCamera();
		}

		if (LeftDowncheck)
		{
			DownBox(left_dsaveZ, left_dsaveX - 1); //���� �ڽ��� ������ �̵�
		}

		else if (RightDowncheck)
		{
			DownBox(right_dsaveZ, right_dsaveX + 1); //������ �ڽ��� ������ �̵�
		}

		else if (UpDowncheck)
		{
			DownBox(up_dsaveZ - 1, up_dsaveX); //���� �ڽ��� ������ �̵�
		}

		else if (DownDowncheck)
		{
			DownBox(down_dsaveZ + 1, down_dsaveX); //�Ʒ��� �ڽ��� ������ �̵�
		}


		if (LeftMovecheck)
		{
			MoveBox("LEFT"); //�������� �ڽ��� �̵�
		}

		else if (RightMovecheck)
		{
			MoveBox("RIGHT"); //���������� �ڽ��� �̵�
		}

		else if (UpMovecheck)
		{
			MoveBox("UP"); //�������� �ڽ��� �̵�
		}

		else if (DownMovecheck)
		{
			MoveBox("DOWN"); //�Ʒ������� �ڽ��� �̵�
		}



		if (Left_button) //���� Ű���� ����Ű
		{
			if (!Camera_move)
			{
				if (Rightcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.xTran -= 2;

					pongpong(); //ĳ���� ����Ƣ�� �̵�

					Screen.xTran += 2;
				}

				if (Rightcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.xTran += 2;
					Screen.xTran -= 2;
				}

				else if (Rightcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[left_saveZ][left_saveX - 1] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						LeftMovecheck = true;
					}
				}
			}
			else
			{
				if (Leftcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.xTran += 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
					Screen.xTran += 2;
				}

				if (Leftcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.xTran -= 2;
					Screen.xTran -= 2;
				}


				else if (Leftcollision(hero, box) == PUSH_OK) //Ǫ�� ����̶� �浹��
				{
					if (mapcheck[right_saveZ][right_saveX + 1] == NONE && mapcheck[right_saveZ][right_saveX + 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						RightMovecheck = true;
					}
				}
			}

		}


		if (Right_button) //������ Ű���� ����Ű
		{
			if (!Camera_move)
			{
				if (Leftcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.xTran += 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
					Screen.xTran -= 2;
				}

				if (Leftcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.xTran -= 2;
					Screen.xTran += 2;
				}


				else if (Leftcollision(hero, box) == PUSH_OK) //Ǫ�� ����̶� �浹��
				{
					if (mapcheck[right_saveZ][right_saveX + 1] == NONE && mapcheck[right_saveZ][right_saveX + 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						RightMovecheck = true;
					}
				}
			}
			else
			{
				if (Rightcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.xTran -= 2;

					pongpong(); //ĳ���� ����Ƣ�� �̵�

					Screen.xTran -= 2;
				}

				if (Rightcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.xTran += 2;
					Screen.xTran += 2;
				}

				else if (Rightcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[left_saveZ][left_saveX - 1] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						LeftMovecheck = true;
					}
				}
			}

		}


		if (Up_button) //���� Ű���� ����Ű
		{
			if (!Camera_move)
			{
				if (Downcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.zTran -= 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
				}

				if (Downcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.zTran += 2;
				}

				else if (Downcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[up_saveZ - 1][up_saveX] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						UpMovecheck = true;
					}
				}
			}
			else
			{
				if (Upcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.zTran += 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
				}

				if (Upcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.zTran -= 2;
				}

				else if (Upcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[down_saveZ + 1][down_saveX] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						DownMovecheck = true;
					}
				}
			}

		}


		if (Down_button) //�Ʒ��� Ű���� ����Ű
		{
			if (!Camera_move)
			{
				if (Upcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.zTran += 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
				}

				if (Upcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.zTran -= 2;
				}

				else if (Upcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[down_saveZ + 1][down_saveX] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						DownMovecheck = true;
					}
				}
			}
			else
			{
				if (Downcollision(hero, box) == NO_CRASH) //�浹�� ��ü�� ������ ��Ȱ�ϰ� �̵�
				{
					hero.zTran -= 2;
					pongpong(); //ĳ���� ����Ƣ�� �̵�
				}

				if (Downcollision(hero, box) == NO_PUSH) //����̶� �浹�� �ϸ� �̵��ѰŸ��� �ǵ����� �ڷ� �з�����
				{
					hero.zTran += 2;
				}

				else if (Downcollision(hero, box) == PUSH_OK) // Ǫ�� ����̶� �浹��
				{
					if (mapcheck[up_saveZ - 1][up_saveX] == NONE && mapcheck[left_saveZ][left_saveX - 1] != INPUSH_BOX) // Ǫ���ϱ��� ���� ��Ͽ� �ƹ��͵� ������ �̵���Ų��
					{
						UpMovecheck = true;
					}
				}
			}

		}


		if (!Left_button && !Right_button && !Up_button && !Down_button)
		{
			hero.yTran = 0;
			hero_ycount = 0;
			hat_stateCount = 0;
		}



		torus.zTran -= 1; //������ ȸ��
		torus.yTran += 1; //������ ȸ��


		for (int i = 0; i < 30; i++) //�� ������
		{
			for (int j = 0; j < 30; j++)
			{
				if (Snow[i][j].yTran > -200)
					Snow[i][j].yTran -= moveY[i][j];
				else
				{
					Snow[i][j].xTran = rand() % 1000 - 500;
					Snow[i][j].yTran = rand() % 200 + 400;
					Snow[i][j].zTran = rand() % 800 - 400;
				}
			}
		}


		glutTimerFunc(10, TimerFunction, 1);
		//printf("%d %d\n", (int)(hero.zTran + 350) / 50, (int)(hero.xTran + 350) / 50); //ĳ���Ͱ� ��� ��ġ�� �ε����� �ִ����� �ֿܼ� ������� // ������


	}



	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		system("cls");

		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				printf("%d ", mapcheck[i][j]); //���콺�� Ŭ���Ͽ� �ܼ�â�� ���� ���� ���¸� ������� (������)
			}
			printf("\n");
		}
		printf("\n");
	}

	glutPostRedisplay();
}


char* ReplaceAll(char *s, const char *olds, const char *news) //���ڿ� ġȯ�Լ�
{
	char* result, *sr;
	int i, count = 0;
	int oldlen = strlen(olds); if (oldlen < 1) return s;
	int newlen = strlen(news);


	if (newlen != oldlen) {
		for (i = 0; s[i] != '\0';) {
			if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
			else i++;
		}
	}
	else i = strlen(s);


	result = (char *)malloc(i + 1 + count * (newlen - oldlen));
	if (result == NULL) return NULL;


	sr = result;
	while (*s) {
		if (memcmp(s, olds, oldlen) == 0) {
			memcpy(sr, news, newlen);
			sr += newlen;
			s += oldlen;
		}
		else *sr++ = *s++;
	}
	*sr = NULL;
	return result;

}


void LoadMap(int Stage) //MapTool �о���� �κ� Stage�� ���� �ε��Ҽ� �ִ�
{
	for (int i = 0; i < max_endcount; i++)
	{
		end_r[i] = end_g[i] = end_b[i] = 1;
		end_box[i].xTran = end_box[i].zTran = 0; //�� ������������ ����ߴ� ������ ��ǥ���� �ʱ�ȭ
	}


	win_count = 0;
	draw_count = 0;
	lose_count = 0;
	max_endcount = 0;

	char* name = "res/Stage/Stage-.txt";
	char* str;
	char buf[3];
	_itoa(Stage, buf, 10);

	str = ReplaceAll(name, "-", buf);

	FILE* fp = fopen(str, "r");

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			//��ϵ��� ���°� �о����
			fscanf(fp, "%02d ", &mapcheck[i][j]);

			//������Ʈ �ʱ���ǥ ���� // ��������� �������� ��ü���� �׷��ֱ����� ��ǥ���� ����
			box[i][j].xTran = j * BoxSize - Boxinitpos; //������� �������� ����� glTranslated(-350, 0, -350) old 225
			box[i][j].zTran = i * BoxSize - Boxinitpos; //������� �������� ����� glTranslated(-350, 0, -350)


			//ĳ���� �ʱ���ǥ ����
			if (mapcheck[i][j] == START)
			{
				hero.xTran = box[i][j].xTran; //������� �������� ����� glTranslated(-350, 0, -350)
				hero.zTran = box[i][j].zTran; //������� �������� ����� glTranslated(-350, 0, -350)
				mapcheck[i][j] = 0; //ĳ������ ��ġ������ ������ �����Ͽ����� ������ ��������� �����.
			}

			//������ �ʱ���ǥ ����

			else if (mapcheck[i][j] == END_MUK)  //�������̸�
			{
				end_box[max_endcount].xTran = box[i][j].xTran; //��ǥ ����
				end_box[max_endcount].zTran = box[i][j].zTran;

				end_box[max_endcount].check = END_MUK;
				mapcheck[i][j] = 0;

				max_endcount++;
			}

			else if (mapcheck[i][j] == END_GEE)  //�������̸�
			{
				end_box[max_endcount].xTran = box[i][j].xTran; //��ǥ ����
				end_box[max_endcount].zTran = box[i][j].zTran;

				end_box[max_endcount].check = END_GEE;
				mapcheck[i][j] = 0;

				max_endcount++;
			}

			else if (mapcheck[i][j] == END_BAR)  //�������̸�
			{
				end_box[max_endcount].xTran = box[i][j].xTran; //��ǥ ����
				end_box[max_endcount].zTran = box[i][j].zTran;

				end_box[max_endcount].check = END_BAR;
				mapcheck[i][j] = 0;

				max_endcount++;
			}
		}
	}
	fclose(fp);


	Screen.xTran = ((int)((hero.xTran + 350) / 50) - 7) * -BoxSize; //ĳ���Ͱ� ī�޶� x���� ��� ���� ������
	Screen.yTran = -225;
	Screen.zTran = -500;
	Screen.xRot = 0;
	Screen.yRot = 0;
	start = false;
	Camera_move = false;
	Movecheck = false;
}


bool collision(Object Circle, Object Rect) //���� �Ⱦ��� �Լ� //�ʿ��ұ�� �̸� ��������
{
	float Left = (Circle.xTran - 8);
	float Top = (Circle.zTran - 8);
	float Right = (Circle.xTran + 8);
	float Bottom = (Circle.zTran + 8);


	return false;
}


int Leftcollision(Object Circle, Object(*Rect)[Width]) //ť���� ���ʼ� �浹üũ
{
	float Left = (Circle.xTran - 8);
	float Top = (Circle.zTran - 8);
	float Right = (Circle.xTran + 8);
	float Bottom = (Circle.zTran + 8);

	float Left2;
	float Top2;
	float Right2;
	float Bottom2;


	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (mapcheck[i][j] == NONE) //0 ��� 4 ������ �浹üũ �ȵǰ���
				continue;
			Left2 = (Rect[i][j].xTran - BoxSize / 2);
			Top2 = (Rect[i][j].zTran - BoxSize / 2);
			Right2 = (Rect[i][j].xTran - BoxSize / 2);
			Bottom2 = (Rect[i][j].zTran + BoxSize / 2); // 0 ��� 1 �� 2 ĳ���� 3 �о�ߵ� 4 ������

			if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2) //�浹�ϸ�
			{
				if (mapcheck[i][j] == BOX_1 || mapcheck[i][j] == BOX_2 || mapcheck[i][j] == BOX_3) //ĳ���Ͷ� �浹�� ���� �м� ���� ����̸�
					return NO_PUSH;
				else if (mapcheck[i][j] == MUK || mapcheck[i][j] == GEE || mapcheck[i][j] == BAR) //ĳ���Ͷ� �浹�� ���� �м� �ִ� ����̸�
				{
					right_saveZ = i;
					right_saveX = j;
					return PUSH_OK;
				}
			}
		}
	}



	//�浹 ��������
	return NO_CRASH;
}

int Rightcollision(Object Circle, Object(*Rect)[Width]) //ť���� �����ʼ� �浹üũ
{
	float Left = (Circle.xTran - 8);
	float Top = (Circle.zTran - 8);
	float Right = (Circle.xTran + 8);
	float Bottom = (Circle.zTran + 8);

	float Left2;
	float Top2;
	float Right2;
	float Bottom2;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (mapcheck[i][j] == NONE) //0 ��� �浹üũ �ȵǰ���
				continue;
			Left2 = Rect[i][j].xTran + BoxSize / 2;
			Top2 = Rect[i][j].zTran - BoxSize / 2;
			Right2 = Rect[i][j].xTran + BoxSize / 2;
			Bottom2 = Rect[i][j].zTran + BoxSize / 2;

			if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2) //�浹�ϸ�
			{
				if (mapcheck[i][j] == BOX_1 || mapcheck[i][j] == BOX_2 || mapcheck[i][j] == BOX_3) //ĳ���Ͷ� �浹�� ���� �м� ���� ����̸�
				{
					return NO_PUSH;
				}

				else if (mapcheck[i][j] == MUK || mapcheck[i][j] == GEE || mapcheck[i][j] == BAR) //ĳ���Ͷ� �浹�� ���� �м� �ִ� ����̸�
				{
					left_saveZ = i;
					left_saveX = j;
					return PUSH_OK;
				}

			}

		}
	}

	//�浹 ��������
	return NO_CRASH;
}

int Upcollision(Object Circle, Object(*Rect)[Width]) //ť���� ���ʼ� �浹üũ
{
	float Left = (Circle.xTran - 8);
	float Top = (Circle.zTran - 8);
	float Right = (Circle.xTran + 8);
	float Bottom = (Circle.zTran + 8);


	float Left2;
	float Top2;
	float Right2;
	float Bottom2;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (mapcheck[i][j] == NONE) //0 ��� 4 ������ �浹üũ �ȵǰ���
				continue;

			Left2 = (Rect[i][j].xTran - BoxSize / 2);
			Top2 = (Rect[i][j].zTran - BoxSize / 2);
			Right2 = (Rect[i][j].xTran + BoxSize / 2);
			Bottom2 = (Rect[i][j].zTran - BoxSize / 2);

			if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2) //�浹�ϸ�
			{
				if (mapcheck[i][j] == BOX_1 || mapcheck[i][j] == BOX_2 || mapcheck[i][j] == BOX_3) //ĳ���Ͷ� �浹�� ���� �м� ���� ����̸�
					return NO_PUSH;
				else if (mapcheck[i][j] == MUK || mapcheck[i][j] == GEE || mapcheck[i][j] == BAR) //ĳ���Ͷ� �浹�� ���� �м� �ִ� ����̸�
				{
					down_saveZ = i;
					down_saveX = j;
					return PUSH_OK;
				}
			}

		}
	}
	//�浹��������
	return NO_CRASH;
}

int Downcollision(Object Circle, Object(*Rect)[Width]) //ť���� �Ʒ��� �浹üũ
{
	float Left = (Circle.xTran - 8);
	float Top = (Circle.zTran - 8);
	float Right = (Circle.xTran + 8);
	float Bottom = (Circle.zTran + 8);

	float Left2;
	float Top2;
	float Right2;
	float Bottom2;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (mapcheck[i][j] == NONE) //0 ��� 4 ������ �浹üũ �ȵǰ���
				continue;

			Left2 = (Rect[i][j].xTran - BoxSize / 2);
			Top2 = (Rect[i][j].zTran + BoxSize / 2);
			Right2 = (Rect[i][j].xTran + BoxSize / 2);
			Bottom2 = (Rect[i][j].zTran + BoxSize / 2);

			if (Left < Right2 && Right > Left2 && Top < Bottom2 && Bottom > Top2) //�浹�ϸ�
			{
				if (mapcheck[i][j] == BOX_1 || mapcheck[i][j] == BOX_2 || mapcheck[i][j] == BOX_3) //ĳ���Ͷ� �浹�� ���� �м� ���� ����̸�
					return NO_PUSH;
				else if (mapcheck[i][j] == MUK || mapcheck[i][j] == GEE || mapcheck[i][j] == BAR) //ĳ���Ͷ� �浹�� ���� �м� �ִ� ����̸�
				{
					up_saveZ = i;
					up_saveX = j;
					return PUSH_OK;
				}
			}

		}
	}

	//�浹��������
	return NO_CRASH;
}

void LoadTexture(const char* filename, unsigned int sizeX, unsigned int sizeY, int count)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó ��� ����

	glBindTexture(GL_TEXTURE_2D, textures[count]); //�ؽ�ó�� ��ü�� �����Ѵ�.
	pBytes = LoadDIBitmap(filename, &info); //�̹��� �ε��� �Ѵ�.
	glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes); //�ؽ�ó ���� ���Ǹ� �Ѵ�.

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



void DrawCube(int texture_number)
{
	// ����
	glPushMatrix();
	glTranslated(0, 25, 0);
	DrawVanQuad(texture_number);
	glPopMatrix();

	// �Ʒ���
	glPushMatrix();
	glTranslated(0, -25, 0);
	DrawVanQuad(texture_number);
	glPopMatrix();

	// ���ʸ�
	glPushMatrix();
	glTranslated(-25, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawVanQuad(texture_number);
	glPopMatrix();

	// �����ʸ�
	glPushMatrix();
	glTranslated(+25, 0, 0);
	glRotated(-90, 0, 0, 1);
	DrawVanQuad(texture_number);
	glPopMatrix();

	// �ո�
	glPushMatrix();
	glTranslated(0, 0, +25);
	glRotated(-270, 1, 0, 0);
	DrawVanQuad(texture_number);
	glPopMatrix();

	// �޸�
	glPushMatrix();
	glTranslated(0, 0, -25);
	glRotated(+270, 1, 0, 0);
	DrawVanQuad(texture_number);
	glPopMatrix();
}


void Drawcody() //�������� �׸���
{
	glPushMatrix(); //������ �䷯��

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


	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(0, -140, 0);
	glRotated(torus.yTran, 0, 0, 1);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();

	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(140, 0, 0);
	glRotated(torus.yTran, 0, 0, 1);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();


	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(-140, 0, 0);
	glRotated(torus.yTran, 0, 0, 1);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();

	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(140 / sqrt(2), 140 / sqrt(2), 0);
	glRotated(torus.yTran, 0, 0, 1);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();


	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(-140 / sqrt(2), -140 / sqrt(2), 0);
	glRotated(torus.yTran, 0, 0, 1);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();


	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(-140 / sqrt(2), 140 / sqrt(2), 0);
	glRotated(torus.yTran, 0, 0, 1);
	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix();


	glTranslated(100, 130, -150);

	glRotated(torus.zTran, 0, 0, 1);

	glTranslated(140 / sqrt(2), -140 / sqrt(2), 0);
	glRotated(torus.yTran, 0, 0, 1);
	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();

	glPushMatrix(); //������

	glTranslated(100, 130, -150);

	glColor3f(0, 1, 0);
	glutSolidCube(25);

	glPopMatrix();
}

void DrawMenu(int texture_number)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[texture_number]);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-400, 400, 0);
	glTexCoord2d(0, 0);
	glVertex3f(400, 400, 0);
	glTexCoord2d(1, 0);
	glVertex3f(400, -400, 0);
	glTexCoord2d(1, 1);
	glVertex3f(-400, -400, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void DrawVanQuad(int texture_number)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[texture_number]);

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

	glDisable(GL_TEXTURE_2D);

}

void DrawBottom(int texture_number)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[texture_number]);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-350, 0, -350);
	glTexCoord2d(0, 0);
	glVertex3f(-350, 0, 350);
	glTexCoord2d(1, 0);
	glVertex3f(350, 0, 350);
	glTexCoord2d(1, 1);
	glVertex3f(350, 0, -350);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void DrawVanbgm(int texture_number)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[texture_number]);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-375, 0, -375);
	glTexCoord2d(0, 0);
	glVertex3f(-375, 0, 375);
	glTexCoord2d(1, 0);
	glVertex3f(375, 0, 375);
	glTexCoord2d(1, 1);
	glVertex3f(375, 0, -375);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void Drawbgm(int texture_number)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[texture_number]);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 1);
	glVertex3f(-375, 0, -375);
	glTexCoord2d(0, 0);
	glVertex3f(375, 0, -375);
	glTexCoord2d(1, 0);
	glVertex3f(375, 0, 375);
	glTexCoord2d(1, 1);
	glVertex3f(-375, 0, 375);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}



void Soundinit()
{
	FMOD_System_Create(&g_System); //���� �ý����� ������ִ� �Լ��̴�.


	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL); //���� �ý����� �ʱ�ȭ ���ִ� �Լ���.


	FMOD_System_CreateSound(g_System, "res/Sound/main.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[SOUND_MAIN]); //���带 �޸𸮷� �о���� �Լ� // ����� ���������� mp3,wav,mid,plac,dls,asf,asx,fsb...  ���������
	FMOD_System_CreateSound(g_System, "res/Sound/sister.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[SOUND_MENU]); //���带 �޸𸮷� �о���� �Լ� // ����� ���������� mp3,wav,mid,plac,dls,asf,asx,fsb...  ���������

	FMOD_System_CreateSound(g_System, "res/Sound/swap.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_SWAP]);
	FMOD_System_CreateSound(g_System, "res/Sound/walk.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_WALK]);

	FMOD_System_CreateSound(g_System, "res/Sound/win.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_WIN]);
	FMOD_System_CreateSound(g_System, "res/Sound/draw.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_DRAW]);
	FMOD_System_CreateSound(g_System, "res/Sound/lose.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_LOSE]);

	FMOD_System_CreateSound(g_System, "res/Sound/reset.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_RESET]);
	FMOD_System_CreateSound(g_System, "res/Sound/scenechange.mp3", FMOD_DEFAULT, 0, &g_Sound[SOUND_SCENECHANGE]);


	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_MENU], 0, &g_Channel[SOUND_MENU]);

	

	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_PUSH], 0, &g_Channel[SOUND_PUSH]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_SWAP], 0, &g_Channel[SOUND_SWAP]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_WIN], 0, &g_Channel[SOUND_WIN]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_LOSE], 0, &g_Channel[SOUND_LOSE]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_WALK], 0, &g_Channel[SOUND_WALK]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_SCENECHANGE], 0, &g_Channel[SOUND_SCENECHANGE]);
	//FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[SOUND_RESET], 0, &g_Channel[SOUND_RESET]);
}