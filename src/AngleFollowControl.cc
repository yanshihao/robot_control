/**********************************************
 * 作用：
 *     控制机器人旋转并对准目标
 *     首先要派生了一个具体的控制对象
 * 作者：晏世豪
 * 时间：2020年10月8日
 * *******************************************/
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>
#include <string>
#include <openpose_ros_msgs/HumanDepthList.h>
#include "../include/robot_control/Controller.h"
#include "../include/robot_control/LocOpenpose.h"
#include "../include/robot_control/ultils.h"

class AngleController
:public BaseController
{
public:
    AngleController()
    : BaseController(), kpAngle_(0.5), kiAngle_(0), kdAngle_(0)
      , sumAngle_(0), preAngle_(0)
    {
        std::string inputPoseTopic;
        nh_.param( "inputPoseTopic", inputPoseTopic, std::string("/openpose_ros/human_depth_list") );
        nh_.getParam( "kpAngle", kpAngle_);
        nh_.getParam( "kiAngle", kiAngle_);
        nh_.getParam( "kdAngle", kdAngle_);
        std::cout << "kpAngle:" << kpAngle_ << std::endl;
        openPoseSub_ = nh_.subscribe( inputPoseTopic, 10, &AngleController::handleOpenposeMsg, this );
    }
private:
    void handleOpenposeMsg( const openpose_ros_msgs::HumanDepthListPtr humanDepthptr )
    {
        curHumanPositiontoRobot_ = locOpenpose_.getPose( humanDepthptr );
        ROS_DEBUG_STREAM( curHumanPositiontoRobot_ );
    }
    virtual geometry_msgs::Twist controlStrategyOutput()
    {
        geometry_msgs::Twist output;
        if( fabs(curHumanPositiontoRobot_.theta - 0) > 1e-6 )
        {
            // y 为整数，当人在机器人前方时 x 为整数，否则为负数
            // 此时假设人在机器人前方，那么机器人应当顺时针转动
            // 计算出的角度 atan2(x,y) > 0
            // 机器人旋转的正方向为 逆时针旋转
            // 因此 z = kp * ( -angle )
            double angle = -atan2( curHumanPositiontoRobot_.x , curHumanPositiontoRobot_.y);
            output.angular.z = kpAngle_ * angle + kiAngle_ * sumAngle_ / controlRate_ 
                                + kdAngle_ * ( angle - preAngle_ ) * controlRate_;
            sumAngle_ += angle;
            preAngle_ = angle;
        }
        return output;       
    }
    LocOpenpose locOpenpose_;
    ros::Subscriber openPoseSub_;
    geometry_msgs::Pose2D curHumanPositiontoRobot_;
    double kpAngle_;
    double kiAngle_;
    double kdAngle_;
    double sumAngle_;
    double preAngle_;
};


int main( int argc, char** argv )
{
    ros::init(argc,argv,"AngleControl");   

    AngleController controller;
    controller.run();
}