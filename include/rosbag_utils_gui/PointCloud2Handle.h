/*
 * @Author: kinggreat24
 * @Date: 2022-01-23 14:07:19
 * @LastEditTime: 2022-01-23 15:08:37
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/PointCloud2Handle.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef POINT2CLOUD_HANDLE_H
#define POINT2CLOUD_HANDLE_H

#include "rosbag_utils_gui/base_serialize_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <sensor_msgs/PointCloud2.h>

class PointCloud2Handle : public RosbagSerializeBaseHandle
{
public:
    PointCloud2Handle();
    ~PointCloud2Handle();

    virtual int serialize(rosbag::MessageInstance const m);

private:
    void WritePcdFile(const sensor_msgs::PointCloud2::ConstPtr pointcloud_msg,
                      const QString& topic_name);

    void WriteBinaryFile(const sensor_msgs::PointCloud2::ConstPtr pointcloud_msg,
                         const QString& topic_name);

    std::ofstream ofs_file_list;
};

#endif //POINT2CLOUD_HANDLE_H