/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 19:40:57
 * @LastEditTime: 2021-10-27 19:49:04
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/odom_handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef ODOM_HANDLE_H
#define ODOM_HANDLE_H


#include "rosbag_utils_gui/base_serialize_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"
#include <fstream>

class OdomHandle: public RosbagSerializeBaseHandle
{
public:
    OdomHandle();
    ~OdomHandle();

    virtual int serialize(rosbag::MessageInstance const m);

private:
    std::ofstream ofs_odom;
};


#endif//