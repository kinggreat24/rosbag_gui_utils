/*
 * @Author: kinggreat24
 * @Date: 2022-03-11 11:02:30
 * @LastEditTime: 2022-03-12 20:52:58
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/CompressedImage_handle.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/CompressedImage_handle.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CompressedImage.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QString>

CompressedImageHandle::CompressedImageHandle()
{
    std::cout << "sensor_msgs/CompressedImage handle register" << std::endl;
}

CompressedImageHandle::~CompressedImageHandle() {}

int CompressedImageHandle::serialize(rosbag::MessageInstance const m)
{
    sensor_msgs::CompressedImage::ConstPtr img_msgs = m.instantiate<sensor_msgs::CompressedImage>();
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
        // if (img_msgs->format == "rgb8")
        //     cv_ptr = cv_bridge::toCvCopy(img_msgs, sensor_msgs::image_encodings::BGR8);
        // else
        //     cv_ptr = cv_bridge::toCvCopy(img_msgs, img_msgs->format);
        cv_ptr = cv_bridge::toCvCopy(img_msgs, sensor_msgs::image_encodings::BGR8);
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
    // std::cout<<"save file to: "<<file_name_buf<<std::endl;
    cv::imwrite(file_name_buf, img);

    return 0;
}

// REGISTER_MESSAGE(CompressedImageHandle, "sensor_msgs/Image");