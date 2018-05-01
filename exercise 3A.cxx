// Directives:
#include <cassert>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <graphics.h>
using namespace std;

const int S = 400;

// proto
void shade(double t);

int main()
{

    initwindow (S, S);
    
    for(double(t)=-12; t<=12; t+=.25)
	shade (t);

    clearviewport( );
    bgiout << t;
    outstreamxy(S/2, S/2);
    delay(250);

}

void shade(double t)
{
    putpixel(int(px),int(py),int(color));
    double denominator = 2 * S;
    for(t <= 0)
    {
	blue_amount = int(255 * pow((S + py - px)/denominator, -t/6.0));
    }
    for(t >= 0)
    {
	int(255 * pow((py + px)/denominator, t/6.0));
    }
    color = COLOR(0, 0, blue_amount);
}
	

void shade(t)
{
    for(px...) // 0 ----> S
    {
    } 
    for(py...)
    {
	if()
	{
	}
	color = ...
	putpicel(px, py, color)
	}
}
