/*
 * @Author: kinggreat24
 * @Date: 2022-03-25 14:46:00
 * @LastEditTime: 2022-03-25 15:05:31
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/IMU_handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/IMU_handle.h"
#include <sensor_msgs/Imu.h>
#include "rosbag_utils_gui/IMU.h"
#include <QString>

IMUHandle::IMUHandle() 
{
    std::cout << "sensor_msgs/Imu handle register" << std::endl;
}
IMUHandle::~IMUHandle() {}

int IMUHandle::serialize(rosbag::MessageInstance const m)
{
    sensor_msgs::Imu::ConstPtr imu_msg = m.instantiate<sensor_msgs::Imu>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if(!flag)
    {
        std::string file_list_name = m_topic_save_dirs[topic_name].toStdString()+std::string("/file_list.txt");
        ofs_file_list.open(file_list_name);
        flag = true;
    }

    IMU imu_data;
    imu_data.frame_id_   = imu_msg->header.frame_id;
    imu_data.timestamp_  = imu_msg->header.stamp.toSec();
    
    imu_data.orientation_x_ = imu_msg->orientation.x;
    imu_data.orientation_y_ = imu_msg->orientation.y;
    imu_data.orientation_z_ = imu_msg->orientation.z;
    imu_data.orientation_w_ = imu_msg->orientation.w;
    for(size_t i=0;i<9;i++)
        imu_data.orientation_covariance_[i] = imu_msg->orientation_covariance[i];

    imu_data.angular_velocity_x_ = imu_msg->angular_velocity.x;
    imu_data.angular_velocity_y_ = imu_msg->angular_velocity.y;
    imu_data.angular_velocity_z_ = imu_msg->angular_velocity.z;
    for(size_t i=0;i<9;i++)
        imu_data.angular_velocity_covariance_[i] = imu_msg->angular_velocity_covariance[i];

    imu_data.linear_acceleration_x_ = imu_msg->linear_acceleration.x;
    imu_data.linear_acceleration_y_ = imu_msg->linear_acceleration.y;
    imu_data.linear_acceleration_z_ = imu_msg->linear_acceleration.z;
    for(size_t i=0;i<9;i++)
        imu_data.linear_acceleration_covariance_[i] = imu_msg->linear_acceleration_covariance[i];

    sprintf(file_name_buf,"%s/%0.9f.bin", m_topic_save_dirs[topic_name].toStdString().c_str(), 
        imu_msg->header.stamp.toSec());
    
    ofs_file_list << file_name_buf<<std::endl;
    
    std::ofstream os(file_name_buf);
    boost::archive::binary_oarchive oa(os);
    oa << imu_data;

    clearBuf();

    return 0;
}