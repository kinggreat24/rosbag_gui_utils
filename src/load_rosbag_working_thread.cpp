/*
 * @Author: kinggreat24
 * @Date: 2021-10-26 21:13:13
 * @LastEditTime: 2021-10-26 23:39:21
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/src/load_rosbag_working_thread.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include "rosbag_utils_gui/load_rosbag_working_thread.h"

LoadRosbagWorkingThread::LoadRosbagWorkingThread(QObject *parent)
    : QThread(parent)
{
    isComleted = false;
}

LoadRosbagWorkingThread::~LoadRosbagWorkingThread()
{
}

void LoadRosbagWorkingThread::setRosbagFileName(QFileInfo rosbag_info)
{
    m_rosbag_fileinfo = rosbag_info;
}

//加载rosbag
void LoadRosbagWorkingThread::run()
{
    isComleted = false;

    //rosbag::Bag bag;
    m_rosbag_bag = new rosbag::Bag();
    m_rosbag_bag->open(m_rosbag_fileinfo.filePath().toStdString(), rosbag::bagmode::Read);
    m_rosbag_view = new rosbag::View(*m_rosbag_bag);
    m_rosbag_connection_infos = m_rosbag_view->getConnections();

    isComleted = true;
}