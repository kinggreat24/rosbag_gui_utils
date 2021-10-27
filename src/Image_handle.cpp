/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 16:52:09
 * @LastEditTime: 2021-10-27 19:56:11
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/Image_handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */
#include "rosbag_utils_gui/Image_handle.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

ImageHandle::ImageHandle()
{
    std::cout << "sensor_msgs/Image handle register" << std::endl;
}

ImageHandle::~ImageHandle() {}

int ImageHandle::serialize(rosbag::MessageInstance const m)
{
    sensor_msgs::Image::ConstPtr img_msgs = m.instantiate<sensor_msgs::Image>();
    QString topic_name = QString::fromStdString(m.getTopic());

    static bool flag = false;
    if (!flag)
    {
        std::string file_list_name = m_topic_save_dirs[topic_name].toStdString() + std::string("/file_list.txt");
        ofs_file_list.open(file_list_name);
        flag = true;
    }

    if (img_msgs == NULL)
        return -1;

    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        if (img_msgs->encoding == "rgb8")
            cv_ptr = cv_bridge::toCvCopy(img_msgs, "bgr8");
        else
            cv_ptr = cv_bridge::toCvCopy(img_msgs, img_msgs->encoding);
    }
    catch (cv_bridge::Exception &e)
    {
        std::cerr << "cv_bridge exception: " << e.what() << std::endl;
        return -1;
    }
    cv::Mat img = cv_ptr->image.clone();

    sprintf(file_name_buf, "%s/%0.6f.png", m_topic_save_dirs[topic_name].toStdString().c_str(),
            img_msgs->header.stamp.toSec());
    ofs_file_list << file_name_buf << std::endl;
    cv::imwrite(file_name_buf, img);

    return 0;
}

// REGISTER_MESSAGE(ImageHandle, "sensor_msgs/Image");