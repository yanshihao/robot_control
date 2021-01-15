/**************************************
 * 功能说明：
 *     本文件的功能是控制机器人在目标的侧面跟随
 * 作者：
 *      晏世豪
 * 时间：
 *      2020年12月23日
 * *************************************/


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <prediction_msg/FutureTrajectory.h>
#include <fstream> 
#include <iostream>
#include <string>
#include <memory>
#include <queue>
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

#define SAMPLE_TIME 0.1429

using namespace std;
class MPCFollowController
: public BaseController
{
public:
    MPCFollowController()
    : BaseController(7)
    , curTime_(0), isStart_(false),trajectory_(new WeightTrajectory), yDesired_(0.3), count_(0)
    , outFile_("/home/nvidia/catkin_new/src/robot_control/recordData/information.txt", ios::app)
    , maxLen_(4), sumAngle_(0)
    {
        futureTraSub_ = nh_.subscribe("/predicted_trajectory", 10, &MPCFollowController::handleFutureTraMsg, this);
        realSpdSub_ = nh_.subscribe( "/real_speed" , 1, &MPCFollowController::handleSpdMsg, this ); 
    }
    virtual void run();
    virtual void init();
    virtual geometry_msgs::Twist controlStrategyOutput();
private:
    float curTime_;  // 相对时间
    shared_ptr<WeightTrajectory> trajectory_;
    float yDesired_;
    bool isStart_;
    void change_input();
    ros::Subscriber futureTraSub_;
    ros::Subscriber realSpdSub_;
    void handleFutureTraMsg( const prediction_msg::FutureTrajectoryPtr futureTraPtr );
    void handleSpdMsg(const geometry_msgs::TwistPtr twistPtr);
    int count_;
    geometry_msgs::Twist realSpd_;
    std::ofstream outFile_;
    std::queue<double> currentAngles_;
    double sumAngle_;
    int maxLen_;
};

void MPCFollowController::handleSpdMsg(const geometry_msgs::TwistPtr twistPtr)
{
    realSpd_ = *twistPtr.get();
}

void MPCFollowController::handleFutureTraMsg( prediction_msg::FutureTrajectoryPtr futureTraPtr )
{
    std::cout << "handleFutureTraMsg" << std::endl;
    isStart_ = true;
    trajectory_->setWeights(ref(futureTraPtr->weights));
    curTime_ = 0;
    count_ = 0;
}

void MPCFollowController::init()
{
    std::cout << "init start" << std::endl;
    ros::Rate loopRate(controlRate_);
    while( ros::ok() )
    {
        ros::spinOnce();
        if( curRobotValid_ == true && controlSignal_ == true && isStart_ == true)
            break;
        std:: cout << curRobotValid_ << controlSignal_ << isStart_ << std::endl;
        loopRate.sleep();
    }
    std::cout << "init ok" << std::endl;
}

void MPCFollowController::run()
{
    ros::Rate loopRate(controlRate_);
    double incTime = 1.0 / controlRate_;
    init();
    while( ros::ok() && rtmGetErrorStatus(Adaptive_M) == (NULL) && controlSignal_ == true )
    {
        ros::spinOnce();
        geometry_msgs::Twist output = controlStrategyOutput();
        controlSpeedPub_.publish(output);
        std::cout <<"计算速度" << output.angular.z << "   " << output.linear.x << std::endl;
        std::cout <<"真实速度" << realSpd_.angular.z << "   " << realSpd_.linear.x << std::endl;
        loopRate.sleep();
        count_ ++;
        if( count_ > 5 )
            break;
        //curTime_ += incTime;
    }
    outFile_.close();
}

geometry_msgs::Twist MPCFollowController::controlStrategyOutput()
{   
    std::cout << " curTime_ : " << curTime_ << std::endl;
    Location loc = trajectory_->getLocation( curTime_ );
    double xr = loc.xr;
    double yr = loc.yr;
    double thetar = 0;
    if( currentAngles_.empty() )
    {
        currentAngles_.push(loc.thetar);
        thetar =  getAngle(loc.thetar);
    }
    else
    {
        double preAngle = currentAngles_.front();
        while( loc.thetar - preAngle > PI )
            loc.thetar -= 2*PI;
        while( loc.thetar - preAngle < -PI )
            loc.thetar += 2*PI;
        sumAngle_ += loc.thetar;
        currentAngles_.push(loc.thetar);
        if( maxLen_ >= currentAngles_.size() )
            thetar =  getAngle(sumAngle_ / currentAngles_.size());
        else
        {
            sumAngle_ -= currentAngles_.front();
            currentAngles_.pop();
            thetar = getAngle(sumAngle_ / maxLen_);
        }
    }
    std::cout << " xr : " << xr << " yr : " << yr << " thetar: " << thetar << std::endl;
    geometry_msgs::Pose2D& q = curRobotPosition_;
    real_T x[3];
	real_T y[3];
	x[0] = cos(q.theta) * (xr - q.x) + sin(q.theta) * (yr -q.y);
    x[1] = (-1.0) * sin(q.theta) * (xr - q.x) + cos(q.theta) * (yr -q.y) - yDesired_;
    x[2] = getAngle(thetar - q.theta);
	y[0] = x[0];
	y[1] = x[1];
	y[2] = x[2];
    
	Adaptive_U.moorx[0]=y[0] ;
	Adaptive_U.moorx[1]=y[1] ;
	Adaptive_U.moorx[2]=y[2] ;

	printf("%f %f %f\n", y[0], y[1], y[2]);
	Adaptive_U.ref[0] = 0;
	Adaptive_U.ref[1] = 0;
	Adaptive_U.ref[2] = 0;
    
	Adaptive_U.umin[0] = -0.8;
	Adaptive_U.umin[1] = -0.5;
	Adaptive_U.umax[0] = 0.8;
	Adaptive_U.umax[1] = 0.5;
	Adaptive_U.ymin[0] = -0.5;
	Adaptive_U.ymin[1] = -0.5;
	Adaptive_U.ymin[2] = -1;
	Adaptive_U.ymax[0] = 0.5;
	Adaptive_U.ymax[1] = 0.5;
	Adaptive_U.ymax[2] = 1;
	/*
    Adaptive_U.umin[0] = -2;
	Adaptive_U.umin[1] = -2;
	Adaptive_U.umax[0] = 2;
	Adaptive_U.umax[1] = 2;
	Adaptive_U.ymin[0] = -2;
	Adaptive_U.ymin[1] = -2;
	Adaptive_U.ymin[2] = -2;
	Adaptive_U.ymax[0] = 2;
	Adaptive_U.ymax[1] = 2;
	Adaptive_U.ymax[2] = 2;
    */
    /*
    Adaptive_U.ywt[0] = 20;
	Adaptive_U.ywt[1] = 40;
	Adaptive_U.ywt[2] = 17;
	Adaptive_U.duwt[0] = 100;
	Adaptive_U.duwt[1] = 100;
    */
    
    // 好参数
    Adaptive_U.ywt[0] = 25;
	Adaptive_U.ywt[1] = 40;
	Adaptive_U.ywt[2] = 20;
	Adaptive_U.duwt[0] = 30;
	Adaptive_U.duwt[1] = 20;
    
    Adaptive_DW.last_mv_DSTATE[0] = realSpd_.linear.x;
    Adaptive_DW.last_mv_DSTATE[1] = realSpd_.angular.z;
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
		Adaptive_U.B[6 * i] = (-1 + yDesired_)*SAMPLE_TIME;
		Adaptive_U.B[6 * i + 5] = -SAMPLE_TIME;
		Adaptive_U.C[9 * i] = 1;
		Adaptive_U.C[9 * i + 4] = 1;
		Adaptive_U.C[9 * i + 8] = 1;
	}
    for (int i = 0; i < 16; i++)
	{
        PathInfo pathinfo = trajectory_->getPathInfo( curTime_ );
		double wr = pathinfo.spd.wr;
        double vr = pathinfo.spd.vr;
        Adaptive_U.X[3 * i + 1] = yDesired_;
        Adaptive_U.Y[3 * i + 1] = yDesired_;
        Adaptive_U.U[2 * i + 0] = wr * yDesired_ + vr * cos(x[2]);
        Adaptive_U.U[2 * i + 1] = wr;
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
	//speed.linear.x = Adaptive_Y.mv[0] + vr * cos(thetar-q.theta) + wr*yDesired_;
	//speed.angular.z = Adaptive_Y.mv[1] + wr;
    speed.linear.x = Adaptive_Y.mv[0];
	speed.angular.z = Adaptive_Y.mv[1];
    outFile_ << xr <<" " << yr << " " << thetar << " ";
    outFile_ << q.x << " " << q.y << " " << q.theta << " ";
    outFile_ << speed.linear.x << " " << speed.angular.z << " ";
    outFile_ << realSpd_.linear.x << " " << realSpd_.angular.z << " ";
    outFile_ << x[0] << " " << x[1] << " " << x[2] << std::endl;
    return speed;
}


int main( int argc, char** argv )
{
    ros::init(argc,argv,"MPCFollowControll");   
    MPCFollowController controller;
    controller.run();
    return 0;
}
