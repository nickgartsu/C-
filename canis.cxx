// File: canis.cxx (Sept 2, 2011)
// Written by Greg Gartsu, greg.gartsu@colorado.edu
// This programs drawes five equilateral triangles in the same
// positions as the fivebrightest stars in the constellation Canis Major.

//Directives:
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <graphics.h>

//Named constants:
const int S = 500; //Width and height of the graphics window.
const double PI = 3.14159;

//Prototypes:
void draw_triangle(int x, int y, int d, double theta);

//Function Definitions:
//----------------------------------------------------------
int main()
{
    // 1. Initialize the graphics:
    initwindow(S, S, "Canis Major");
//----------------------------------------------------------
    // 2. Draw 5 triangles:
    draw_triangle(int(.0725*S), int(.75*S), int(.01*S), M_PI/2);
    draw_triangle(S/4, int(.625*S), int(.015*S), M_PI/2);
    draw_triangle(int(.375*S), int(0.72*S), int(.03*S), M_PI/2);
    draw_triangle(int(.875*S), int(0.26*S), int(.02*S), M_PI/2);
    draw_triangle(int(0.55*S), int(0.2*S), int(.05*S), M_PI/2);
//----------------------------------------------------------
    // 3. Pause for 2 seconds:
    delay(2000); //pause for 2 seconds
//----------------------------------------------------------
    // 4. Draw 5 upside down triangles
    draw_triangle(int(.0725*S), int(.75*S), int(.01*S), 3*M_PI/2);
    draw_triangle(S/4, int(.625*S), int(.015*S), 3*M_PI/2);
    draw_triangle(int(.375*S), int(0.72*S), int(.03*S), 3*M_PI/2);
    draw_triangle(int(.875*S), int(0.26*S), int(.02*S), 3*M_PI/2);
    draw_triangle(int(0.55*S), int(0.2*S), int(.05*S), 3*M_PI/2);
//----------------------------------------------------------
    // 5. Finish:
    delay(20000); //pause for 20 seconds
    return EXIT_SUCCESS;
}

//----------------------------------------------------------
void draw_triangle(int x, int y, int d, double theta)
{
    int x1 = int(x + d*cos(theta)); //x-coordinate of the top point
    int y1 = int(y - d*sin(theta)); //y-coordinate of the top point
    int x2 = int(x + d*cos(theta + 2*M_PI/3));
    int y2 = int(y - d*sin(theta + 2*M_PI/3));		     
    int x3 = int(x + d*cos(theta - 2*M_PI/3));
    int y3 = int(y - d*sin(theta - 2*M_PI/3));
    line(x1,y1,x2,y2); //connects top point to the lower left point
    line(x2,y2,x3,y3); 
    line(x3,y3,x1,y1);
}
