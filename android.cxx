// File: robot.cxx
// Written by Michael Main (main@colorado.edu) and TAs!
// This program illustrates a draw_robot function with
// animation.

// Directives:
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <graphics.h>
using namespace std;

//----------------------------------------------------------
// Named constants:
const int S = 442; // Graphics screen width and height (pixels)
const int FRAMES_PER_SEC = 30; // Rate of animation
const double W_MAX = +4.0; // Maximum world coordinate 
const double W_MIN = -4.0; // Minimum world coordinate 

// The size of the robot is controlled by these constants,
// all of which are in pixels. The ROBOT_SIZE is the d
// parameter for draw_robot, and it controls the sizes of
// most things. MAX_SEP is the maximum distance that the
// feet travel horizontally from the center of the robot.
// I chose int for these because they are measured in
// pixels.
const int ROBOT_SIZE = 20;  
const int MAX_SEP = S/15;

// The robot's periodic movement is defined by these two
// constants. FREQ_FEET is the number of repetitions
// of the back-and-forth foot motion in 2*pi seconds.
// FREQ_POSITION is the number of number of times that the
// robot's x and y positions go back and forth across the
// entire screen in 2*pi seconds.
// of the motion in 2*pi seconds. MAX_SEP is the maximum
// distance that the feet travel horizontally from the center
// of the robot.
const double FREQ_FEET = 3.5;      // per 2*pi seconds
const double FREQ_POSITION = 2.1;  // per 2*pi seconds
//----------------------------------------------------------


//----------------------------------------------------------
// Prototypes:
// Draw a robot on the screen. All parameters are measured
// in pixels. (px,py) is the coordinate of the center of
// the robot. The value of d determines various distances,
// such as the radius of the head. The foot_sep is the
// distance of the feet from the horizontal center of the
// robot.
void draw_robot(
    int px, int py, int d, int foot_sep
    );

// This function returns the value of a periodic function
// that is computed from t (in seconds). The return values
// range from a low of (base - amplitude) to a high of
// (base + amplitude). The pattern of return values is
// repeated omega times in every 2*pi seconds (so that
// omega is a measure of frequency per 2*pi seconds).
double periodic_value(
    double t, double amplitude, double omega, double base
    );

// This function converts a world coordinate (wx) to a
// pixel coordinate. The range of world coordinates
// that we consider are from w0 (on the left or top of
// the displayed area) to w1 (on the right or bottom of
// the displayed area). The range of possible pixels is
// from p0 (on the left or top) to p1 (on the right or
// bottom).
int pixel(
    double wx, double w0, double w1, int p0, int p1
    );
//----------------------------------------------------------


//----------------------------------------------------------
int main( )
{
    double t = 0;  // current time in seconds
    double wx, wy; // robot position in world coordinates
    int px, py;    // robot position in pixel coordinates
    int foot_sep;  // dist. of feet from center (pixels)
    
    initwindow(S, S, "I, Robot", 0, 0, true);

    while(true)
    {
	// step 0: calculate info for next frame.
	wx = periodic_value(t, W_MAX, FREQ_POSITION, 0);
	foot_sep = int(periodic_value(t, MAX_SEP, FREQ_FEET, 0));
	wy = periodic_value(
	    t + (M_PI/2)*(1/FREQ_POSITION), // Alter phase by pi/2
	    W_MAX/2, // Amplitude is only half the screen
	    FREQ_POSITION, // Same frequency as x coordinate
	    W_MAX/10       // And shift the base up a bit
	    );
	t += 1.0/FRAMES_PER_SEC;
	
        // step 1: draw the next frame
	clearviewport();
        px = pixel(wx, W_MIN, W_MAX, 0, S);
        py = pixel(wy, W_MAX, W_MIN, 0, S);
	draw_robot(px, py, ROBOT_SIZE, foot_sep);

	// step 2: swap buffers and delay
	swapbuffers();
	delay(1000/FRAMES_PER_SEC);

    }
    delay(42000);
    
    return EXIT_SUCCESS;
}
//----------------------------------------------------------

//----------------------------------------------------------
void draw_robot(
    int px, int py, int d, int foot_sep
    )
{
    // Some pixel values for sizes of things in the robot:
    const int ARM_OFFSET = 6;
    const int ARM_SPACING = 2;
    const int ARM_HEIGHT = 10;

    // Draw the head above the body
    fillellipse(px, py - d, d, d);

    // Draw the Android body
    if(px < S/2)
    {
	setfillstyle(SOLID_FILL, COLOR(165, 198, 59));
    }
    else
    {
	setfillstyle(SOLID_FILL, MAGENTA);
    }
    bar(px - d, py - d, px + d, py + d);

    // Draw the Android arms
    bar(
	px - d - ARM_OFFSET - ARM_SPACING, py - d,
	px - d - ARM_SPACING, py + d - ARM_HEIGHT
	);
    bar(
	px + d + ARM_OFFSET + ARM_SPACING, py - d,
	px + d + ARM_SPACING, py + d - ARM_HEIGHT
	);

    // Draw the legs, which start from the bottom of the
    // body and go downward from there.
    line(px, py + d, px - foot_sep/2, py + 2*d);
    line(px, py + d, px + foot_sep/2, py + 2*d);
}
//----------------------------------------------------------


//----------------------------------------------------------
double periodic_value(
    double t, double amplitude, double omega, double base
    )
{
    return amplitude*cos(omega*t) + base;
}
//----------------------------------------------------------


//----------------------------------------------------------
int pixel(
    double wx, double w0, double w1, int p0, int p1
    )
{
    // Sizes of the parts of the two coordinate systems
    // that we are using:
    double world_width = w1 - w0; 
    double pixel_width = p1 - p0;

    // How far across the world coordinate system is wx?
    double fraction = (wx - w0)/world_width;

    // Convert that fraction to the corresponding spot in
    // the pixel coordinate system:
    return int(p0 + fraction*pixel_width);
}
//----------------------------------------------------------


