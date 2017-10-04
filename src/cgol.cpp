/* Sergio Cosman Agraz
 * McMaster University
 * Jan 21th, 2016
 * ------------------------------
 * Computer Science 3GC3
 * Assignment 1
 * Conway's Game of Life
 */

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/****************
*****DISPLAY*****
*****************/
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	printf("clear screen\n");

	glColor3f(0,0,0);
	glBegin(GL_POINTS);
		glVertex2f(0, 0);
	glEnd();
	printf("draw point\n");

	glFlush();
};
/****************
**GRID FUNCTIONS*
*****************/

/********************
**CONTROLL FUNCTIONS*
*********************/

/***************
*** Callbacks **
****************/

/***************************
****** Main Function *******
****************************/

int main(int argc, char** argv) {
	//Create main window
	printf("starting main\n");
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Conway's Game of Life.x");

	//Set clear colour to white
	glClearColor(1,1,1,1);

	glutDisplayFunc(display);

	glutMainLoop();

	return(0);
};