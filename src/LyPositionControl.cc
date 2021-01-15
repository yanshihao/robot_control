/**********************************************
 * 作用：
 *     控制机器人到某个特定的位置
 *     首先要派生了一个具体的控制对象
 * 作者：晏世豪
 * 时间：2020年10月9日
 * *******************************************/
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

#include <iostream>
#include <string>
#include <cmath>
#include <openpose_ros_msgs/HumanDepthList.h>
#include "../include/robot_control/Controller.h"
#include "../include/robot_control/LocOpenpose.h"
#include "../include/robot_control/ultils.h"




class LyPositionController
:public BaseController
{
public:
    LyPositionController( geometry_msgs::Pose2D position = geometry_msgs::Pose2D() )
    : BaseController(), kd_(0.3), ka_(0.6), kb_(-0.2),targetPosition_( position ),controlStep_(0)
    {
        nh_.getParam("kd", kd_);
        nh_.getParam("ka", ka_);
        nh_.getParam("kb", kb_);
    }
    virtual void run()
    {
        ros::Rate loopRate(controlRate_);
        init();
        while( ros::ok() )
        {
            ros::spinOnce();
            geometry_msgs::Twist output = controlStrategyOutput();
            controlSpeedPub_.publish( output );
            if( controlStep_ >= 2 ) break;
            loopRate.sleep();
        }
    }
private:
    virtual void init()
    {
        BaseController::init();
        geometry_msgs::Pose2D& tb = targetPosition_;
        geometry_msgs::Pose2D& qb = curRobotPosition_;
        geometry_msgs::Pose2D  qt;
        qt.x = cos( tb.theta ) * ( qb.x - tb.x ) + sin( tb.theta ) * ( qb.y - tb.y );
        qt.y =-sin( tb.theta ) * ( qb.x - tb.x ) + cos( tb.theta ) * ( qb.y - tb.y );
        qt.theta = getAngle( qb.theta - tb.theta );
        double alpha = getAngle( atan2( -qt.y, -qt.x ) - qt.theta );
        std::cout << "robotPosition: " << qb.x << " " << qb.y << " " << qb.theta << std::endl;
        std::cout << " y is " << qt.y << std::endl;
        std::cout << " x is " << qt.x << std::endl;
        std::cout << " alpha is " << alpha << std::endl;
        forward_ = true;
        if( alpha > PI/2 || alpha < - PI/2 )
            forward_ = false;
        
        std::cout << " forward is " << forward_ << std::endl;
        
        int tmp;
        std::cin >> tmp;
    }

    virtual geometry_msgs::Twist controlStrategyOutput()
    {
        if( controlStep_ == 0 )
            return positionControl();
        else
            return angleControl();
    }

    geometry_msgs::Twist positionControl()
    {
        geometry_msgs::Pose2D& tb = targetPosition_;
        geometry_msgs::Pose2D& qb = curRobotPosition_;
        geometry_msgs::Pose2D  qt;
        qt.x = cos( tb.theta ) * ( qb.x - tb.x ) + sin( tb.theta ) * ( qb.y - tb.y );
        qt.y =-sin( tb.theta ) * ( qb.x - tb.x ) + cos( tb.theta ) * ( qb.y - tb.y );
        qt.theta = getAngle( qb.theta - tb.theta );
        double alpha;
        double beta;
        double distance;
        double theta;
        if( forward_ == true )
        {
            theta = atan2( -qt.y, -qt.x );
            distance = sqrt( qt.x * qt.x + qt.y * qt.y );
        }
        else
        {
            theta = getAngle( atan2( -qt.y, -qt.x ) + PI );
            distance = - sqrt( qt.x * qt.x + qt.y * qt.y );
        }
        alpha = getAngle( theta - qt.theta );
        beta = - theta;
        double v = kd_ * distance;
        double w = ka_ * alpha + kb_ * beta;
        geometry_msgs::Twist speed;
        speed.angular.z = w;
        speed.linear.x = v;
        static int times = 0;
        if( (fabs(distance) < 0.05) && (fabs(v) < 0.1) )
            times ++;
        else
            times = 0;
        if( times >= 10 ) controlStep_ = 1;
        std::cout << controlStep_ << "  " << distance << std::endl;
        std::cout << " times = "<< times << std::endl;
        return speed;
    }

    geometry_msgs::Twist angleControl()
    {
        geometry_msgs::Pose2D& tb = targetPosition_;
        geometry_msgs::Pose2D& qb = curRobotPosition_;
        double beta = - tb.theta + qb.theta;
        double w = kb_ * beta;
        double v = 0;
        static int times = 0;
        if( fabs(beta) < 0.05 )
            times ++;
        if( times >= 6 )
            controlStep_ = 2;
        geometry_msgs::Twist speed;
        speed.angular.z = w;
        speed.linear.x = v;
        return speed;
    }

    double kd_;
    double ka_;
    double kb_;
    bool   forward_;
    geometry_msgs::Pose2D targetPosition_;
    int    controlStep_;   // 0 初始; 1 到达指定地点; 2 到达指定位姿
};

int main( int argc, char** argv )
{
    ros::init(argc,argv,"LyPositionControl");   
    geometry_msgs::Pose2D pose;
    pose.x = 0.5;
    pose.y = 0.5;
    pose.theta = 0.5;

    std::string commond;
    while(1)
    {
        std::cout << "x = " << pose.x << ", y =  " << pose.y << ", theta = " << pose.theta << std::endl;
        std::cout << "Please enter \"yes\" to confirm the configure." << std::endl;
        std::cin >> commond;
        if( commond == "yes" )
            break;
        else
        {
            std::cout << "Please input x, y, theta: ";
            std::cin >> pose.x >> pose.y >> pose.theta;  
        }
    }
    LyPositionController controller( pose );
    controller.run();
}
