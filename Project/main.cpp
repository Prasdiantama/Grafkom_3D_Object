#include<gl/freeglut.h>

float xrot =0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
bool mouseDown = false;

void ukur(int lebar, int tinggi){
if(tinggi==0) tinggi=1;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45,lebar/tinggi, 5, 450);
glTranslatef(0,0,-300);
glMatrixMode(GL_MODELVIEW);
}
void myinit(void){
glClearColor (0.0, 0.0, 0.0, 0.0);
glMatrixMode(GL_PROJECTION);
glEnable(GL_DEPTH_TEST);

glMatrixMode(GL_MODELVIEW);
glPointSize(10.0);
glLineWidth(7.0f);
}

void idle()
{
if (!mouseDown)
{
xrot += 0.3;
yrot += 0.4;
}
glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
mouseDown = true;
xdiff = x - yrot;
ydiff = -y + xrot;
}
else
mouseDown = false;
}

void mouseMotion(int x, int y)
{
if(mouseDown)
{
yrot = x - xdiff;
xrot = y + ydiff;
glutPostRedisplay();
}
}

void tampilan(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
gluLookAt(0,0,3,0,0,0,0,1,0);
glRotatef(xrot, 1, 0,0);
glRotatef(yrot, 0,1,0);
glPushMatrix();


glBegin(GL_POLYGON);
glColor3f(255,128,0);
glVertex3f(-50,15,40);
glVertex3f(50,15,40);
glVertex3f(50,15,-10);
glVertex3f(-50,15,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(102,51,0);
glVertex3f(-50,10,40);
glVertex3f(50,10,40);
glVertex3f(50,10,-10);
glVertex3f(-50,10,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(102,51,0);
glVertex3f(50,10,40);
glVertex3f(50,15,40);
glVertex3f(50,15,-10);
glVertex3f(50,10,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(102,51,0);
glVertex3f(-50,10,40);
glVertex3f(-50,15,40);
glVertex3f(-50,15,-10);
glVertex3f(-50,10,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(102,51,0);
glVertex3f(-50,10,40);
glVertex3f(-50,15,40);
glVertex3f(50,15,40);
glVertex3f(50,10,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(102,51,0);
glVertex3f(-50,10,-10);
glVertex3f(-50,15,-10);
glVertex3f(50,15,-10);
glVertex3f(50,10,-10);
glEnd();

glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,-40,30);
glVertex3f(-40,-40,30);
glVertex3f(-40,-40,40);
glVertex3f(-50,-40,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,40);
glVertex3f(-40,10,40);
glVertex3f(-40,-40,40);
glVertex3f(-50,-40,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,30);
glVertex3f(-40,10,30);
glVertex3f(-40,-40,30);
glVertex3f(-50,-40,30);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,30);
glVertex3f(-50,-40,30);
glVertex3f(-50,-40,40);
glVertex3f(-50,10,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-40,10,30);
glVertex3f(-40,-40,30);
glVertex3f(-40,-40,40);
glVertex3f(-40,10,40);
glEnd();

glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,-40,30);
glVertex3f(40,-40,30);
glVertex3f(40,-40,40);
glVertex3f(50,-40,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,40);
glVertex3f(40,10,40);
glVertex3f(40,-40,40);
glVertex3f(50,-40,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,30);
glVertex3f(40,10,30);
glVertex3f(40,-40,30);
glVertex3f(50,-40,30);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,30);
glVertex3f(50,-40,30);
glVertex3f(50,-40,40);
glVertex3f(50,10,40);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(40,10,30);
glVertex3f(40,-40,30);
glVertex3f(40,-40,40);
glVertex3f(40,10,40);
glEnd();

glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,-40,0);
glVertex3f(-40,-40,0);
glVertex3f(-40,-40,-10);
glVertex3f(-50,-40,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,0);
glVertex3f(-40,10,0);
glVertex3f(-40,-40,0);
glVertex3f(-50,-40,0);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,-10);
glVertex3f(-40,10,-10);
glVertex3f(-40,-40,-10);
glVertex3f(-50,-40,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-50,10,0);
glVertex3f(-50,-40,0);
glVertex3f(-50,-40,-10);
glVertex3f(-50,10,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(-40,10,0);
glVertex3f(-40,-40,0);
glVertex3f(-40,-40,-10);
glVertex3f(-40,10,-10);
glEnd();

glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,-40,0);
glVertex3f(40,-40,0);
glVertex3f(40,-40,-10);
glVertex3f(50,-40,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,0);
glVertex3f(40,10,0);
glVertex3f(40,-40,0);
glVertex3f(50,-40,0);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,-10);
glVertex3f(40,10,-10);
glVertex3f(40,-40,-10);
glVertex3f(50,-40,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(50,10,0);
glVertex3f(50,-40,0);
glVertex3f(50,-40,-10);
glVertex3f(50,10,-10);
glEnd();
glBegin(GL_POLYGON);
glColor3f(153,76,0);
glVertex3f(40,10,0);
glVertex3f(40,-40,0);
glVertex3f(40,-40,-10);
glVertex3f(40,10,-10);
glEnd();


glPushMatrix();
glPopMatrix();
glutSwapBuffers();
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(240, 80);
    glutInitWindowSize(750, 600);
    glutCreateWindow("LIVNG ROOM 3D");
    myinit();
    glutDisplayFunc(tampilan);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
    glutReshapeFunc(ukur);
    glutMainLoop();
}
