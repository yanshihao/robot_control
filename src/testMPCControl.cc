#include <iostream>
#include <cmath>
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */

//#define GET_TIME

#ifdef GET_TIME
#include <chrono>
#endif

extern "C"{
    #include "mpcbase/Adaptive.h"                  /* Model's header file */
    #include "mpcbase/rtwtypes.h"
} 

#ifndef PI
#define PI 3.1415926
#endif
#define SAMPLE_TIME 0.1


// 记录位置信息
struct Location{
    double xr;
    double yr;
    double thetar;
    Location( double x, double y, double theta )
    : xr(x), yr(y), thetar(theta)
    {
    }
};

// 记录速度信息
struct Speed{
    double wr;
    double vr;
    Speed( double w, double v )
    : wr(w), vr(v) {}
};

// 记录路径信息
struct PathInfo{
    Location loc;
    Speed    spd;
    PathInfo( double x, double y, double theta, double w, double v )
    : loc( x,y,theta ), spd( w,v )
    {

    }
};


static Location getLocation( double time )
{
    double xr = 1.1 + 0.7 * sin(2 * PI * time / 30);
	double yr = 0.9 + 0.7 * sin(4 * PI * time / 30.0);
	double xr_dot = 0.7 * cos(2 * PI * time / 30.0) * 2.0 * PI / 30.0;
	double yr_dot = 0.7 * cos(4 * PI * time / 30.0) * 4.0 * PI / 30.0;
	double thetar = atan2(yr_dot, xr_dot);
    return Location( xr, yr, thetar );
}

static PathInfo getPathInfo( double time )
{
    double xr = 1.1 + 0.7 * sin(2 * PI * time / 30);
    double yr = 0.9 + 0.7 * sin(4 * PI * time / 30.0);
    double xr_dot = 0.7 * cos(2 * PI * time / 30.0) * 2.0 * PI / 30.0;
    double yr_dot = 0.7 * cos(4 * PI * time / 30.0) * 4.0 * PI / 30.0;
    double thetar = atan2(yr_dot, xr_dot);
    double xr_dot_dot = -0.7 * sin(2 * PI * time / 30.0) * 2 * PI / 30 * 2 * PI / 30.0;
    double yr_dot_dot = -0.7 * sin(4 * PI * time / 30.0) * 4 * PI / 30 * 4 * PI / 30.0;
    double vr = sqrt(xr_dot * xr_dot + yr_dot * yr_dot);    
    double wr = (xr_dot * yr_dot_dot - yr_dot * xr_dot_dot) / (xr_dot * xr_dot + yr_dot * yr_dot);
    return PathInfo( xr,yr,thetar, wr, vr );
}


static real_T q[3] = {0.8,0.8,0.6071};
//real_T q[3] = {0.8,0.8,0.5};
static float count_time = 0.0;

static void rt_OneStep(void);
static void change_state(void);
static void change_input(void);

void change_input(void)
{
	Location loc = getLocation( count_time );
    double xr = loc.xr;
    double yr = loc.yr;
    double thetar = loc.thetar;
    real_T x[3];
	real_T y[3];
	x[0] = cos(q[2]) * (xr - q[0]) + sin(q[2]) * (yr -q[1]);
    x[1] = (-1.0) * sin(q[2]) * (xr - q[0]) + cos(q[2]) * (yr -q[1]);
    x[2] = thetar - q[2];
	y[0] = x[0];
	y[1] = x[1];
	y[2] = x[2] ;

	Adaptive_U.moorx[0]=y[0] ;
	Adaptive_U.moorx[1]=y[1];
	Adaptive_U.moorx[2]=y[2] ;

	printf("%f %f %f\n", y[0], y[1], y[2]);
	Adaptive_U.ref[0] = 0;
	Adaptive_U.ref[1] = 0;
	Adaptive_U.ref[2] = 0;
	Adaptive_U.umin[0] = -2.0;
	Adaptive_U.umin[1] = -1;
	Adaptive_U.umax[0] = 2.0;
	Adaptive_U.umax[1] = 1;
	Adaptive_U.ymin[0] = -2.0;
	Adaptive_U.ymin[1] = -2.0;
	Adaptive_U.ymin[2] = -1.57;
	Adaptive_U.ymax[0] = 2.0;
	Adaptive_U.ymax[1] = 2.0;
	Adaptive_U.ymax[2] = 1.57;
	Adaptive_U.ywt[0] = 1.0;
	Adaptive_U.ywt[1] = 1.0;
	Adaptive_U.ywt[2] = 10;
	Adaptive_U.duwt[0] = 0.1;
	Adaptive_U.duwt[1] = 0.1;

	for (int i = 0; i < 16; i++)
	{
        PathInfo pathinfo = getPathInfo( count_time + i * SAMPLE_TIME );
		double wr = pathinfo.spd.wr;
        double vr = pathinfo.spd.vr;

		Adaptive_U.A[9 * i] = 1;
		Adaptive_U.A[9 * i + 4] = 1;
		Adaptive_U.A[9 * i + 8] = 1;
		Adaptive_U.A[9 * i + 1] = SAMPLE_TIME * wr;
		Adaptive_U.A[9 * i + 3] = -SAMPLE_TIME * wr;
		Adaptive_U.A[9 * i + 5] = SAMPLE_TIME * vr;
		Adaptive_U.B[6 * i] = -SAMPLE_TIME;
		Adaptive_U.B[6 * i + 5] = -SAMPLE_TIME;
		Adaptive_U.C[9 * i] = 1;
		Adaptive_U.C[9 * i + 4] = 1;
		Adaptive_U.C[9 * i + 8] = 1;
	}
}

void change_state(void)
{
	PathInfo info = getPathInfo( count_time );
    double vr = info.spd.vr;
    double wr = info.spd.wr;
    double thetar = info.loc.thetar;
    real_T real_U[2];
	real_U[0] = Adaptive_Y.mv[0] + vr * cos(thetar-q[2]);
	real_U[1] = Adaptive_Y.mv[1] + wr;
	q[0] =q[0] + cos(q[2]) * SAMPLE_TIME * real_U[0];
	q[1] = q[1] + sin(q[2]) * SAMPLE_TIME * real_U[0];
	q[2] =q[2] + real_U[1] * SAMPLE_TIME;

	if (q[2] > PI)
		q[2] = q[2] - 2 * PI;

	if (q[2] < -PI)
		q[2] = q[2] + 2 * PI;
}

void rt_OneStep(void)
{
    static boolean_T OverrunFlag = false;
    if (OverrunFlag) {
        rtmSetErrorStatus(Adaptive_M, "Overrun");
        return;
    }
    OverrunFlag = true;
    Adaptive_step();
    OverrunFlag = false;
}

using namespace std;
int_T main(int_T argc, const char *argv[])
{
    int j = 0;
    Adaptive_initialize();
    printf("Warning: The simulation will run forever. "
            "Generated ERT main won't simulate model step behavior. "
            "To change this behavior select the 'MAT-file logging' option.\n");
    fflush((NULL));
    while (rtmGetErrorStatus(Adaptive_M) == (NULL)) {
        #ifdef GET_TIME
        chrono::steady_clock::time_point time_start = chrono::steady_clock::now();
        #endif
        change_input();
        Adaptive_step();
        printf("%f \n", count_time);

        change_state();
        count_time = count_time + SAMPLE_TIME;
        j++;
        
        #ifdef GET_TIME
        chrono::steady_clock::time_point time_end = chrono::steady_clock::now();
        chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(time_end - time_start);
        cout << "time use:" << time_used.count() << "s" << endl;
        #endif
        // use:0.000543915s
        if (j == 500)
        {
            break;
        }
    }
    Adaptive_terminate();
    return 0;
}