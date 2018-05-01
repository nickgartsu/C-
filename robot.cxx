// File: robot.cxx
// Written by Michael Main (main@colorado.edu)
// This program illustrates a draw_robot function with and
// without parameters.

// Directives:
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <graphics.h>
using namespace std;

// Named constants:
const int S = 442;
const int FRAMES_PER_SEC = 30;
const double FOOT_FREQ = 7.0;

const double MAX_SEPARATION = S/15.0;

// Prototypes:
void draw_robot(
    double x, double y, double d, double foot_separation,
    int body_color
    );

// Function definitions:
//----------------------------------------------------------
int main( )
{
    double t = 0; // time in seconds
    double x = 0, y = 0; // starting point for robot
    double foot_separation = MAX_SEPARATION;
    int c;
    
    initwindow(S, S, "I, Robot", 0, 0, true);

    while(true)
    {
	// step 1: calculate info for next frame
	t += 1.0/FRAMES_PER_SEC;
	x = 20*t;
	y = 0.8*S - pow((0.5/(t-8)),4);
	foot_separation = MAX_SEPARATION*cos(FOOT_FREQ*t);
	c = COLOR(
	    int(100*cos(t)+150),
	    int(100*sin(2*t)+150),
	    int(100*sin(4*t)+150));
	
        // step 2: draw the next frame
	clearviewport();
	draw_robot(x, y, S/20, foot_separation, c);

	// step 3: swap buffers and delay
	swapbuffers();
	delay(1000/FRAMES_PER_SEC);

    }
    delay(42000);
    
    return EXIT_SUCCESS;
}
//----------------------------------------------------------

//----------------------------------------------------------
void draw_robot(
    double x, double y, double d, double foot_separation,
    int body_color
    )
{
    // Draw the body
    setfillstyle(SOLID_FILL, body_color);
    bar(int(x - d), int(y - d), int(x + d), int(y + d));

    // Draw the head above the body
    circle(int(x), int(y - 2*d), int(d));

    // Draw the legs, which start from a new (x,y) and go
    // downward from there.
    line(int(x), int(y + d), int(x - foot_separation/2), int(y + 2*d)); // back
    line(int(x), int(y + d), int(x + foot_separation/2), int(y + 2*d)); // front
}
//----------------------------------------------------------
