/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 19:43:53
 * @LastEditTime: 2021-11-16 14:27:12
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/odomHandle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/odom_handle.h"
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <fstream>

OdomHandle::OdomHandle()
{
    std::cout << "nav_msgs/Odometry handle register" << std::endl;
}
OdomHandle::~OdomHandle(){}

int OdomHandle::serialize(rosbag::MessageInstance const m)
{
    nav_msgs::Odometry::ConstPtr odom_msgs = m.instantiate<nav_msgs::Odometry>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if(!flag)
    {
        QString odom_txt_file = m_topic_save_dirs[topic_name] + "/odom.txt";
        ofs_odom.open(odom_txt_file.toStdString());
        flag = true;
    }
    
    // 
    double roll = 0.0, pitch = 0.0, yaw = 0.0;
    tf::Quaternion RQ2;
    tf::quaternionMsgToTF(odom_msgs->pose.pose.orientation,RQ2);
    tf::Matrix3x3(RQ2).getRPY(roll,pitch,yaw); 

    char odom_data[256]={0};
    sprintf(odom_data,"%0.6f %0.3f %0.3f %0.3f",odom_msgs->header.stamp.toSec(),
        odom_msgs->pose.pose.position.x,
        odom_msgs->pose.pose.position.y,
        yaw);
    ofs_odom << odom_data << std::endl;
}