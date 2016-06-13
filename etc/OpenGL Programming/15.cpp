#include<GL/glut.h>
#include<iostream>
#include<Windows.h>
#include<math.h>

using std::cout;
using std::endl;

#define Wnd_Width 600
#define Wnd_Height 600

#define PI 3.141592
#define SIZE 15

int degree = 0;
GLfloat rotx,roty,rotz;
bool Wireframe = false;
float CameraPosition = 100.0f;

float CameraPosX = 0.0, CameraPosY = 0.0, CameraPosZ = 100.0;
float CameraDirX = 0.0, CameraDirY = 0.0, CameraDirZ = -1.0;
float CameraRotX = 0.0, CameraRotY = 0.0, CameraRotZ = 0.0;

float rotXX = 0, rotYY = 0, rotZZ = 0;
//-------------------------
//setup function
//-------------------------
void InitWindow(void);

//-------------------------
//call back function
//-------------------------
void DrawScene(void);
void SetScene(void);
void TimerFunction(int value);
void Mouse(int button,int state,int x,int y);
void Keyboard(unsigned char key ,int _x,int _y);
void Reshape(int w,int h);
void drawObject(int x , int y, int z);
void drawCoord(void);
void drawOrbit(void);
void SetLight(void);

 //char FSmode[80] = "800x600:32@75";

void main(int argc,char* argv[])
{
	////glutInitPascal(false);
	//glutGameModeString(FSmode);
	//glutEnterGameMode;
	//glutSetCursor(GLUT_CURSOR_NONE);
	
	InitWindow();

	glutDisplayFunc(DrawScene);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutTimerFunc(50, TimerFunction, 0);

	rotx=roty=rotz=0.0f;
	SetScene();

	glutMainLoop();
}	

void InitWindow(void){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(Wnd_Width,Wnd_Height);
	glutCreateWindow("example2");

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);
}

//-------------------------
//call back function
//-------------------------
void DrawScene(void){
   
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();

	//gluLookAt(0.0f, 0.0f, CameraPosition, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(CameraDirX, 0.0f, CameraPosition,     0.0, CameraPosY, 0.0f,    CameraRotX , 1.0f, 0.0f);
	
	glRotatef(rotx,1.0f,0.0f,0.0f);
	glRotatef(roty,0.0f,1.0f,0.0f);
	glRotatef(rotz,0.0f,0.0f,1.0f);


   glPushMatrix();

   SetLight();
   drawCoord();
	drawOrbit();
	drawObject(-100,0,0);

	glPopMatrix();
	
	//Sleep(100);
	

	//rotx=roty=rotz=0;
	glutSwapBuffers();
	

}	

void SetScene(void)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);	
}

void TimerFunction(int value)
{
	degree++;
	if (degree >= 72) //72)
		degree = 0;
	glutTimerFunc(50, TimerFunction, 0);
	glutPostRedisplay();
}

void Reshape(int w,int h){
	GLfloat nRange = 200.0f	;	//CameraPosition*2;//
	GLfloat fAspect;

	if(h == 0 )
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//if(w <= h){
	//	glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,1,nRange);
	//}
	//else{
	//	glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,1,nRange);
	//}
	

	fAspect = (float)w/(float)h;
	gluPerspective(45.0, fAspect, 1.0, 1500.0);
    glTranslatef(0.0f, 0.0f, -350.0f);

	gluLookAt( 0.0f, 0.0f, CameraPosition, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void Mouse(int button,int state,int _x,int _y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	}
	else if(button == GLUT_RIGHT_BUTTON && state ==GLUT_DOWN){
	}
//	glutPostRedisplay();
}

void Keyboard(unsigned char key ,int _x,int _y)
{	
	switch(key){
	case '1':
		rotXX += 5;
		break;

	case '2':
		rotYY += 5;
		break;

	case '3':
		rotZZ += 5;
		break;

	case 27 :
		exit(0);
		break;
	case 'x' :
		rotx -= 2.0f;
		if (rotx <= -360)
			rotx = 0;
		break;
	case 'X' :
		rotx+=2.0f;
		if(rotx >= 360)
			rotx = 0;
		break;
	case 'y' :
		roty -= 2.0f;
		if (roty <= -360)
			roty = 0;
		break;
	case 'Y' :
		roty+=2.0f;
		if(roty >= 360)
			roty = 0;
		break;
	case 'z' :
		rotz -= 2.0f;
		if (rotz <= -360)
			rotz = 0;
		break;
	case 'Z':
		rotz +=2.0f;
		if(rotz >=360)
			rotz =0;
		break;
	case 'W' :
	case 'w' :
		Wireframe = !Wireframe;
		break;
	case 'I' :
	case 'i' :
		CameraPosition -= 30.0f;
		//gluLookAt( 0.0f, 0.0f, CameraPosition, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
		break;
	case 'O' :
	case 'o' :
		CameraPosition += 30.0f;
		//gluLookAt( 0.0f, 0.0f, CameraPosition, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
		break;

	case 'a':
		CameraDirX += 2;
		break;
	case 'b':
		CameraPosY += 2;
		break;
	case 'c':
		CameraRotX += 0.1;
		break;

	case 'q':
		CameraPosition = 100.0;
		CameraDirX = 0.0;
		CameraRotX = 0.0;
		CameraPosY = 0.0;
		break;
		
	default:
		break;
	}
	glutPostRedisplay();
}

void drawObject(int x , int y, int z)
{
   glColor3f(1.0f,1.0f,1.0f);
	if(Wireframe)
		glutWireSphere(SIZE,15,15);
	else
		glutSolidSphere(SIZE,15,15);
		
	for(int i = 0 ; i < 3 ; i++)
	{
		glPushMatrix();
		glColor3f(1-i,i%2,i-1);

		glRotated( (45 * (i-1)) ,0,0,1);
		glRotated(degree*(5*(i+1)),0,1,0);
		
		glRotated(rotXX, 1, 0, 0);
		glRotated(rotYY, 0, 1, 0);
		glRotated(rotZZ, 0, 0, 1);

		glTranslated(x,y,z);
		if(Wireframe)
			glutWireSphere(SIZE*3/5,10,10);
		else
			glutSolidSphere(SIZE*3/5,10,10);
	//	
		glPushMatrix();
			glRotated(-degree*(20*(i+1)),0,1,0);
			glRotated(rotXX, 1, 0, 0);
			glRotated(rotYY, 0, 1, 0);
			glRotated(rotZZ, 0, 0, 1);

			glTranslated(20,0,0);
			glColor3d(i-1,1-i,i%2);
			if(Wireframe)
				glutWireSphere(SIZE*2/5,8,8);
			else
				glutSolidSphere(SIZE*2/5,8,8);
		
		
		glPopMatrix();
//
		glPopMatrix();
	}
}
void drawCoord(void)
{
	glPushMatrix();
	
	glLineWidth(1);
	glBegin(GL_LINES);
		glColor3d(1,0,0);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(50.0f,0.0f,0.0f);

		glColor3d(0,1,0);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,50.0f,0.0f);

		glColor3d(0,0,1);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,50.0f);
	glEnd();
	glPopMatrix();
}

void drawOrbit(void)
{
	glPushMatrix();
	glLineWidth(1);
	
	
	for(int j = -1 ; j < 2 ; j++)
	{   
		glPushMatrix();
			glRotated((45*j),0,0,1);

			glRotated(rotXX, 1, 0, 0);
			glRotated(rotYY, 0, 1, 0);
			glRotated(rotZZ, 0, 0, 1);

			glBegin(GL_LINE_LOOP);

			for(int i = 0 ; i <= 360 ; i++)
			{
				glColor3f(-j,(j+1)%2,j);
				glVertex3f((float)(100*cos(2*i*PI/360)),0.0f,(float)(100*sin(2*i*PI/360)));
			}

			glEnd();
		glPopMatrix();
	}

	glPopMatrix();
}

void SetLight(void)
{
   //glEnable(GL_LIGHTING);
   GLfloat ambient[]={0.8f,0.8f,0.8f,0.0f};
 //  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
   
   GLfloat Diffuse[]={0.0f,0.0f,-100.0f,1.0f};
   GLfloat lightPos[]={300.0f,-300.0f,0.0f,1.0f};
 //  glLightfv(GL_LIGHT0,GL_DIFFUSE,Diffuse);
   glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
   glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
   glEnable(GL_LIGHT0);
 
   glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

}