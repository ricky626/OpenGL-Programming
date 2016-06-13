
#include <gl/glut.h> 			// includes gl.h glu.h
#include <math.h>

#define GL_PI 3.1415
void Keyboard (unsigned char key, int x, int y);

GLfloat xRot = 0.0f, yRot = 0.0f, zRot = 0.0f;
GLfloat zTran = 0.0f;
GLfloat yLeftRot = 0.0, yRightRot = 0.0;


void SetupRC()
{
	// clear ������ ���������� ����
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f );

	// �׸����� ������� ���� 
	glColor3f(1.0f, 0.0f, 0.0f);


}


void DrawScene(void)
{
	GLfloat x,y,z,angle; 

	// �����츦 ������ ������ clear�Ѵ�.
	glClear(GL_COLOR_BUFFER_BIT);

	// ����� �����ϰ� ȸ���Ѵ�.
	glPushMatrix();
		glColor3ub (180, 180, 0);

		glTranslatef (0.0, 0.0, zTran);
		glRotatef (xRot, 1.0f, 0.0f, 0.0f);
		glRotatef (yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);

		glScalef (3.0, 2.0, 2.0);

		glBegin (GL_QUADS);
			glVertex3f (-100.0, -100.0, -100.0);
			glVertex3f (-100.0, -100.0, 100.0);
			glVertex3f (100.0, -100.0, 100.0);
			glVertex3f (100.0, -100.0, -100.0);
			glEnd ();
	glPopMatrix ();
	
	glPushMatrix ();
		glTranslatef (0.0, 0.0, zTran);
		glRotatef (xRot, 1.0f, 0.0f, 0.0f);
		glRotatef (yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);

		glLineWidth(2);
		glBegin(GL_LINES);
		glColor3d(1, 0, 0);
		glVertex3f(0.0f, 0.0f,0.0f);
		glVertex3f(50.0f, 0.0f,0.0f);

		glColor3d(0,1,0);
		glVertex3f(0.0f, 0.0f,0.0f);
		glVertex3f(0.0f, 50.0f,0.0f);

		glColor3d(0,0,1);
		glVertex3f(0.0f, 0.0f,0.0f);
		glVertex3f(0.0f, 0.0f,50.0f);
	glEnd();

	glLineWidth (1);
	glTranslatef (0.0f, -100.0, 0.0);

	glPushMatrix ();
		glColor3f (0.0, 0.0, 1.0);
		glTranslatef (-100.0f, 0.0, 0.0);

		glRotatef (yLeftRot, 0.0f, 1.0f, 0.0f);

		glScalef (1.0, 2.0, 1.0);
		glutSolidCube (100.0f);
	glPopMatrix ();

	glPushMatrix ();
		glColor3f (0.0, 1.0, 0.0);
		
		
		glTranslatef(180.0f, -50.0, -50.0);
		glRotatef(yRightRot, 0.0f, 1.0f, 0.0f);
		glScalef(3.0, 1.0, 1.0);

		glutWireCube (70.0f);

	glPopMatrix ();

	//glutSolidCube (50.0f);

	// ������ ����� ��ȯ�Ѵ�.
	glPopMatrix();

	// ���� ���۸����� �׸� �׸��� ����	
	glutSwapBuffers();
	//glFlush ();
}

void Reshape(int w, int h)
{
	// �������� ���� ���� ����
    glViewport(0, 0, w, h);

	// ���� ��� ���� �缳�� // �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����
	
	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard (unsigned char key, int x, int y)
{
	if ( key == 'f' ) 
		zTran += 5.0f;
	else if ( key == 'F' )
		zTran -= 5.0f;
	else if ( key == 'l')
		yLeftRot += 5.0f;
	else if (key == 'r')
		yRightRot += 5.0f;

	else if (key == 'z')
		zRot += 5.0f;
	else if (key == 'Z')
		zRot -= 5.0f;

	if ( yLeftRot > 356.0f )
		yLeftRot = 0.0f;
	if ( yLeftRot < 0.0f )
		yLeftRot = 355.0f;
	if ( yRightRot > 356.0f )
		yRightRot = 0.0f;
	if ( yRightRot < 0.0f )
		yRightRot = 355.0f;


	glutPostRedisplay ();
}

void SpecialKeyBoard (int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		xRot += 5.0f;
	else if (key == GLUT_KEY_RIGHT)
		xRot -= 5.0f;
	else if (key == GLUT_KEY_UP)
		yRot += 5.0f;
	else if (key == GLUT_KEY_DOWN)
		yRot -= 5.0f;

	if ( xRot > 356.0f )
		xRot = 0.0f;
	if ( xRot < 0.0f )
		xRot = 355.0f;
	if ( yRot > 356.0f )
		yRot = 0.0f;
	if ( yRot < 0.0f )
		yRot = 355.0f;

	glutPostRedisplay ();
}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode (GLUT_RGB);
	glutInitWindowSize ( 800, 600 ); 	// �������� ũ�� ����
	glutCreateWindow ("example");

	SetupRC();
	
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutSpecialFunc (SpecialKeyBoard);
	glutKeyboardFunc (Keyboard);

	glutMainLoop();

	return 0;
}

