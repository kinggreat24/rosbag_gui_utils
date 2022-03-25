/*
 * @Author: kinggreat24
 * @Date: 2021-10-04 14:01:11
 * @LastEditTime: 2022-03-25 15:48:28
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/IMU.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef IMU_SENSOR_H_
#define IMU_SENSOR_H_

#include <vector>
#include <string>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


class IMU
{
public:
    IMU();
    IMU(const IMU &laserscan);

    std::string frame_id_;
    double timestamp_;

    // orientation
    double orientation_x_;
    double orientation_y_;
    double orientation_z_;
    double orientation_w_;
    std::vector<double> orientation_covariance_;

    // angular_velocity
    double angular_velocity_x_;
    double angular_velocity_y_;
    double angular_velocity_z_;
    std::vector<double> angular_velocity_covariance_;

    // linear_acceleration
    double linear_acceleration_x_;
    double linear_acceleration_y_;
    double linear_acceleration_z_;
    std::vector<double> linear_acceleration_covariance_;

private:
    friend class boost::serialization::access;

    // template<class Archieve>
    // void serialize(Archieve& var, const unsigned int version);

    template <class Archieve>
    void save(Archieve &ar, const unsigned int version) const
    {
        ar &frame_id_;
        ar &timestamp_;

        ar &orientation_x_ &orientation_y_ &orientation_z_ &orientation_w_;
        ar &orientation_covariance_;

        ar &angular_velocity_x_ &angular_velocity_y_ &angular_velocity_z_;
        ar &angular_velocity_covariance_;

        ar &linear_acceleration_x_ &linear_acceleration_y_ &linear_acceleration_z_;
        ar &linear_acceleration_covariance_;
    }

    template <class Archieve>
    void load(Archieve &ar, const unsigned int version)
    {
        ar &frame_id_;
        ar &timestamp_;

        ar &orientation_x_ &orientation_y_ &orientation_z_ &orientation_w_;
        ar &orientation_covariance_;

        ar &angular_velocity_x_ &angular_velocity_y_ &angular_velocity_z_;
        ar &angular_velocity_covariance_;

        ar &linear_acceleration_x_ &linear_acceleration_y_ &linear_acceleration_z_;
        ar &linear_acceleration_covariance_;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

#endif //IMU_SENSOR_H_