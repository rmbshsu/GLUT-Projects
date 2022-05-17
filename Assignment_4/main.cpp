#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;

class scrPt{
public:
    GLint x,y;
};

static void init (void)
{
scrPt hexVertex;  GLdouble hexTheta;  GLint k;

glClearColor (1.0, 1.0, 1.0, 0.0);

/* Set up a display list for a red regular hexagon.
Vertices for the hexagon are six equally spaced
points around the circumference of a circle.
*/
    regHex = glGenLists (1);
    glNewList (regHex, GL_COMPILE);  glColor3f (0.75, 0.0, 0.5);
    glBegin (GL_POLYGON);  for (k = 0; k < 6; k++){
    hexTheta = TWO_PI * k / 6;
    hexVertex.x = 150 + 100 * cos (hexTheta);  hexVertex.y = 150 + 100 * sin (hexTheta);  glVertex2i (hexVertex.x, hexVertex.y);
    }
    glEnd ( );
    glEndList ( );
}

void displayHex (void)
{
glClear (GL_COLOR_BUFFER_BIT);

glPushMatrix ( );
glRotatef (rotTheta, 0.0, 0.0, 1.0);  glCallList (regHex);
glPopMatrix ( );
glutSwapBuffers ( );  glFlush ( );
}

/*
    Following are functions for rotating the hexagon
    either clockwise or counter-clockwise, and
    with regular speed or double speed.
*/

void anti_rotateHex (void)
{
rotTheta += 1.0;
if (rotTheta > 360.0) rotTheta -= 360.0;

glutPostRedisplay ( );
}

void fast_anti_rotateHex(void)
{
rotTheta += 2.0;
if (rotTheta > 360.0)  rotTheta -= 360.0;

glutPostRedisplay ( );
}

void clock_rotateHex(void)
{
rotTheta -= 1.0;
if (rotTheta < 360.0) rotTheta += 360.0;

glutPostRedisplay();

}

void fast_clock_rotateHex(void)
{
rotTheta -= 2.0;
if (rotTheta < 360.0) rotTheta += 360.0;

glutPostRedisplay();
}



void winReshapeFcn (int newWidth, int newHeight)
{
glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);  glMatrixMode (GL_PROJECTION);
glLoadIdentity ( );
gluOrtho2D (-320.0, 320.0, -320.0, 320.0);

glMatrixMode (GL_MODELVIEW);  glLoadIdentity ( );
glClear (GL_COLOR_BUFFER_BIT);
}


//Keys needed are q, w, and x
//ASCII values for each are: 113, 119, 120
//q : rotate hex around z axis clockwise w/ my speed
//w: rotate hex around z axis clockwise w/ 2x speed
//x: pause
//esc: quit - 27
void Keyboard(unsigned char c, int x, int y)
{
    //Control for keyboard, added ESC for quit functionality
    printf("%d\n",c);
    switch(c)
    {
        case 113:
            glutIdleFunc(clock_rotateHex);
            break;
        case 119:
            glutIdleFunc(fast_clock_rotateHex);
            break;
        case 120:
            glutIdleFunc(NULL);
            break;
        case 27:
            exit(1);
    }
}

void MouseFcn (int button, int action, int x, int y)
{
    //Control for mouse buttons
    switch(button){
    case GLUT_LEFT_BUTTON:
        if (action == GLUT_DOWN)
            glutIdleFunc(anti_rotateHex);
        break;
    case GLUT_RIGHT_BUTTON:
        if (action == GLUT_DOWN)
            glutIdleFunc(fast_anti_rotateHex);
        break;
    default:
        break;

    }

}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth,winHeight);
    glutInitWindowPosition(150,150);
    glutCreateWindow("Ryan Bracewell - Assignment #4");

    std::cout << "Left Mouse: Anticlockwise Rotation about z-axis." << std::endl;
    std::cout << "Right Mouse: Anticlockwise Rotation about z-axis with double speed." << std::endl;
    std::cout << "q: Clockwise Rotation about z-axis." << std::endl;
    std::cout << "w: Clockwise Rotation about z-axis with double speed." << std::endl;
    std::cout << "x: Pause the animation." << std::endl;
    std::cout << "ESC: Exit the program." << std::endl;

    init();
    glutDisplayFunc(displayHex);
    glutReshapeFunc(winReshapeFcn);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseFcn);
    glutMainLoop();
    return 0;
}
