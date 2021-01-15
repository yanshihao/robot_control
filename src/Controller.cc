/**********************************************
 * 作用：
 *     控制问题的基类，协调ROS系统输出控制信息
 *     可重载 run() 方法改变控制过程
 *     可重载 controlStrategyOutPut() 方法改变控制策略，
 *     当然也可在派生类中添加其他辅助
 * 作者：晏世豪
 * 时间：2020年10月8日
 * *******************************************/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>
#include <string>
#include "../include/robot_control/Controller.h"
BaseController::BaseController(int controlRate)
:controlRate_(controlRate), nh_("~"), curRobotValid_(false), controlSignal_(false)
{
    // 参数化订阅名，方便后续无编译更改
    std::string outputSpeedTopic("/robot/speed");
    std::string inputOdmTopic ;
    std::string inputControlSignalTopic ;
    nh_.param("outputTwistTopic", outputSpeedTopic, std::string("/robot/speed"));
    nh_.param("inputOdmTopic", inputOdmTopic, std::string("/robot_odm"));
    nh_.param("inputControlSignalTopic", inputControlSignalTopic, std::string("/robot/controlSignal"));
    std::cout << outputSpeedTopic << std::endl;
    controlSpeedPub_ = nh_.advertise<geometry_msgs::Twist>(outputSpeedTopic,10);
    robotOdmSub_     = nh_.subscribe( inputOdmTopic , 10, &BaseController::handleOdmMsg, this ); 
    controlSignalSub_ = nh_.subscribe( inputControlSignalTopic, 10, &BaseController::handleControlSignalMsg, this  );
}

void BaseController::run()
{
    ros::Rate loopRate(controlRate_);
    init();
    while( ros::ok() && controlSignal_ == true )
    {
        ros::spinOnce();
        geometry_msgs::Twist output = controlStrategyOutput();
        //ROS_INFO_STREAM( output );
        controlSpeedPub_.publish( output );
        loopRate.sleep();
    }
}