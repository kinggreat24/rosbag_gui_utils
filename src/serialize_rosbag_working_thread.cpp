/*
 * @Author: kinggreat24
 * @Date: 2021-10-27 10:12:26
 * @LastEditTime: 2021-10-27 19:39:59
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
    std::vector<std::string> v_query_topics;
    for (size_t i = 0; i < topics.size(); i++)
    {
        v_query_topics.push_back(topics.at(i).toStdString());
    }
    m_rosbag_view->addQuery(*bag, rosbag::TopicQuery(v_query_topics));

    // 注册处理函数
    REGISTER_MESSAGE(ImageHandle, "sensor_msgs/Image");
    REGISTER_MESSAGE(LaserscanHandle,"sensor_msgs/LaserScan");


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
    foreach (rosbag::MessageInstance const m, *m_rosbag_view)
    {
        std::string type_name = m.getDataType();
        if(handlers_.find(type_name) != handlers_.end())
        {
            handlers_.find(type_name)->second->serialize(m);
        }
        else
        {
            ROS_ERROR("Can not find %s Handle",type_name.c_str());
            continue;
        }
    }

    isComleted = true;
}