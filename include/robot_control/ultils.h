#pragma once
#include <iostream>
#ifndef PI
#define PI 3.1415926
#endif
using namespace std;
#define DIVISOR 50.0
// 记录位置信息
struct Location{
    double xr;
    double yr;
    double thetar;
    Location( double x, double y, double theta )
    : xr(x), yr(y), thetar(theta)
    {
    }
    friend ostream& operator<<(ostream& outs, const Location& loc)
    {
        outs << "x: " << loc.xr << " y: " << loc.yr << " theta: " << loc.thetar << endl;
    }
};

// 记录速度信息
struct Speed{
    double wr;
    double vr;
    Speed( double w, double v )
    : wr(w), vr(v) {}
    friend ostream& operator<<(ostream& outs, const Speed& spd)
    {
        outs << "w: " << spd.wr << " v: " << spd.vr << endl;
    }
};

// 记录路径信息
struct PathInfo{
    Location loc;
    Speed    spd;
    PathInfo( double x, double y, double theta, double w, double v )
    : loc( x,y,theta ), spd( w,v )
    {

    }
    friend ostream& operator<<(ostream& outs, const PathInfo& info)
    {
        outs << info.loc;
        outs << info.spd;
    }
};

// 纯虚类-描述轨迹
class Trajectory{
public:
    virtual Location getLocation( double time ) = 0;
    virtual PathInfo getPathInfo( double time ) = 0;        
};

double getAngle( double angle );
Location getLocation( double time );
PathInfo getPathInfo( double time );
double sign( double x );
double siga( double alpha, double x );
