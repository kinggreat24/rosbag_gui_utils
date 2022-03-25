/*
 * @Author: kinggreat24
 * @Date: 2022-03-25 15:09:44
 * @LastEditTime: 2022-03-25 15:38:08
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/livox_driver_custom_msg_handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/livox_driver_custom_msg_handle.h"
#include <livox_ros_driver/CustomMsg.h>
#include <QString>

LivoxCustomMsgHandle::LivoxCustomMsgHandle()
{
    std::cout << "<livox_ros_driver/CustomMsg handle register" << std::endl;
}
LivoxCustomMsgHandle::~LivoxCustomMsgHandle() {}

int LivoxCustomMsgHandle::serialize(rosbag::MessageInstance const m)
{
    livox_ros_driver::CustomMsg::ConstPtr livox_msg_in = m.instantiate<livox_ros_driver::CustomMsg>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if (!flag)
    {
        std::string file_list_name = m_topic_save_dirs[topic_name].toStdString() + std::string("/file_list.txt");
        ofs_file_list.open(file_list_name);
        flag = true;
    }

    pcl::PointCloud<pcl::PointXYZI>::Ptr horizon_cloud(new pcl::PointCloud<pcl::PointXYZI>());
    for (uint i = 0; i < livox_msg_in->point_num; ++i)
    {
        if (((livox_msg_in->points[i].x)) || ((livox_msg_in->points[i].y)) || ((livox_msg_in->points[i].z)))
        {
            pcl::PointXYZI myPoint;
            myPoint.x = livox_msg_in->points[i].x;
            myPoint.y = livox_msg_in->points[i].y;
            myPoint.z = livox_msg_in->points[i].z;
            myPoint.intensity = livox_msg_in->points[i].reflectivity;
            horizon_cloud->push_back(myPoint);
        }
    }

    WriteBinaryFile(horizon_cloud, livox_msg_in->header.stamp.toSec(), topic_name);
    
    return 0;
}

void LivoxCustomMsgHandle::WriteBinaryFile(const pcl::PointCloud<pcl::PointXYZI>::Ptr pointcloud_ptr,
                                           const double timestamp, const QString &topic_name)
{
    sprintf(file_name_buf, "%s/%0.6f.bin", m_topic_save_dirs[topic_name].toStdString().c_str(),
            timestamp);
    ofs_file_list << file_name_buf << std::endl;

    std::vector<float> binFileValues;
    binFileValues.reserve(pointcloud_ptr->size() * 4);

    for (auto pt_iter = pointcloud_ptr->begin(); pt_iter != pointcloud_ptr->end(); pt_iter++)
    {
        binFileValues.push_back(pt_iter->x);
        binFileValues.push_back(pt_iter->y);
        binFileValues.push_back(pt_iter->z);
        binFileValues.push_back(pt_iter->intensity);
    }

    std::ofstream outBinFile(std::string(file_name_buf), std::ios::out | std::ios::binary);
    outBinFile.write((char *)binFileValues.data(), binFileValues.size() * sizeof(float));
    outBinFile.flush();
    outBinFile.close();
}