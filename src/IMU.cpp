/*
 * @Author: kinggreat24
 * @Date: 2021-10-04 14:20:47
 * @LastEditTime: 2022-03-25 15:52:13
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/IMU.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/IMU.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>

IMU::IMU()
    : frame_id_("imu"), timestamp_(0.0)
    , orientation_x_(0.0), orientation_y_(0.0), orientation_z_(0.0), orientation_w_(1.0)
    , orientation_covariance_(std::vector<double>(9, 0.0)), angular_velocity_x_(0.0)
    , angular_velocity_y_(0.0), angular_velocity_z_(0.0), angular_velocity_covariance_(std::vector<double>(9, 0.0)), linear_acceleration_x_(0.0), linear_acceleration_y_(0.0), linear_acceleration_z_(0.0), linear_acceleration_covariance_(std::vector<double>(9, 0.0))
{
}

// template<class Archieve>
// void LaserScan::serialize(Archieve& ar, const unsigned int version)
// {
//     ar & frame_id_;
//     ar & timestamp_;
//     ar & min_angle_ & max_angle_ & angle_increment_ & length_;
//     ar & ranges_ & intensitys_;
// }

// template void LaserScan::serialize(boost::archive::binary_iarchive&, const unsigned int);
// template void LaserScan::serialize(boost::archive::binary_oarchive&, const unsigned int);
