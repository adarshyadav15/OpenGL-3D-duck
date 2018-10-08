#include <stdlib.h>
#include <GL/GLUT.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define random(x) (rand()%x)

#define BODY_RADIUS 0.8
#define TAIL_LENGTH 0.2
#define TAIL_RADIUS 0.05
#define HEAD_RADUIS 0.45
#define MOUTH_RADIUS 0.15
#define EYE_RADIUS 0.08
#define EYE_BALL_RADIUS 0.02
#define WING_RADIUS 0.3
#define LEG_RADIUS 0.07
#define FEET_RADIUS 0.04
#define HAT_HEIGHT 0.4
#define HAT_RADIUS 0.4

int axis = 2; //axis number
GLfloat theta[3] = { 0.0, 0.0, 30.0 }; //angle of each axis
GLfloat legTheta = 0.0;
GLfloat wingTheta = 6.0;
GLfloat eyeTheta = 0.0;
GLfloat mouthTheta = 10.0;
GLfloat posX = 0.0; //initialize position of the duck
GLfloat posY = 0.0;
GLfloat posZ = 0.0;
GLfloat mx = 1.0f; //scale factor
GLfloat my = 1.0f;
GLfloat mz = 1.0f;
GLfloat ex = 3.0; //camera position
GLfloat ey = 0.0;
GLfloat ez = 0.5;
GLfloat legRadius = 0.05;
GLfloat legLength = 0.1;
GLint view = 0;
GLint feetFlag = 0;
GLint wingFlag = 0;
GLint mouthFlag = 0;

GLfloat randomX = 0.0;
GLfloat randomY = 0.0;
GLfloat randomZ = 0.0;
GLfloat difX = 0.0;
GLfloat difY = 0.0;
GLfloat difZ = 0.0;
GLint transDirection1 = 0;
GLint transDirection2 = 0;
GLfloat angle2 = 0.0;
GLfloat angle3 = 0.0;
GLfloat transVelocity = 0.01;


void drawBody()
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	//glTranslatef(0.0, 0.0, BODY_HEIGHT);
	glScaled(0.8, 1.0, 0.65);
	glutSolidSphere(BODY_RADIUS, 100, 100);
	glPopMatrix();
}
void drawTail()
{
	glColor3f(0.9, 0.9, 0.0);
	glPushMatrix();
	glTranslatef(0.0, BODY_RADIUS - 0.1, -0.2);
	glRotatef(-110.0, 1.0, 0.0, 0.0);
	glutSolidCone(TAIL_RADIUS, TAIL_LENGTH, 40, 40);
	glPopMatrix();
}
void drawHead()
{
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	//Head
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.55);
	glutSolidSphere(HEAD_RADUIS, 100, 100);

	//mouth 1
	glColor3ub(233, 150, 122);
	glPushMatrix();
	glTranslatef(0.0, -HEAD_RADUIS + 0.02, -0.07);
	glRotatef(mouthTheta, 1.0, 0.0, 0.0);
	glScaled(1.0, 0.8, 0.2);
	glutSolidSphere(MOUTH_RADIUS, 100, 100);
	glPopMatrix();

	//mouth 2
	glPushMatrix();
	glTranslatef(0.0, -HEAD_RADUIS + 0.02, -0.07);
	glRotatef(-mouthTheta, 1.0, 0.0, 0.0);
	glScaled(1.0, 0.8, 0.2);
	glutSolidSphere(MOUTH_RADIUS, 100, 100);
	glPopMatrix();

	//eye 1
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.2, -HEAD_RADUIS + 0.07, 0.13);
	glutSolidSphere(EYE_RADIUS, 100, 100);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, -EYE_RADIUS, 0.0);
	glRotatef(eyeTheta, 0.0, 1.0, 0.0);
	glTranslatef(0.02, 0.0, 0.0);
	glutSolidSphere(EYE_BALL_RADIUS, 100, 100);
	glPopMatrix();

	//eye 2
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-0.2, -HEAD_RADUIS + 0.07, 0.13);
	glutSolidSphere(EYE_RADIUS, 100, 100);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, -EYE_RADIUS, 0.0);
	glRotatef(-eyeTheta, 0.0, 1.0, 0.0);
	glTranslatef(-0.02, 0.0, 0.0);
	glutSolidSphere(EYE_BALL_RADIUS, 100, 100);
	glPopMatrix();

	//Hat
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.03*HAT_RADIUS + 0.9*HEAD_RADUIS);
	glScaled(1.0, 1.0, 0.05);
	glutSolidSphere(HAT_RADIUS, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.03*HAT_RADIUS + 0.9*HEAD_RADUIS);
	gluCylinder(quadratic, 0.2, 0.2, HAT_HEIGHT, 100, 100);
	glPopMatrix();

	glTranslatef(0.0, 0.0, 0.03*HAT_RADIUS + 0.9*HEAD_RADUIS + HAT_HEIGHT);
	glScaled(1.0, 1.0, 0.05);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPopMatrix();
}
void drawWings()
{
	//Wing 1
	glColor3ub(245, 245, 30);
	glPushMatrix();
	glTranslatef(BODY_RADIUS * 0.8, 0.0, 0.1);
	glRotatef(-5.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -WING_RADIUS, 0.0);
	glRotatef(wingTheta, 0.0, 0.0, 1.0);
	glTranslatef(0.0, WING_RADIUS, 0.0);
	glScaled(0.3, 1.0, 0.8);
	glutSolidSphere(WING_RADIUS, 100, 100);
	glPopMatrix();

	//wing 2
	glColor3ub(245, 245, 30);
	glPushMatrix();
	glTranslatef(-BODY_RADIUS * 0.8, 0.0, 0.1);
	glRotatef(5.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -WING_RADIUS, 0.0);
	glRotatef(-wingTheta, 0.0, 0.0, 1.0);
	glTranslatef(0.0, WING_RADIUS, 0.0);
	glScaled(0.3, 1.0, 0.8);
	glutSolidSphere(WING_RADIUS, 100, 100);
	glPopMatrix();
}
void drawFeet()
{
	//feet 1
	glColor3ub(233, 150, 122);
	glPushMatrix();

	glTranslatef(BODY_RADIUS * 0.6, 0.0, -0.45 * BODY_RADIUS);
	glutSolidSphere(LEG_RADIUS, 100, 100);

	glTranslatef(0.0, -0.05, 0.0);
	glRotatef(legTheta, 1.0, 0.0, 0.0);
	glScaled(2.0, 2.0, 0.6);
	glutSolidSphere(FEET_RADIUS, 100, 100);

	glPopMatrix();

	//feet 2
	glPushMatrix();

	glTranslatef(-BODY_RADIUS * 0.6, 0.0, -0.45 * BODY_RADIUS);
	glutSolidSphere(LEG_RADIUS, 100, 100);

	glTranslatef(0.0, -0.05, 0.0);
	glRotatef(legTheta, 1.0, 0.0, 0.0);
	glScaled(2.0, 2.0, 0.6);
	glutSolidSphere(FEET_RADIUS, 100, 100);

	glPopMatrix();
}
void drawDuck()
{
	glTranslatef(posX, posY, posZ);
	glScalef(mx, my, mz);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glPushMatrix();
	//body
	drawBody();

	//tail
	drawTail();

	//Head
	drawHead();

	//wings
	drawWings();

	//feet
	drawFeet();

	glPopMatrix();
}

void display()
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ex, ey, ez, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glPushMatrix();
	drawDuck();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	// in case of being divided by 0
	if (0 == h) {
		h = 1;
	}
	// set the viewport
	glViewport(0, 0, w, h);

	// reset the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// calculate the aspect ratio
	aspectRatio = (GLfloat)w / (GLfloat)h;

	// define the clipping region
	if (w <= h) {// width < height
		glOrtho(-2.0, 2.0, -2.0 / aspectRatio, 2.0 / aspectRatio, 0.0, 10.0);
	}
	else {// width > height
		glOrtho(-2.0 * aspectRatio, 2.0 *aspectRatio, -2.0, 2.0, 0.0, 10.0);
	}
	//glutPostRedisplay();
}


void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0, (GLfloat)800.0/(GLfloat)600.0, 0.0, 100.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 10.0);

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Duck");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);;
	init();
	glutMainLoop();
}