/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 10:05:04
 * @LastEditTime: 2022-03-11 11:10:03
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/serialize_rosbag_working_thread.h
 * 可以输入预定的版权声明、个性签名、空行等
 */

#ifndef ROSBAG_SERIALIZA_WORKING_THREAD_H
#define ROSBAG_SERIALIZA_WORKING_THREAD_H

#include <QThread>
#include <qfileinfo.h>

#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <unistd.h>

#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "rosbag_utils_gui/Image_handle.h"
#include "rosbag_utils_gui/CompressedImage_handle.h"
#include "rosbag_utils_gui/Laserscan_handle.h"
#include "rosbag_utils_gui/odom_handle.h"
#include "rosbag_utils_gui/serialize_factory.h"
#include "rosbag_utils_gui/PointCloud2Handle.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

class RosbagSerializeWorkingThread: public QThread{
    Q_OBJECT
public:
    RosbagSerializeWorkingThread(QObject *parent, const rosbag::Bag *bag, rosbag::View* view, 
        const std::vector<QString>& topics, const std::map<QString, QString>& save_dir);
    ~RosbagSerializeWorkingThread();

    bool isCompleted()
	{
		return isComleted;
	}
protected:
    void run();

private:
    const rosbag::Bag* m_rosbag_bag;
    rosbag::View* m_rosbag_view;
    std::vector<QString> m_rosbag_topics;
    std::map<QString, QString> m_rosbag_save_dirs;

    bool isComleted;

    std::map<std::string, RosbagSerializeBaseHandle* > handlers_;
};

#endif//ROSBAG_SERIALIZA_WORKING_THREAD_H

