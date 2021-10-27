/*
 * @Author: kinggreat24
 * @Date: 2021-10-04 14:01:11
 * @LastEditTime: 2021-10-27 19:13:06
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/LaserScan.h
 * 可以输入预定的版权声明、个性签名、空行等
 */


#ifndef LASER_SCAN_H_
#define LASER_SCAN_H_

#include <vector>
#include <string>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


class LaserScan{
public:
    LaserScan();
    LaserScan(const LaserScan& laserscan);
    
    std::string frame_id_;
    double timestamp_;
    double min_angle_;
    double max_angle_;
    double min_ranges_;
    double max_ranges_;
    double angle_increment_;
    int length_;
    std::vector<double> ranges_;
    std::vector<double> intensitys_;

    // seralization addition   
private:
    friend class boost::serialization::access;
    
    // template<class Archieve>
    // void serialize(Archieve& var, const unsigned int version);
    
    template<class Archieve>
    void save(Archieve& ar, const unsigned int version) const
    {
        ar & frame_id_;
        ar & timestamp_;
        ar & min_angle_ & max_angle_ & angle_increment_ & length_;
        ar & ranges_ & intensitys_;
    }

    template<class Archieve>
    void load(Archieve& ar, const unsigned int version)
    {
        ar & frame_id_;
        ar & timestamp_;
        ar & min_angle_ & max_angle_ & angle_increment_ & length_;
        ar & ranges_ & intensitys_;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
    
};


#endif//LASER_SCAN_H_