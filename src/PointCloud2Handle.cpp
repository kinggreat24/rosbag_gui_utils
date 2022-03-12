/*
 * @Author: kinggreat24
 * @Date: 2022-01-23 14:15:07
 * @LastEditTime: 2022-01-23 16:08:04
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/PointCloud2Handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/PointCloud2Handle.h"
#include <fstream>
#include <QString>

PointCloud2Handle::PointCloud2Handle()
{
    std::cout << "sensor_msgs/PointCloud2 handle register" << std::endl;
}
PointCloud2Handle::~PointCloud2Handle() {}

int PointCloud2Handle::serialize(rosbag::MessageInstance const m)
{
    sensor_msgs::PointCloud2::ConstPtr pointcloud2_msgs = m.instantiate<sensor_msgs::PointCloud2>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if (!flag)
    {
        std::string file_list_name = m_topic_save_dirs[topic_name].toStdString() + std::string("/file_list.txt");
        ofs_file_list.open(file_list_name);
        flag = true;
    }

    //以pcd的格式存储
    // WritePcdFile(pointcloud2_msgs, topic_name);

    //以bin格式存储
    WriteBinaryFile(pointcloud2_msgs, topic_name);
    return 0;
}

void PointCloud2Handle::WritePcdFile(const sensor_msgs::PointCloud2::ConstPtr pointcloud_msg, const QString &topic_name)
{
    pcl::PointCloud<pcl::PointXYZI>::Ptr pointcloud_ptr(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::fromROSMsg(*pointcloud_msg, *pointcloud_ptr);
    sprintf(file_name_buf, "%s/%0.6f.pcd", m_topic_save_dirs[topic_name].toStdString().c_str(),
            pointcloud_msg->header.stamp.toSec());
    ofs_file_list << file_name_buf << std::endl;

    pcl::io::savePCDFileASCII(file_name_buf, *pointcloud_ptr); //将点云保存到PCD文件中
}

void PointCloud2Handle::WriteBinaryFile(const sensor_msgs::PointCloud2::ConstPtr pointcloud_msg,
                                        const QString &topic_name)
{
    pcl::PointCloud<pcl::PointXYZI>::Ptr pointcloud_ptr(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::fromROSMsg(*pointcloud_msg, *pointcloud_ptr);
    sprintf(file_name_buf, "%s/%0.6f.bin", m_topic_save_dirs[topic_name].toStdString().c_str(),
            pointcloud_msg->header.stamp.toSec());
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