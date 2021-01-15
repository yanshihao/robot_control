/**********************************************
 * 作用：
 *     控制机器人直线跟随目标
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

class LineFollowControl
: public BaseController
{
public:
    LineFollowControl()
    : BaseController(), kpDis_(0.5), kiDis_(0), kdDis_(0)
      , sumDis_(0), preDis_(0)
    {
        std::string inputPoseTopic;
        nh_.param( "inputPoseTopic", inputPoseTopic, std::string("/openpose_ros/human_depth_list") );
        nh_.getParam( "kpDis", kpDis_);
        nh_.getParam( "kiDis", kiDis_);
        nh_.getParam( "kdDis", kdDis_);
        std::cout << "kpDis:" << kpDis_ << std::endl;
        std::cout << "kiDis:" << kiDis_ << std::endl;
        std::cout << "kdDis:" << kdDis_ << std::endl;
        openPoseSub_ = nh_.subscribe( inputPoseTopic, 10, &LineFollowControl::handleOpenposeMsg, this );
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
        const double& x = curHumanPositiontoRobot_.x;
        sumDis_ += x;
        output.linear.x = kpDis_ * x + kiDis_ * sumDis_ / controlRate_
                          + kdDis_ * ( x - preDis_ ) * controlRate_;
        preDis_ = x;
        return output;
    }
    LocOpenpose locOpenpose_;
    ros::Subscriber openPoseSub_;
    geometry_msgs::Pose2D curHumanPositiontoRobot_;
    double kpDis_;
    double kiDis_;
    double kdDis_;
    double sumDis_;
    double preDis_;
};


int main( int argc, char** argv )
{
    ros::init(argc,argv,"LineFollowControl");   

    LineFollowControl controller;
    controller.run();
}