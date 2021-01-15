#include "../include/robot_control/ultils.h"
#include <cmath>

double getAngle( double angle )
{
    while( angle > PI ) angle -= 2*PI;
    while( angle < -PI ) angle += 2*PI;
    return angle;
}

Location getLocation( double time )
{
    double xr = 1.1 + 0.7 * sin(2 * PI * time / DIVISOR);
	double yr = 0.9 + 0.7 * sin(4 * PI * time / DIVISOR);
	double xr_dot = 0.7 * cos(2 * PI * time / DIVISOR) * 2.0 * PI / DIVISOR;
	double yr_dot = 0.7 * cos(4 * PI * time / DIVISOR) * 4.0 * PI / DIVISOR;
	double thetar = atan2(yr_dot, xr_dot);
    return Location( xr, yr, thetar );
}

PathInfo getPathInfo( double time )
{
    double xr = 1.1 + 0.7 * sin(2 * PI * time / DIVISOR);
    double yr = 0.9 + 0.7 * sin(4 * PI * time / DIVISOR);
    double xr_dot = 0.7 * cos(2 * PI * time / DIVISOR) * 2.0 * PI / DIVISOR;
    double yr_dot = 0.7 * cos(4 * PI * time / DIVISOR) * 4.0 * PI / DIVISOR;
    double thetar = atan2(yr_dot, xr_dot);
    double xr_dot_dot = -0.7 * sin(2 * PI * time / DIVISOR) * 2 * PI / DIVISOR * 2 * PI / DIVISOR;
    double yr_dot_dot = -0.7 * sin(4 * PI * time / DIVISOR) * 4 * PI / DIVISOR * 4 * PI / DIVISOR;
    double vr = sqrt(xr_dot * xr_dot + yr_dot * yr_dot);    
    double wr = (xr_dot * yr_dot_dot - yr_dot * xr_dot_dot) / (xr_dot * xr_dot + yr_dot * yr_dot);
    return PathInfo( xr,yr,thetar, wr, vr );
}

double sign( double x )
{
    if( x > 0 ) return 1;
    else return -1;
}

double siga( double alpha, double x )
{
    return pow(fabs(x), alpha) * sign(x);
}
