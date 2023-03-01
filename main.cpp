/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"


using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() { // Spinning teapot thingy
    // TODO: Your code here!
  for (int angle = 0; angle < 360; angle += 36){ // teapot every 36 degrees, 10 teapots total
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(1, 0 , 0);
    glutSolidTeapot(0.25);
    glPopMatrix();
  }
}
void problem2() { // Staircase
    // TODO: Your code here!
  float x_pos = +10;
	float y_pos = 0;
  float fl_pos = 0;
  
	for(int cube_count = 1; cube_count <= 20; cube_count++){ // 20 rows of cubes for 20 steps
		glPushMatrix();

		glTranslatef(x_pos, y_pos, 0.25);
		glScalef(1, cube_count*.5, 1); // x length is double y length to create stairs with longer surface and less height
		
		glutSolidCube(1);

		glPopMatrix();

		x_pos--; // decrease x position by 1 each time to move the start of the cubes left one
		y_pos += .25; // y position increase by 0.25 to match ratio with x value
	}
}

void problem3() {
    // TODO: Your code here!
  for(int row = 1; row <= 6; row++) { // 6 rows total
		float position = (row % 2 == 0) ? -.5 * row + .5 : -1 * row/2; // row measures position between teapots above and below and positions current teapots in row there

		for(int currentTeapot = 1; currentTeapot <= row; currentTeapot++)
		{
			glPushMatrix();

			glTranslatef(position, (- 4 + row) * .75, 0);
			glutSolidTeapot(.25);

			position += 1;
      //std::cout << position << std::endl;

			glPopMatrix();
		}
	}
}

void problem4() {
    // TODO: Your code here!

  //Pointer Finger
	for(int cube_count = 0; cube_count <= 5; cube_count++){ // loop creating stack of squares upward

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(-1, cube_count); 
    glVertex2f(1, cube_count);
    glVertex2f(0, cube_count + 1);
    glEnd();
    glPopMatrix();
	}

  // Middle finger
  float x_vertex = 0;

  for(int cube_count = 0; cube_count <= 5; cube_count++){ 

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(x_vertex + 1, cube_count); 
    glVertex2f(x_vertex + 3, cube_count);
    glVertex2f(x_vertex + 2, cube_count + 1);
    glEnd();
    glPopMatrix();

		x_vertex += .25; //offsets the position of x vertices slightly to create angled finger
	}

  // 4th finger
  float fourthf_x = 0;

  for(int cube_count = 0; cube_count <= 4; cube_count++){

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(fourthf_x + 3.5, cube_count); 
    glVertex2f(fourthf_x + 5.5, cube_count);
    glVertex2f(fourthf_x + 4.5, cube_count + 1);
    glEnd();
    glPopMatrix();

		fourthf_x += .4;
	}

  // Thumb

  float thumb_x = 0;

  for(int cube_count = 0; cube_count <= 4; cube_count++){

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(thumb_x - 1, cube_count - 2); 
    glVertex2f(thumb_x - 3, cube_count - 2);
    glVertex2f(thumb_x - 2, cube_count - 1);
    glEnd();
    glPopMatrix();

		thumb_x -= 0.5;
	}

  // Pinky

  float pinky_x = 0;

  for(int cube_count = 0; cube_count <= 3; cube_count++){

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(fourthf_x + 3.5, cube_count - 2); 
    glVertex2f(fourthf_x + 5.5, cube_count - 2 );
    glVertex2f(fourthf_x + 4.5, cube_count - 1);
    glEnd();
    glPopMatrix();

		fourthf_x += .4;
	}

  // Palm
  
  for (int row = 0; row <= 5; row++){ //nested loop creating 6 by 6 square to be palm
    int position = 1;
    for(int currentTeapot = 1; currentTeapot <= 6; currentTeapot++)
		{
			glPushMatrix();

      glTranslatef(position - 1, row - 6, 0);
			glutSolidCube(0.75);

			position += 1;
      //std::cout << position << std::endl;

			glPopMatrix();
		}
  }


}

// No code was modified below this point

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
