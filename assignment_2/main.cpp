#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>

/*  Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/*  Set range for world coordinates.  */
GLfloat xwcMin = -3000.0, xwcMax = 2000.0;
GLfloat ywcMin = -1000.0, ywcMax = 2000.0;

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

void shear2D_yref (GLfloat shx, GLfloat yref)
{
    Matrix3x3 matShearRef;

   /*  Initialize scaling matrix to identity.  */
   matrix3x3SetIdentity (matShearRef);

   matShearRef [0][1] = shx;
   matShearRef [0][2] = -shx * yref;

   matrix3x3PreMultiply (matShearRef, matComposite);
}

void reflectOrigin2D ()
{
    Matrix3x3 matRefOrigin;

    matrix3x3SetIdentity (matRefOrigin);

    matRefOrigin [0][0] = -1;
    matRefOrigin [1][1] = -1;

    matrix3x3PreMultiply(matRefOrigin, matComposite);
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

void triangle (wcPt2D *verts)
{
    GLint k;

    glBegin (GL_TRIANGLES);
       for (k = 0; k < 3; k++)
          glVertex2f (verts [k].x, verts [k].y);
    glEnd ( );
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
        std::cout << "Valid coordinates between 0 - 250" << std::endl;
        std::cout << "Enter the x coordinate for point #" << i+1 << std::endl;
        std::cin >> user_points[i].x;
        std::cout << "Enter the y coordinate for point #" << i+1 << std::endl;
        std::cin >> user_points[i].y;
    }

    //These coordinates were used to test and gave a decent result.
    //wcPt2D user_points [4] = { {50.0, 25.0}, {150.0, 25.0}, {175.0, 100.0}, {75,100} };
    GLint nVerts = 4;
    wcPt2D centroidPt;

    //Calculate centroid point for scaling with a fixed point
    GLint k, xSum = 0, ySum = 0;
    for (k = 0; k < nVerts;  k++) {
      xSum += user_points [k].x;
      ySum += user_points [k].y;
    }
   centroidPt.x = GLfloat (xSum) / GLfloat (nVerts);
   centroidPt.y = GLfloat (ySum) / GLfloat (nVerts);

   //Define origin of (0,0)
   wcPt2D originPt;
   originPt.x = 0;
   originPt.y = 0;

   //scale factors for origin scaling (3,2)
   GLfloat sx = 3, sy = 2;
   //scale factors for fixed scaling (2,3)
   GLfloat inside_sx = 2, inside_sy = 3;
   //45 degree clockwise rotation, reference angle used here to save not needing to create an inverse rotation matrix!
   GLdouble theta = 7*pi/4.0;

   glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
   glColor3f (0.0, 0.0, 1.0);       //  Set initial fill color to blue.
   quadrilateral(user_points);      //  Display the initial user shape with blue

    //Transformations are:
    /*
     1. Rotate the object by 45 deg. clockwise about the origin
     2. Scale the Quad by a scaling factor of (3,2)
     3. Choose any point inside Quad and scale that by a factor of (2,3)
     4. Reflect Quad about Coordinate origin
     5. Shear Quad with shear parameter of Shx = 2, relative to ref. line y = -1
    */

   matrix3x3SetIdentity (matComposite);     //  Initialize Composite Matrix to Identity Matrix
   shear2D_yref(2.0 , -1.0);                //  Begin Transformations: Reverse order for proper multiplication!
   reflectOrigin2D();
   scale2D(inside_sx,inside_sy,centroidPt);
   scale2D(sx,sy,originPt);
   rotate2D(originPt, theta);
   transformVerts2D (nVerts, user_points);  //Do multiplication
   glColor3f (1.0, 0.0, 0.0);            // Set color for transformed quadrilateral to red.
   quadrilateral(user_points);             // Display transformed quadrilateral.

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
   glutCreateWindow ("Assignment #2, Ryan Bracewell");

   init ( );
   glutDisplayFunc (displayFcn);
   glutReshapeFunc (winReshapeFcn);

   glutMainLoop ( );
}
