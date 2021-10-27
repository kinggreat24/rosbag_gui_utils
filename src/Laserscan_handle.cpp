/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 19:02:44
 * @LastEditTime: 2021-10-27 19:55:48
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/Laserscan_handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/Laserscan_handle.h"
#include <QString>

LaserscanHandle::LaserscanHandle() 
{
    std::cout << "sensor_msgs/LaserScan handle register" << std::endl;
}
LaserscanHandle::~LaserscanHandle() {}

int LaserscanHandle::serialize(rosbag::MessageInstance const m)
{
    sensor_msgs::LaserScan::ConstPtr laserscan_msgs = m.instantiate<sensor_msgs::LaserScan>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if(!flag)
    {
        std::string file_list_name = m_topic_save_dirs[topic_name].toStdString()+std::string("/file_list.txt");
        ofs_file_list.open(file_list_name);
        flag = true;
    }

    LaserScan laserscan;
    laserscan.frame_id_   = laserscan_msgs->header.frame_id;
    laserscan.timestamp_  = laserscan_msgs->header.stamp.toSec();
    laserscan.min_angle_  = laserscan_msgs->angle_min;
    laserscan.max_angle_  = laserscan_msgs->angle_max;
    laserscan.min_ranges_ = laserscan_msgs->range_min;
    laserscan.max_ranges_ = laserscan_msgs->range_max;
    laserscan.angle_increment_ = laserscan_msgs->angle_increment;
    laserscan.length_ = laserscan_msgs->ranges.size();
    laserscan.ranges_.resize(laserscan_msgs->ranges.size(), 0.0);
    laserscan.intensitys_.resize(laserscan_msgs->intensities.size(), 0.0);

    for (int i = 0; i < laserscan_msgs->ranges.size(); i++)
        laserscan.ranges_[i] = laserscan_msgs->ranges.at(i);

    if (laserscan_msgs->intensities.size() > 0)
    {
        for (int i = 0; i < laserscan_msgs->intensities.size(); i++)
            laserscan.intensitys_[i] = laserscan_msgs->intensities.at(i);
    }

    sprintf(file_name_buf,"%s/%0.6f.bin", m_topic_save_dirs[topic_name].toStdString().c_str(), 
        laserscan_msgs->header.stamp.toSec());
    
    ofs_file_list << file_name_buf<<std::endl;
    
    std::ofstream os(file_name_buf);
    boost::archive::binary_oarchive oa(os);
    oa << laserscan;

    clearBuf();

    return 0;
}