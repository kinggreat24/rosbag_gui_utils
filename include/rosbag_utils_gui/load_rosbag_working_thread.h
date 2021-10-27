/*
 * @Author: kinggreat24
 * @Date: 2021-10-26 21:10:46
 * @LastEditTime: 2021-10-26 23:40:02
 * @LastEditors: kinggreat24
 * @Description: 
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/load_rosbag_working_thread.h
 * 可以输入预定的版权声明、个性签名、空行等
 */


#ifndef LOAD_ROSBAG_WORKING_THREAD_H
#define LOAD_ROSBAG_WORKING_THREAD_H


#include <QThread>
#include <qfileinfo.h>

#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <unistd.h>

class LoadRosbagWorkingThread : public QThread
{
	Q_OBJECT

public:
	LoadRosbagWorkingThread(QObject *parent);
	~LoadRosbagWorkingThread();

	void setRosbagFileName(QFileInfo);

	bool isLoadCompleted()
	{
		return isComleted;
	}

    std::vector<const rosbag::ConnectionInfo *> getConnectionInfo()
    {
        return m_rosbag_connection_infos;
    }

    rosbag::View* getRosbagView()
    {
        return m_rosbag_view;
    }

    rosbag::Bag* getRosbagBag()
    {
        return m_rosbag_bag;
    }

protected:
	void run();

private:
	QFileInfo m_rosbag_fileinfo;
	rosbag::View* m_rosbag_view;
    rosbag::Bag* m_rosbag_bag;
	bool isComleted;

    std::vector<const rosbag::ConnectionInfo *> m_rosbag_connection_infos;

    uint64_t m_rosbag_size;  // rosbag的大小
};


#endif//LOAD_ROSBAG_WORKING_THREAD_H