/**********************************************
 * 作用：
 *     控制问题的测试程序
 *     派生了一个具体的控制对象
 * 作者：晏世豪
 * 时间：2020年10月8日
 * *******************************************/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>
#include <string>
#include "../include/robot_control/Controller.h"

class ConcreteController
:public BaseController
{
public:
    ConcreteController()
    : BaseController()
    {

    }
private:
    geometry_msgs::Twist controlStrategyOutput()
    {
        ROS_DEBUG_STREAM("controlStrategyOutput  " << " x:" << 0 << " y:" << " z:" << 0);
        return geometry_msgs::Twist();
    }
};


int main( int argc, char** argv )
{
    ros::init(argc,argv,"testControl");   
    ConcreteController controller;
    controller.run();
}