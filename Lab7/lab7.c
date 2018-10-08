#include <stdlib.h>
#include <GL/GLUT.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

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
#define ORIGINAL_POSX -1.0
#define ORIGINAL_POSY 2.0
#define ORIGINAL_POSZ 0.5


int axis = 2; //axis number
GLfloat theta[3] = { 0.0, 0.0, 70.0 }; //angle of each axis
GLfloat legTheta = 0.0;
GLfloat wingTheta = 6.0;
GLfloat eyeTheta = 0.0;
GLfloat mouthTheta = 10.0;
GLfloat duckPosX = ORIGINAL_POSX; //initialize position of the duck
GLfloat duckPosY = ORIGINAL_POSY;
GLfloat duckPosZ = ORIGINAL_POSZ;
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

GLint menu_id = 0;
GLint submenu_id = 0;

GLboolean moveResetState = true;
GLboolean moveState1Start = false;
GLboolean moveState2Start = false;
GLboolean moveState3Start = false;
GLboolean moveState4Start = false;
GLboolean moveState5Start = false;
GLint moveState = 1;

GLfloat des1X = 0.0;
GLfloat des1Y = 0.0;
GLfloat des1Z = 0.0;
GLfloat des2X = 0.0;
GLfloat des2Y = -2.0;
GLfloat des2Z = 0.5;
GLfloat des3X = ORIGINAL_POSX;
GLfloat des3Y = ORIGINAL_POSY;
GLfloat des3Z = ORIGINAL_POSZ;
GLfloat difX = 0.0;
GLfloat difY = 0.0;
GLfloat difZ = 0.0;
GLfloat difAngleX = 0.0;
GLfloat difAngleY = 0.0;
GLfloat difAngleZ = 0.0;
GLfloat storeAngle = 0.0;

GLint transDirection1 = 0;
GLint transDirection2 = 0;
GLfloat angle2 = 0.0;
GLfloat angle3 = 0.0;
GLfloat transVelocity = 0.015;

GLint flag = -1;
GLint materialSet = 1;

// shading ...

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

materialStruct bodyMaterials = {
	{ 0.8, 0.8, 0.0, 1.0 },
	{ 0.8, 0.8, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct bodyMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct mouseMaterials = {
	{ 0.91, 0.50, 0.20, 1.0 },
	{ 0.91, 0.50, 0.20, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	1.0
};

materialStruct mouseMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct eyeWhiteMaterials = {
	{ 0.9, 0.9, 0.9, 1.0 },
	{ 0.9, 0.9, 0.9, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct eyeWhiteMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct eyeBallMaterials = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct eyeBallMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct hatMaterials = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	1.0
};

materialStruct hatMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct wingsMaterials = {
	{ 0.86, 0.86, 0.02, 1.0 },
	{ 0.86, 0.86, 0.02, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	2.0
};

materialStruct wingsMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct feetMaterials = {
	{ 0.91, 0.59, 0.48, 1.0 },
	{ 0.91, 0.59, 0.48, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct feetMaterials2 = {
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.0, 0.6, 0.0, 1.0 },
	{ 0.1, 0.1, 0.1, 1.0 },
	5.0
};

materialStruct goldMaterials = {
	{ 0.8, 0.8, 0.0, 1.0 },
	{ 0.8, 0.8, 0.0, 1.0 },
	{ 0.7, 0.7, 0.7, 1.0 },
	100.0
};

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};

lightingStruct coloredLighting = {
	{ 0.2, 0.0, 0.0, 1.0 },
	{ 0.0, 1.0, 0.0, 1.0 },
	{ 0.0, 0.0, 1.0, 1.0 }
};

GLfloat light0_pos[4] = { 0.0, 0.0, -3.0, 0.0 };

materialStruct *currentMaterials;
lightingStruct *currentLighting;


void drawBody()
{
	//glColor3f(1.0, 1.0, 0.0);
	if (materialSet == 1) {
		currentMaterials = &bodyMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &bodyMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	glPushMatrix();
	//glTranslatef(0.0, 0.0, BODY_HEIGHT);
	glScaled(0.8, 1.0, 0.65);
	glutSolidSphere(BODY_RADIUS, 100, 100);
	glPopMatrix();
}
void drawTail()
{
	//glColor3f(0.9, 0.9, 0.0);
	if (materialSet == 1) {
		currentMaterials = &bodyMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &bodyMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
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
	//glColor3f(1.0, 1.0, 0.0);
	if (materialSet == 1) {
		currentMaterials = &bodyMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &bodyMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);
	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.55);
	glutSolidSphere(HEAD_RADUIS, 100, 100);

	//mouth 1
	//glColor3ub(233, 150, 122);
	if (materialSet == 1) {
		currentMaterials = &mouseMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &mouseMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);
	glPushMatrix();
	glTranslatef(0.0, -HEAD_RADUIS + 0.04, -0.07);
	glRotatef(mouthTheta, 1.0, 0.0, 0.0);
	glScaled(1.0, 0.8, 0.2);
	glutSolidSphere(MOUTH_RADIUS, 100, 100);
	glPopMatrix();

	//mouth 2
	glPushMatrix();
	glTranslatef(0.0, -HEAD_RADUIS + 0.04, -0.07);
	glRotatef(-mouthTheta, 1.0, 0.0, 0.0);
	glScaled(1.0, 0.8, 0.2);
	glutSolidSphere(MOUTH_RADIUS, 100, 100);
	glPopMatrix();

	//eye 1
	//glColor3f(1.0, 1.0, 1.0);
	if (materialSet == 1) {
		currentMaterials = &eyeWhiteMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &eyeWhiteMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	glPushMatrix();
	glTranslatef(0.2, -HEAD_RADUIS + 0.07, 0.13);
	glutSolidSphere(EYE_RADIUS, 100, 100);
	//glColor3f(0.0, 0.0, 0.0);

	if (materialSet == 1) {
		currentMaterials = &eyeBallMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &eyeBallMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	glTranslatef(0.0, -EYE_RADIUS, 0.0);
	//glRotatef(eyeTheta, 0.0, 1.0, 0.0);
	//glTranslatef(0.02, 0.0, 0.0);
	glutSolidSphere(EYE_BALL_RADIUS, 100, 100);
	glPopMatrix();

	//eye 2
	//glColor3f(1.0, 1.0, 1.0);
	if (materialSet == 1) {
		currentMaterials = &eyeWhiteMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &eyeWhiteMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	glPushMatrix();
	glTranslatef(-0.2, -HEAD_RADUIS + 0.07, 0.13);
	glutSolidSphere(EYE_RADIUS, 100, 100);
	//glColor3f(0.0, 0.0, 0.0);
	if (materialSet == 1) {
		currentMaterials = &eyeBallMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &eyeBallMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

	glTranslatef(0.0, -EYE_RADIUS, 0.0);
	glRotatef(-eyeTheta, 0.0, 1.0, 0.0);
	glTranslatef(-0.02, 0.0, 0.0);
	glutSolidSphere(EYE_BALL_RADIUS, 100, 100);
	glPopMatrix();

	//Hat
	//glColor3f(0.0, 0.0, 0.0);
	if (materialSet == 1) {
		currentMaterials = &hatMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &hatMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);

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
	//glColor3ub(245, 245, 30);
	if (materialSet == 1) {
		currentMaterials = &wingsMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &wingsMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);
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
	//glColor3ub(245, 245, 30);
	if (materialSet == 1) {
		currentMaterials = &wingsMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &wingsMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);
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
	//glColor3ub(233, 150, 122);
	currentMaterials = &feetMaterials;
	if (materialSet == 1) {
		currentMaterials = &feetMaterials;
	}
	else if (materialSet == 2) {
		currentMaterials = &feetMaterials2;
	}
	else if (materialSet == 3) {
		currentMaterials = &goldMaterials;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &currentMaterials->shininess);
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
	glTranslatef(duckPosX, duckPosY, duckPosZ);
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

//void drawFence(){
//    glTranslatef(-0.3, 3.0, 0.0);
//    glRotatef(theta[0], 1.0, 0.0, 0.0);
//    glRotatef(theta[1], 0.0, 1.0, 0.0);
//    glRotatef(theta[2], 0.0, 0.0, 1.0);
//    glScalef(1.0, 1.0, 10.0);
//    glutSolidCube(0.2);
//}

void display()
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ex, ey, ez, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	//    glPushMatrix();
	//    drawFence();
	//    glPopMatrix();

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
		glOrtho(-4.0, 4.0, -4.0 / aspectRatio, 4.0 / aspectRatio, 0.0, 10.0);
	}
	else {// width > height
		glOrtho(-4.0 * aspectRatio, 4.0 *aspectRatio, -4.0, 4.0, 0.0, 10.0);
	}
	//glutPostRedisplay();
}

void idle()
{
	if (flag == 1) {
		//rotate the eyes
		//eyeTheta += 10.0;

		//rotate the feet
		if (feetFlag == 0) {
			legTheta += 5.0;
		}
		if (legTheta > 30.0)
			feetFlag = 1;
		if (feetFlag == 1) {
			legTheta -= 5.0;
		}
		if (legTheta < 0.0)
			feetFlag = 0;

		//rotate the wings
		if (wingFlag == 0) {
			wingTheta += 3.0;
		}
		if (wingTheta > 20.0)
			wingFlag = 1;
		if (wingFlag == 1) {
			wingTheta -= 3.0;
		}
		if (wingTheta < 6.0)
			wingFlag = 0;

		//rotate teh mouth
		if (mouthFlag == 0) {
			mouthTheta += 3.0;
		}
		if (mouthTheta > 30.0)
			mouthFlag = 1;
		if (mouthFlag == 1) {
			mouthTheta -= 3.0;
		}
		if (mouthTheta < 10.0)
			mouthFlag = 0;

		//move
		if (moveResetState == true) {
			difAngleZ = 0.0;
			theta[2] = 70.0;
			duckPosX = ORIGINAL_POSX;
			duckPosY = ORIGINAL_POSY;
			duckPosZ = ORIGINAL_POSZ;
			moveResetState = false;
			moveState = 1;
			moveState1Start = true;
		}
		if (moveState == 1 && moveState1Start == true) {
			difY = des1Y - duckPosY;
			difZ = des1Z - duckPosZ;
			moveState1Start = false;
		}
		if (moveState == 1) {
			if (fabs(duckPosY - des1Y) <= 0.02 && fabs(duckPosZ - des1Z) <= 0.02) {
				moveState = 2;
				moveState2Start = true;
			}
		}
		if (moveState == 2 && moveState2Start == true) {
			difY = des2Y - duckPosY;
			difZ = des2Z - duckPosZ;
			moveState2Start = false;
		}
		if (moveState == 2) {
			if (fabs(duckPosY - des2Y) <= 0.02 && fabs(duckPosZ - des2Z) <= 0.02) {
				moveState = 3;
				moveState3Start = true;
			}
		}
		if (moveState == 3 && moveState3Start == true) {
			difY = des3Y - duckPosY;
			difZ = des3Z - duckPosZ;
			difAngleZ = -180.0;
			storeAngle = theta[2];
			moveState3Start = false;
		}
		if (moveState == 3) {
			if (fabs(duckPosY - des3Y) <= 0.02 && fabs(duckPosZ - des3Z) <= 0.02) {
				moveState = 4;
				moveState4Start = true;
			}
			if (fabs(theta[2] - storeAngle) >= 175.0) {
				difAngleZ = 0.0;
			}
		}
		if (moveState == 4 && moveState4Start == true) {
			difY = 0.0;
			difZ = 0.0;
			difAngleZ = 180.0;
			storeAngle = theta[2];
			moveState4Start = false;
		}
		if (moveState == 4) {
			if (fabs(theta[2] - storeAngle) >= 175.0) {
				difAngleZ = 0.0;
				moveResetState = true;
			}
		}
		duckPosY += difY * transVelocity;
		duckPosZ += difZ * transVelocity;
		theta[2] += difAngleZ * 2 * transVelocity;
	}

	glutPostRedisplay();
}

//set up the menu function
void mymenu(int id)
{
	if (id == 1) {
		materialSet = 1;
	}
	if (id == 2) {
		materialSet = 2;
	}
	if (id == 3) {
		materialSet = 3;
	}
}

void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		flag = -flag;
	}
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0, (GLfloat)800.0/(GLfloat)600.0, 0.0, 100.0);
	glOrtho(-4.0, 4.0, -4.0, 4.0, 0.0, 10.0);

	menu_id = glutCreateMenu(mymenu);
	glutAddMenuEntry("normal materials", 1);
	glutAddMenuEntry("grass materials", 2);
	glutAddMenuEntry("gold materials", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//light properties
	float ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	float position[] = { 4.0f, 4.0f, 4.0f, 1.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//light model properties
	float model_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	int model_two_side = 1; //0=2sided, 1=1sided
	int viewpoint = 1;      //0=infinite Viewpoint, 1=local Viewpoint

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Duck");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMouseFunc(myMouse);
	srand((unsigned)time(NULL));
	init();
	glutMainLoop();
}