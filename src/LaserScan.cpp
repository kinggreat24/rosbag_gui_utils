/*
 * @Author: kinggreat24
 * @Date: 2021-10-04 14:20:47
 * @LastEditTime: 2021-10-27 19:24:52
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/LaserScan.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/LaserScan.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>


LaserScan::LaserScan()
    : frame_id_("laserscan1"), min_angle_(-3.14), max_angle_(3.14)
    , min_ranges_(0.0), max_ranges_(40.0), angle_increment_(0.1)
    , length_( (max_angle_-min_angle_)/angle_increment_ )
    , ranges_(std::vector<double>(length_, 0.0))
    , intensitys_(std::vector<double>(length_, 1.0))
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

