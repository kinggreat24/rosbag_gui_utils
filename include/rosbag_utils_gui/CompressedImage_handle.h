/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 16:48:33
 * @LastEditTime: 2022-03-11 11:25:29
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/CompressedImage_handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef SENSOR_MSGS_COMPRESSED_IMAGE_HANDLE_H
#define SENSOR_MSGS_COMPRESSED_IMAGE_HANDLE_H

#include "rosbag_utils_gui/base_serialize_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"

#include <fstream>

class CompressedImageHandle: public RosbagSerializeBaseHandle
{
public:
    CompressedImageHandle();
    ~CompressedImageHandle();

    virtual int serialize(rosbag::MessageInstance const m);

private:
    std::ofstream ofs_file_list;
};



#endif//SENSOR_MSGS_COMPRESSED_IMAGE_HANDLE_H