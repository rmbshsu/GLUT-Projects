#include <windows.h>
#ifdef __APPLE__

#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>

void init (void)
{
	glClearColor (0.45, 0.45, 0.75, 1.0); // Set display-window color.
	glMatrixMode (GL_PROJECTION); // Set projection parameters.
	gluOrtho2D (0.0, 200.0, 0.0, 150.0); //Define 2D co-ordinate plane for window.
}
/*
Each shape is made into its own function for neatness.
The unfill prefix refers to a shape that is just the outline.
The regular name of the shape refers to the filled variation.
Each shape until the circles contains the collection of vertices I calculated.
*/
void triangle (void)
{
    glColor3f (0.0, 0.4, 0.2);
    glBegin (GL_POLYGON);
    glVertex2i ( 50, 137.32);
    glVertex2i ( 40, 120);
    glVertex2i ( 60, 120);
    glEnd ( );
    glFlush();
}

void unfill_triangle (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.4, 0.2);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 20, 137.32);
    glVertex2i ( 10, 120);
    glVertex2i ( 30, 120);
    glEnd ( );
    glFlush();
}

//Functions to display both squares
void unfill_square (void)
{
    glColor3f (1, 0.2, 0.2);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 70, 140);
    glVertex2i ( 90, 140);
    glVertex2i ( 90, 120);
    glVertex2i ( 70, 120);
    glEnd ( );
    glFlush();
}

void square(void)
{
    glColor3f (1, 0.2, 0.2);
    glBegin (GL_POLYGON);
    glVertex2i ( 100, 140);
    glVertex2i ( 120, 140);
    glVertex2i ( 120, 120);
    glVertex2i ( 100, 120);
    glEnd ( );
    glFlush();
}

//Functions to display both pentagons
void unfill_pentagon(void)
{
    glColor3f (0.5, 0.3, 0.3);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 150, 140);
    glVertex2i ( 137.86, 131.18);
    glVertex2i ( 142.49, 116.91);
    glVertex2i ( 157.49, 116.91);
    glVertex2i ( 162.36, 131.18);
    glEnd ( );
    glFlush();
}

void pentagon (void)
{
    glColor3f (0.7, 0.3, 0.3);
    glBegin (GL_POLYGON);
    glVertex2i ( 180, 140);
    glVertex2i ( 167.86, 131.18);
    glVertex2i ( 172.49, 116.91);
    glVertex2i ( 187.49, 116.91);
    glVertex2i ( 192.36, 131.18);
    glEnd ( );
    glFlush();
}

//Functions to display both hexagons
void unfill_hexagon (void)
{
    glColor3f (0.7, 0.5, 0.5);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 20, 90);
    glVertex2i ( 9.61, 84);
    glVertex2i ( 9.61, 72);
    glVertex2i ( 20, 66);
    glVertex2i ( 30.39, 72);
    glVertex2i ( 30.39, 84);
    glEnd ( );
    glFlush();

}

void hexagon (void)
{
    glColor3f (0.7, 0.5, 0.5);
    glBegin (GL_POLYGON);
    glVertex2i ( 50, 90);
    glVertex2i ( 39.61, 84);
    glVertex2i ( 39.61, 72);
    glVertex2i ( 50, 66);
    glVertex2i ( 60.39, 72);
    glVertex2i ( 60.39, 84);
    glEnd ( );
    glFlush();

}

//Functions to display both heptagons
void unfill_heptagon (void)
{
    glColor3f (0.25, 0.3, 0.1);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 80, 90);
    glVertex2i ( 87.82, 86.23);
    glVertex2i ( 89.75, 77.78);
    glVertex2i ( 84.34, 70.99);
    glVertex2i ( 75.66, 70.99);
    glVertex2i ( 70.25, 77.77);
    glVertex2i ( 72.18, 86.23);
    glEnd ( );
    glFlush();

}

void heptagon (void)
{
    glColor3f (0.25, 0.3, 0.1);
    glBegin (GL_POLYGON);
    glVertex2i ( 110, 90);
    glVertex2i ( 117.82, 86.23);
    glVertex2i ( 119.75, 77.78);
    glVertex2i ( 114.34, 70.99);
    glVertex2i ( 105.66, 70.99);
    glVertex2i ( 100.25, 77.77);
    glVertex2i ( 102.18, 86.23);
    glEnd ( );
    glFlush();

}

//Functions to display both octagons
void unfill_octagon (void)
{
    glColor3f (0.15, 0.7, 0.2);
    glBegin (GL_LINE_LOOP);
    glVertex2i ( 140, 90);
    glVertex2i ( 132.93, 82.93);
    glVertex2i ( 132.93, 72.93);
    glVertex2i ( 140, 65.86);
    glVertex2i ( 150, 65.86);
    glVertex2i ( 157.07, 72.93);
    glVertex2i ( 157.07, 82.93);
    glVertex2i ( 150, 90);
    glEnd ( );
    glFlush();
}

void octagon (void)
{
    glColor3f (0.15, 0.7, 0.2);
    glBegin (GL_POLYGON);
    glVertex2i ( 170, 90);
    glVertex2i ( 162.93, 82.93);
    glVertex2i ( 162.93, 72.93);
    glVertex2i ( 170, 65.86);
    glVertex2i ( 180, 65.86);
    glVertex2i ( 187.07, 72.93);
    glVertex2i ( 187.07, 82.93);
    glVertex2i ( 180, 90);
    glEnd ( );
    glFlush();
}

void unfill_circle(void)
{
    //define our number of 'sides', and the radius for our circle
    //also the coordinates of the circle's center
    int sides = 360;
    double radius = 10;
    int x_coord_center = 80;
    int y_coord_center = 40;

    glColor3f (0.5, 0.0, 0.5);
    glBegin (GL_LINE_LOOP);
    //This loop will convert the degrees we go through in the loop into radians
    //then find the cartesian coordiates by using the polar conversion
    //then connect each of these coordiates through-out the 360 degrees
    for(int i = 0; i < sides; i++)
    {
        double rad = i * 3.14159/180;
        double x_coord = x_coord_center + radius * cos(rad);
        double y_coord = y_coord_center + radius * sin(rad);
        glVertex2d(x_coord,y_coord);
    }
    glEnd();
    glFlush();
}

void circle(void)
{
    //the same exact process as above just with a shifted center point
    //also changed to fill the circle
    int sides = 360;
    double radius = 10;
    int x_coord_center = 120;
    int y_coord_center = 40;

    glColor3f (0.5, 0.0, 0.5);
    glBegin (GL_POLYGON);
    for(int i = 0; i < sides; i++)
    {
        double rad = i * 3.14159/180;
        double x_coord = x_coord_center + radius * cos(rad);
        double y_coord = y_coord_center + radius * sin(rad);
        glVertex2d(x_coord,y_coord);
    }
    glEnd();
    glFlush();
}

//Function to sequentially call each shape
//and draw it on the window

void Shapes (void)
{
    unfill_triangle();
    triangle();
    unfill_square();
    square();
    unfill_pentagon();
    pentagon();
    unfill_hexagon();
    hexagon();
    unfill_heptagon();
    heptagon();
    unfill_octagon();
    octagon();
    unfill_circle();
    circle();
}

int main (int argc, char** argv)
{
glutInit (&argc, argv); // Initialize GLUT.
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.

glutInitWindowPosition (500, 250); // Set top-left display-window position.
glutInitWindowSize (1024, 768); // Set display-window width and height.

glutCreateWindow ("Bracewell"); // Create display window.
init ( ); // Execute initialization procedure.
glutDisplayFunc (Shapes); //Draw all the shapes defined above!
glutMainLoop ( ); // Display everything and wait.

return 0;
}
