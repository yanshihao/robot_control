/**************************************
 * 功能说明：
 *     本文件的功能是实时获取目标位置
 * 作者：
 *      晏世豪
 * 时间：
 *      2020年10月6日
 * *************************************/

#pragma once
#include <openpose_ros_msgs/HumanDepthList.h>
#include <geometry_msgs/Pose2D.h>
#include <vector>

class LocOpenpose{
public:
    LocOpenpose(): start_(false), RightHipLoc(9), repeatOutTimes_(0)
    {

    }
    geometry_msgs::Pose2D getPose(const openpose_ros_msgs::HumanDepthListPtr humanListptr ); 
private:
    bool start_;
    geometry_msgs::Pose2D preLoc_;
    int repeatOutTimes_; 
    const int RightHipLoc;    // 右边髋关节的位置是 9
};