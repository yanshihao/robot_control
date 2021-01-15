/**************************************
 * 功能说明：
 *     本文件的功能是控制机器人跟随某个确定轨迹运动
 * 作者：
 *      晏世豪
 * 时间：
 *      2020年10月15日
 * *************************************/
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>
#include <string>
#include <memory>
#include "../include/robot_control/Controller.h"
#include "../include/robot_control/ultils.h"
#include "Trajectory.hpp"
#include <cmath>
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */

extern "C"{
    #include "mpcbase/Adaptive.h"                  /* Model's header file */
    #include "mpcbase/rtwtypes.h"
} 

#define SAMPLE_TIME 0.1

using namespace std;
class MPCTraController
: public BaseController
{
public:
    MPCTraController()
    : curTime_(0)
    {

    }
    virtual void run();
    virtual void init();
    virtual geometry_msgs::Twist controlStrategyOutput();
private:
    float curTime_;                       // 当前时间 
    shared_ptr<Trajectory> trajectory_;
};

void MPCTraController::init()
{
    BaseController::init();
    //trajectory_.reset(new LineTrajectory(0,0,0,0.3));
    //trajectory_.reset(new ReverseCircleTrajectory(0,0,0,1,0.25));
    //trajectory_.reset(new TurningLeftTrajectory(0.35,1,3,0.3,PI/9,3));
    trajectory_.reset(new TurningLeftTrajectory2);
}

geometry_msgs::Twist MPCTraController::controlStrategyOutput()
{
    std::cout << " curTime_ : " << curTime_ << std::endl;
    Location loc = trajectory_->getLocation( curTime_ );
    double xr = loc.xr;
    double yr = loc.yr;
    double thetar = loc.thetar;
    std::cout << " xr : " << xr << " yr : " << yr << " thetar: " << thetar << std::endl;
    geometry_msgs::Pose2D& q = curRobotPosition_;
    real_T x[3];
	real_T y[3];
	x[0] = cos(q.theta) * (xr - q.x) + sin(q.theta) * (yr -q.y);
    x[1] = (-1.0) * sin(q.theta) * (xr - q.x) + cos(q.theta) * (yr -q.y);
    x[2] = getAngle(thetar - q.theta);
	y[0] = x[0];
	y[1] = x[1];
	y[2] = x[2];

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
        PathInfo pathinfo = trajectory_->getPathInfo( curTime_ + i * SAMPLE_TIME );
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
    static boolean_T OverrunFlag = false;
    if (OverrunFlag) {
        rtmSetErrorStatus(Adaptive_M, "Overrun");
        return geometry_msgs::Twist();
    }
    OverrunFlag = true;
    Adaptive_step();
    OverrunFlag = false;

    PathInfo info = trajectory_->getPathInfo( curTime_ );
    double vr = info.spd.vr;
    double wr = info.spd.wr;
    thetar = info.loc.thetar;
    geometry_msgs::Twist speed;
	speed.linear.x = Adaptive_Y.mv[0] + vr * cos(thetar-q.theta);
	speed.angular.z = Adaptive_Y.mv[1] + wr;
    return speed;
}

void MPCTraController::run()
{
    ros::Rate loopRate(controlRate_);
    double incTime = 1.0 / controlRate_;
    init();
    while( ros::ok() && rtmGetErrorStatus(Adaptive_M) == (NULL) && controlSignal_ == true )
    {
        ros::spinOnce();
        
        geometry_msgs::Twist output = controlStrategyOutput();

        controlSpeedPub_.publish(output);
        loopRate.sleep();
        curTime_ += incTime;
        std::cout << "curTime = " << curTime_ << std::endl;
    }
}

int main( int argc, char** argv )
{
    ros::init(argc,argv,"MPCTraTrackControl");   
    MPCTraController controller;
    controller.run();
    return 0;
}
