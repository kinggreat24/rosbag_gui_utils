/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 19:00:11
 * @LastEditTime: 2021-10-27 19:51:57
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/Laserscan_handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef LASERSCAN_HANDLE_H
#define LASERSCAN_HANDLE_H

#include <fstream>

#include "rosbag_utils_gui/base_serialize_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"
#include "rosbag_utils_gui/LaserScan.h"
#include <sensor_msgs/LaserScan.h>

class LaserscanHandle: public RosbagSerializeBaseHandle
{

public:
    LaserscanHandle();
    ~LaserscanHandle();

    virtual int serialize(rosbag::MessageInstance const m);

private:
    std::ofstream ofs_file_list;
};


#endif//LASERSCAN_HANDLE_H