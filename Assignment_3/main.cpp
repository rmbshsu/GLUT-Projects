#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>

/*  Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/*  Set range for world coordinates.  */
GLfloat xwcMin = -100.0, xwcMax = 100.0;
GLfloat ywcMin = -100.0, ywcMax = 100.0;

class wcPt2D {
   public:
      GLfloat x, y;
};

typedef GLfloat Matrix3x3 [3][3];

Matrix3x3 matComposite;

const GLdouble pi = 3.14159;

void init (void)
{
   /*  Set color of display window to white.  */
   glClearColor (1.0, 1.0, 1.0, 0.0);
}

/* Construct the 3 by 3 identity matrix. */
void matrix3x3SetIdentity (Matrix3x3 matIdent3x3)
{
   GLint row, col;

   for (row = 0; row < 3; row++)
      for (col = 0; col < 3; col++)
         matIdent3x3 [row][col] = (row == col);
}

/* Premultiply matrix m1 times matrix m2, store result in m2. */
void matrix3x3PreMultiply (Matrix3x3 m1, Matrix3x3 m2)
{
   GLint row, col;
   Matrix3x3 matTemp;

   for (row = 0; row < 3; row++)
      for (col = 0; col < 3 ; col++)
         matTemp [row][col] = m1 [row][0] * m2 [0][col] + m1 [row][1] *
                            m2 [1][col] + m1 [row][2] * m2 [2][col];

   for (row = 0; row < 3; row++)
      for (col = 0; col < 3; col++)
         m2 [row][col] = matTemp [row][col];
}

void translate2D (GLfloat tx, GLfloat ty)
{
   Matrix3x3 matTransl;

   /*  Initialize translation matrix to identity.  */
   matrix3x3SetIdentity (matTransl);

   matTransl [0][2] = tx;
   matTransl [1][2] = ty;

   /*  Concatenate matTransl with the composite matrix.  */
   matrix3x3PreMultiply (matTransl, matComposite);
}

void rotate2D (wcPt2D pivotPt, GLfloat theta)
{
   Matrix3x3 matRot;

   /*  Initialize rotation matrix to identity.  */
   matrix3x3SetIdentity (matRot);

   matRot [0][0] = cos (theta);
   matRot [0][1] = -sin (theta);
   matRot [0][2] = pivotPt.x * (1 - cos (theta)) +
                        pivotPt.y * sin (theta);
   matRot [1][0] = sin (theta);
   matRot [1][1] = cos (theta);
   matRot [1][2] = pivotPt.y * (1 - cos (theta)) -
                        pivotPt.x * sin (theta);

   /*  Concatenate matRot with the composite matrix.  */
   matrix3x3PreMultiply (matRot, matComposite);
}

void scale2D (GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
   Matrix3x3 matScale;

   /*  Initialize scaling matrix to identity.  */
   matrix3x3SetIdentity (matScale);

   matScale [0][0] = sx;
   matScale [0][2] = (1 - sx) * fixedPt.x;
   matScale [1][1] = sy;
   matScale [1][2] = (1 - sy) * fixedPt.y;

   /*  Concatenate matScale with the composite matrix.  */
   matrix3x3PreMultiply (matScale, matComposite);
}


/* Using the composite matrix, calculate transformed coordinates. */
void transformVerts2D (GLint nVerts, wcPt2D * verts)
{
   GLint k;
   GLfloat temp;

   for (k = 0; k < nVerts; k++) {
      temp = matComposite [0][0] * verts [k].x + matComposite [0][1] *
             verts [k].y + matComposite [0][2];
      verts [k].y = matComposite [1][0] * verts [k].x + matComposite [1][1] *
                  verts [k].y + matComposite [1][2];
         verts [k].x = temp;
   }
}


void quadrilateral (wcPt2D *verts)
{
    GLint k;

    glBegin (GL_POLYGON);
        for (k = 0; k < 4; k++)
            glVertex2f(verts[k].x, verts [k].y);
    glEnd();
}


void displayFcn (void)
{
    //Get the coordinates from the user, and store inside array
    wcPt2D user_points [4];
        for(int i = 0; i < 4; i++){
        std::cout << "Valid coordinates between -100 - 100" << std::endl;
        std::cout << "Enter the x coordinate for point #" << i+1 << std::endl;
        std::cin >> user_points[i].x;
        std::cout << "Enter the y coordinate for point #" << i+1 << std::endl;
        std::cin >> user_points[i].y;
    }

    //These coordinates were used to test output and is a simple square with 30 units length.
    //wcPt2D user_points [4] = { {10.0, 10.0}, {40.0, 10.0}, {40.0, 40.0}, {10,40} };
    GLint nVerts = 4;

   //Define origin of (0,0)
   wcPt2D originPt;
   originPt.x = 0;
   originPt.y = 0;

   //scale factors for origin scaling (3,2)
   GLfloat sx = 2, sy = 1;
   GLfloat tx = 2, ty = 5;
   //90 degree anti-clockwise rotation, an appropriate reference angle could also be used here to go clockwise.
   GLdouble theta = pi/2.0;

   glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
   glColor3f (1.0, 0.0, 1.0);       //  Set initial fill color to purple.
   quadrilateral(user_points);      //  Display the initial user shape with purple

    //Transformations are:
    /*
     1. Rotate the object by 45 deg. anti-clockwise about the origin
     2. Translate each point by (2,5)
     3. Scale each point by a scaling factor of (2,1)
    */

   matrix3x3SetIdentity (matComposite);     //  Initialize Composite Matrix to Identity Matrix
   scale2D(sx,sy,originPt);                 //  Begin Transformations: Reverse order for proper multiplication!
   translate2D(tx,ty);
   rotate2D(originPt, theta);
   transformVerts2D (nVerts, user_points);  //Do composite transformation by multiplying
   glColor3f (0.0, 1.0, 0.0);               // Set color for transformed quadrilateral to green.
   quadrilateral(user_points);              // Display transformed quadrilateral.

   //A handy loop similar to the input loop to see the coordinates of the transformed shape
    /*
    for(int i = 0; i < 4; i++){
        std::cout << "x coordinate for point #" << i+1 << std::endl;
        std::cout << user_points[i].x;
        std::cout << "y coordinate for point #" << i+1 << std::endl;
        std::cout << user_points[i].y << std::endl;
    }
    */
   glFlush ( );

}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ( );
   gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

   glClear (GL_COLOR_BUFFER_BIT);
}


int main (int argc, char ** argv)
{

   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition (50, 50);
   glutInitWindowSize (winWidth, winHeight);
   glutCreateWindow ("Assignment #3, Ryan Bracewell");

   init ( );
   glutDisplayFunc (displayFcn);
   glutReshapeFunc (winReshapeFcn);

   glutMainLoop ( );
}
