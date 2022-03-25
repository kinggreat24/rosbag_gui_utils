/*
 * @Author: kinggreat24
 * @Date: 2022-03-25 15:07:11
 * @LastEditTime: 2022-03-25 15:37:22
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/livox_driver_custom_msg_handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef LIVOX_DRIVER_CUSTOM_MSG_HANDLE_H
#define LIVOX_DRIVER_CUSTOM_MSG_HANDLE_H

#include "rosbag_utils_gui/base_serialize_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <fstream>

class LivoxCustomMsgHandle : public RosbagSerializeBaseHandle
{
public:
    LivoxCustomMsgHandle();
    ~LivoxCustomMsgHandle();

    virtual int serialize(rosbag::MessageInstance const m);

protected:
    void WriteBinaryFile(const pcl::PointCloud<pcl::PointXYZI>::Ptr pointcloud_ptr,
                         const double timestamp, const QString &topic_name);

private:
    std::ofstream ofs_file_list;
};

#endif //LIVOX_DRIVER_CUSTOM_MSG_HANDLE_H