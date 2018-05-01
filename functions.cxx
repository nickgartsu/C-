// File: functions.cxx (Sept 23, 2011)
// Written by Greg Gartsu, greg.gartsu@colorado.edu
// This program is a short interactive program that lets a user calculate
// solutions for five different functions.

// Directives:
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

// Named constants:
const double EPSILON = 0.001;

//-----------------------------------------------------------------------------
// Function Prototypes

// sr(double z)--- This function uses the iterative technique shown in
// class to find a value of x that is very close to solving the
// equation: x = 0.5(x + z/x)
// As we did in class, the while-loop stops when the error in x is
// less than 0.001. Notes: The initial guess for the equation must be
// 1.0. The input parameter, z, must be positive. The answer should be
// close to the square root of z.
double sr(double z);

// pixel(wx, w0, w1, p0, p1) converts wx from an interval that ranges from w0 to
// w1 into an integer interval that ranges from p0 to p1.
// Note that when wx = w0,
// the answer is always p0, and when wx = w1, the answer is always p1.
// Example 1: Suppose an x-coordinate called x ranges from -2 (on the left
// side of the screen) to +3 (on the right side of the screen), and
// we want to figure out the corresponding pixel x coordinate for a screen
// that is 400 pixel wide. Then call pixel(x, -2, 3, 0, 400).
// Example 2: Suppose a y-coordinate called y ranges from +4 (on the top
// of the screen) to -2 (on the bottom of the screen), and
// we want to figure out the corresponding pixel y coordinate for a screen
// that is 300 pixels tall. Then call pixel(y, 4, -2, 0, 300). Note that in this
// case w0 > w1 since we want bigger coordinates at the top of the screen.
int pixel(double wx, double w0, double w1, int p0, int p1);

// A function to calculate the solution to Kepler's equation. The equation is
// x = ma + ecc*sin(x), and the answer returned is x, within EPSILON.
double kepler_solution(double ma, double ecc);

// orbit_angle(ecc, period, t) computes the angle of a planet's position
// in polar coordinates at time t.  ecc is the ecentricity of the orbit,
// and period is the time for one full orbit.  period and t must be in the
// same units.
double orbit_angle(double ecc, double period, double t);

// orbit_dist(a, ecc, theta) computes the distance of a planet
// from the sun when it is at angle theta in polar coordinates.
// a is the semi-major axis; ecc is the orbit's eccentricity.  The units
// of the answer are the same as the units of a.
double orbit_dist(double a, double ecc, double theta);
//-----------------------------------------------------------------------------
// ^^^^ Michael Main's version of pixel code  ^^^^


//-----------------------------------------------------------------------------
int main()
{
    double ma, ecc; // to test kepler_solutions
    double period, t; // to test orbit angle
    double a, theta; // to test orbit dist
    double wx, w0, w1; // to test pixel
    int p0, p1; // to test pixel
    double z; // to test sr
    
    cout << "Please type ma and ecc for testing kepler_solution: ";
    cin >> ma >> ecc;
    cout << "kepler_solution is "
	 << kepler_solution(ma , ecc) << endl;
    cout << "Please type ecc, period and t for testing orbit_angle: ";
    cin >> ecc >> period >> t;
    cout << "orbit_angle is "
	 << orbit_angle(ecc, period, t) << endl;
    cout << "Please type a, ecc and theta for testing orbit_dist: ";
    cin >> a >> ecc >> theta;
    cout << "orbit_dist is "
         << orbit_dist(a, ecc, theta) << endl;
    cout << "Please type wx, w0, w1, p0 and p1 for testing pixel: ";
    cin >> wx >> w0 >> w1 >> p0 >> p1;
    cout << "pixel is "
    	 << pixel(wx, w0, w1, p0, p1) << endl;
    cout << "Please type z for testing sr: ";
    cin >> z;
    cout << "the square root of z is approximately "
         << sr(z) << endl;
    cout << "Thank you, Mr. Kepler. ";
    
    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
double kepler_solution(double ma, double ecc)
{

    double x = 0;
    double right = ma + ecc*sin(x); // equation for orbit of a plant
    double diff = abs(right - x);
    while (diff >= EPSILON)
    {
	x = right;
	right = ma + ecc*sin(x);
	diff = abs(right - x);
    }
    return x;
    
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
double orbit_angle(double ecc, double period, double t)
{
    double ma = 2*M_PI*t/period;
    double x = kepler_solution(ma, ecc);
    return 2*atan(sqrt((1+ecc)/(1-ecc))*tan(x/2));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
double orbit_dist(double a, double ecc, double theta)
{
    return a*(1-ecc*ecc)/(1+ecc*cos(theta));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
double sr(double z)
{
    double x = 200;
    double right = 0.5*(x + z/x);
    double diff = abs(right - x);
    while (diff > 0.0001)
    {
	x = right;
	right =  0.5*(x + z/x);
	diff = abs(right - x);
    }
    return x;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int pixel(double wx, double w0, double w1, int p0, int p1)
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
// "Int pixel" coding from Main's android.cxx
//-----------------------------------------------------------------------------
