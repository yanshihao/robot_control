/**************************************
 * 功能说明:
 *     本文件的功能是实时获取目标位置
 * 作者：
 *      晏世豪
 * 时间：
 *      2020年10月6日
 * *************************************/



#include "../include/robot_control/LocOpenpose.h"
#include "../include/robot_control/ultils.h"
#include <openpose_ros_msgs/HumanDepthList.h>
#include <openpose_ros_msgs/HumanDepth.h>
#include <geometry_msgs/Pose2D.h>
#include <cmath>
using namespace openpose_ros_msgs;
geometry_msgs::Pose2D LocOpenpose::getPose(const openpose_ros_msgs::HumanDepthListPtr humanListptr )
{
    if( humanListptr->num_humans == 0 )
    {
        repeatOutTimes_ ++;
        if( repeatOutTimes_ >= 3 )
        {
            preLoc_.theta = 0;
            repeatOutTimes_ = 3;
        }
        return preLoc_;
    }
    else
    {
        repeatOutTimes_ = 0;
        HumanDepth& firstMan = humanListptr->human_depth_list[0];
        if( firstMan.num_body_key_points_with_non_zero_depth <= 0 ) return preLoc_;
        
        PointWithDepth& rightHip =  firstMan.body_key_points_with_depth[RightHipLoc];

        geometry_msgs::Pose2D curLoc;
        curLoc.theta = 1;
        curLoc.x = rightHip.x;
        curLoc.y = cos(15.0/180*PI)*rightHip.depth - sin(15.0/180*PI)*rightHip.y;
        preLoc_ = curLoc;
        return curLoc;
    }
}