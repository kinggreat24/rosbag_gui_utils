/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 10:12:26
 * @LastEditTime: 2022-09-19 16:16:41
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/serialize_rosbag_working_thread.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/serialize_rosbag_working_thread.h"

RosbagSerializeWorkingThread::RosbagSerializeWorkingThread(
    QObject *parent, const rosbag::Bag *bag, rosbag::View *view,
    const std::vector<QString> &topics, const std::map<QString, QString> &save_dir)
    : QThread(parent), m_rosbag_bag(bag), m_rosbag_view(view), m_rosbag_topics(topics), m_rosbag_save_dirs(save_dir), isComleted(false)
{
    // std::vector<std::string> v_query_topics;
    // for (size_t i = 0; i < topics.size(); i++)
    // {
    //     v_query_topics.push_back(topics.at(i).toStdString());
    // }
    // m_rosbag_view->addQuery(*bag, rosbag::TopicQuery(v_query_topics));

    beginTime_ = m_rosbag_view->getBeginTime();
    endTime_ = m_rosbag_view->getEndTime();

    duration_ = (endTime_ - beginTime_).toSec();

    // 注册处理函数
    REGISTER_MESSAGE(ImageHandle, "sensor_msgs/Image");
    REGISTER_MESSAGE(CompressedImageHandle, "sensor_msgs/CompressedImage");
    REGISTER_MESSAGE(LaserscanHandle, "sensor_msgs/LaserScan");
    REGISTER_MESSAGE(PointCloud2Handle, "sensor_msgs/PointCloud2");
    REGISTER_MESSAGE(OdomHandle, "nav_msgs/Odometry");
    REGISTER_MESSAGE(LivoxCustomMsgHandle, "livox_ros_driver/CustomMsg");
    REGISTER_MESSAGE(IMUHandle, "sensor_msgs/Imu");

    //Initalization handlers
    handlers_ = RosbagSerializeFactory::getHandlers();
    ROS_INFO("Handler size: %d", static_cast<int>(RosbagSerializeFactory::getMap().size()));
    for (auto &x : RosbagSerializeFactory::getMap())
    {
        RosbagSerializeBaseHandle *phandler = x.second();
        phandler->initialize(save_dir);
        handlers_.emplace(x.first, phandler);
    }
}

RosbagSerializeWorkingThread::~RosbagSerializeWorkingThread()
{
}

void RosbagSerializeWorkingThread::run()
{
    isComleted = false;
    int id = 0;
    foreach (rosbag::MessageInstance const m, *m_rosbag_view)
    {
        std::string type_name = m.getDataType();
        std::string topic_name = m.getTopic();
        ros::Time c_time = m.getTime();
        float c_progress = (c_time - beginTime_).toSec();
        int progress_status = (c_progress / duration_) * 100;
        Q_EMIT updateProgressSignal(progress_status);

        // updateProgressSignal
        if (std::find(std::begin(m_rosbag_topics), std::end(m_rosbag_topics), QString::fromStdString(topic_name)) == std::end(m_rosbag_topics))
            continue;

        if (handlers_.find(type_name) != handlers_.end())
        {
            handlers_.find(type_name)->second->serialize(m);
        }
        else
        {
            ROS_ERROR("Can not find %s Handle", type_name.c_str());
            continue;
        }
        id++;
    }

    isComleted = true;
}