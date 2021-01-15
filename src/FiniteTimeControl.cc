/**************************************
 * 功能说明：
 *     本文件的功能是控制机器人跟随某个确定轨迹运动
 *     有限时间控制
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
#include "../include/robot_control/Controller.h"
#include "../include/robot_control/ultils.h"
#include <cmath>

#define SAMPLE_TIME 0.1
// x: 1.1 y: 0.9 theta: 1.10715
// w: 0 v: 0.327825
class FiniteTimeController
: public BaseController
{
public:
    FiniteTimeController():
    curTime_(0), k1_(5), k2_(2) , k3_(2),
    alpha1_(0.6), alpha2_(0.75), alpha3_(0.6)
    {

    }
    virtual void run();
    virtual geometry_msgs::Twist controlStrategyOutput();
private:
    float curTime_;                       // 当前时间 
    float k1_, k2_, k3_;
    float alpha1_, alpha2_, alpha3_;
};

geometry_msgs::Twist FiniteTimeController::controlStrategyOutput()
{
    std::cout << " curTime_ : " << curTime_ << std::endl;
    PathInfo info = getPathInfo( curTime_ );
    double xr = info.loc.xr;
    double yr = info.loc.yr;
    double thetar = info.loc.thetar;
    double wr = info.spd.wr;
    double vr = info.spd.vr;
    std::cout << info;
    geometry_msgs::Pose2D& q = curRobotPosition_;
    float x[3];
    x[0] = cos(q.theta) * (xr - q.x) + sin(q.theta) * (yr -q.y);
    x[1] = (-1.0) * sin(q.theta) * (xr - q.x) + cos(q.theta) * (yr -q.y);
    x[2] = thetar - q.theta;
    cout << "e[0] : " << x[0] << " e[1] :" << x[1] << " e[2] : " << x[2] << endl;
    geometry_msgs::Twist speed;
    speed.angular.z = wr + k3_ * siga(alpha3_, x[2]);
    speed.linear.x = vr + wr * x[1] - k1_* wr * siga(alpha1_, x[1]) + k2_ * siga(alpha2_, x[0]);
    return speed;
}

void FiniteTimeController::run()
{
    ros::Rate loopRate(controlRate_);
    double incTime = 1.0 / controlRate_;
    init();
    while( ros::ok() )
    {
        ros::spinOnce();
        geometry_msgs::Twist output = controlStrategyOutput();
        controlSpeedPub_.publish(output);
        loopRate.sleep();
        curTime_ += incTime;
    }
}

int main( int argc, char** argv )
{
    ros::init(argc,argv,"testControl");   
    FiniteTimeController controller;
    controller.run();
}