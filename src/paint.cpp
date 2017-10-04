/* Sergio Cosman Agraz
 * McMaster University
 * Oct. 7th, 2015
 * ------------------------------
 * Computer Science 3GC3
 * Assignment 1
 * Paint.x
 */
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#  include <stdio.h>
#  include <time.h>
#  include <math.h>

float red, green, blue = 0.0f;
int pointSize = 10;
int mode = 0; //brush mode (point, line, rectangle, circle)
int oldx, oldy = 0;//used to fill the gap between points
bool drawing = false;

void drawPoint(int x, int y){
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glColor3f(red,green,blue);
	glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH)/2.0 )/(glutGet(GLUT_WINDOW_WIDTH)/2.0),
		-(y - glutGet(GLUT_WINDOW_HEIGHT)/2.0 )/(glutGet(GLUT_WINDOW_HEIGHT)/2.0));
	glEnd();
}


void display(void){
	glFlush();
}

int sign(int x) {
    return (x > 0) - (x < 0);
}

void drawLine(int x0, int y0, int x1, int y1){
	// Bresenham's algorithm from Wikipedia
	int dx = abs(x1-x0);
	int dy = abs(y1-y0);
	int error = dx-dy;

	int x = x0;
	int y = y0;

	while (!(x == x1 && y == y1)) {
		drawPoint(x, y);
		float derror = 2*error;
		if (derror > -dy){
			error = error - dy;
			x = x + sign(x1-x0);
		}
		if (derror <  dx){
			error = error + dx;
			y = y + sign(y1-y0); 
		}
	}
}

void drawRectangle(int x0, int y0, int x1, int y1){
	drawLine(x0, y0, x0, y1);
	drawLine(x0, y0, x1, y0);
	drawLine(x1, y0, x1, y1);
	drawLine(x0, y1, x1, y1);

}

void drawCircle(int x0, int y0, int x1, int y1){
	float r = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
	float deg = 0.0174532925;
	for (float theta = deg; theta <= 361*deg; theta+=deg){
		drawLine(
			(x0 + r*cos(theta)), 
			(y0 + r*sin(theta)),
			(x0 + r*cos(theta+deg)), 
			(y0 + r*sin(theta+deg))
		);
	}
}

void keyboard(unsigned char key, int x, int y){
	//printf("kbd\n");
	switch(key){
		case 27: //escape key with fall through
		case 'q':
			exit(0);
			break;
		case'a':
			//RANDOMIZE color
			red = ((float) rand()) / (float) RAND_MAX;
			green = ((float) rand()) / (float) RAND_MAX;
			blue = ((float) rand()) / (float) RAND_MAX;
			break;
		case 'x':
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1,1,1,1);
			break;
		case 'p':	
			mode = 0;
			break;
		case 'l':
			mode = 1;
			break;
		case 'r':
			mode = 2;
			break;
		case 'c':
			mode = 3;
			break;
		default:
			break;
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			pointSize++;
			break;
		case GLUT_KEY_DOWN:
			if (pointSize > 1) {pointSize--;}
			break;
		default:
			break;
	}
}

void mouse(int btn, int state, int x, int y){
	if (btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN){return;}
	switch(mode){
		case 0:
			//point
			drawPoint(x, y);	
			break;
		case 1:
			//lines
			if (drawing == true) {
				drawing = false;
				drawLine(oldx, oldy, x, y);
			} else {
				drawing = true;
				oldx = x;
				oldy = y;
			}
			break;
		case 2:
			//rectangle
			if (drawing == true) {
				drawing = false;
				drawRectangle(oldx, oldy, x, y);
			} else {
				drawing = true;
				oldx = x;
				oldy = y;
			}
			break;
		case 3:
			//circle
			if (drawing == true) {
				drawing = false;
				drawCircle(oldx, oldy, x, y);
			} else {
				drawing = true;
				oldx = x;
				oldy = y;
			}
			break;
		default:
			break;
	}
}

void motion(int x,int y){
	//printf("motion: %i,%i\n", x, y);
	if (mode != 0){return;}
	drawLine(oldx, oldy, x, y);
	oldx = x;
	oldy = y;
	display();
}

void passive(int x,int y){
	//printf("passive: %i,%i\n", x, y);
	if (mode != 0){return;}
	oldx = x;
	oldy = y;
}

/***************************
***** Right-click menu *****
****************************/
void menu(int value){
	//printf("menu action\n");
	switch(value){
		case 0:
			exit(0);
			break;
		default:
			break;
	}
}

void cmenu(int value){
	//printf("colormenu action\n");
	switch(value){
		case 0:
			//red
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
			break;
		case 1:
			//green
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case 2:
			//blue
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
			break;
		case 3:
			//purple
			red = 0.5f;
			green = 0.0f;
			blue = 0.5f;
			break;
		case 4:
			//yellow
			red = 1.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case 5:
			//black
			red = 0.0f;
			green = 0.0f;
			blue = 0.0f;
			break;
		case 6:
			//RANDOM
			red = ((float) rand()) / (float) RAND_MAX;
			green = ((float) rand()) / (float) RAND_MAX;
			blue = ((float) rand()) / (float) RAND_MAX;
			break;
		case 7:
			//white/eraser
			red = 1.0f;
			green = 1.0f;
			blue = 1.0f;
			break;
		default:
			break;
	}
}

void smenu(int value){
	//printf("shapemenu action\n");
	mode = value;
}

void resize(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow(700, 700);
}
/************************
*** Display functions ***
*************************/
void timerRedisplay(int value){
	glutTimerFunc(0.1, timerRedisplay, 0);
	display();
}

/***************
*** Callbacks **
****************/
void glutCallbacks(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutReshapeFunc(resize);
}

void initMenu(){
	
	int colormenu = glutCreateMenu(cmenu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);	
	glutAddMenuEntry("Purple", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Black", 5);
	glutAddMenuEntry("RANDOM", 6);
	glutAddMenuEntry("ERASER", 7);

	glutSetMenu(colormenu);

	int shapemenu = glutCreateMenu(smenu);
	glutAddMenuEntry("Point", 0);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Rectangle", 2);
	glutAddMenuEntry("Circle", 3);

	glutSetMenu(shapemenu);

	int mmenu = glutCreateMenu(menu);
	glutSetMenu(mmenu);

	glutAddSubMenu("Color", colormenu);
	glutAddSubMenu("Shape", shapemenu);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
/***************************
****** Main Function *******
****************************/

int main(int argc, char** argv) {
	printf("######################\n######################\nPaint.x shortcuts:\n######################\na -		random color\n UP_ARROW -	increase brush thickness\n DOWN_ARROW -	decrease brush thickness\n p -		draw point\n l -		draw line\n r -		draw rectangle\n c -		draw circle\n x -		clear screen\n ESC/q -	quit\n######################\n######################\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(700,700);
	glutCreateWindow("Paint.x");
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Initialize random seed
	srand(time(NULL));

	glutCallbacks();

	initMenu();

	timerRedisplay(0);

	glutMainLoop();

	return(0);
}
