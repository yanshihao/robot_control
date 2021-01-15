/**********************************************
 * 作用：
 *     控制问题的基类，协调ROS系统输出控制信息
 *     可重载 run() 方法改变控制过程
 *     可重载 controlStrategyOutPut() 方法改变控制策略，
 *     当然也可在派生类中添加其他辅助
 * 作者：晏世豪
 * 时间：2020年10月8日
 * *******************************************/
#pragma once
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Bool.h>
#include <iostream>
#include <string>
// 订阅 "/robot_odm"， 其类型为 geometry_msgs::Pose2D

class BaseController
{
public:
    BaseController(int controlRate=10);
    virtual void run();
private:
    void handleOdmMsg( const geometry_msgs::Pose2DPtr poseptr )
    {
        curRobotValid_ = true;
        curRobotPosition_ = *poseptr.get();
    }
    void handleControlSignalMsg( const std_msgs::BoolConstPtr controlSigal )
    {
        controlSignal_ = controlSigal.get()->data;
    }
    virtual geometry_msgs::Twist controlStrategyOutput()=0;
protected:
    virtual void init(){
        while( ros::ok() )
        {
            ros::spinOnce();
            if( curRobotValid_ == true && controlSignal_ == true )
                break;
        }
    }
    ros::NodeHandle nh_;
    ros::Publisher controlSpeedPub_;
    ros::Subscriber robotOdmSub_;
    ros::Subscriber controlSignalSub_;
    const int controlRate_;
    geometry_msgs::Pose2D curRobotPosition_;
    bool curRobotValid_;
    bool controlSignal_;    //控制机器人开始和停止的信号
};