/*
 * @Author: kinggreat24
 * @Date: 2021-10-20 14:22:04
 * @LastEditTime: 2021-10-27 09:57:33
 * @LastEditors: kinggreat24
 * @Description: 录制rosbag
 * @FilePath: /rosbag_utils_gui/include/rosbag_utils_gui/rosbag_record_page.h
 * 可以输入预定的版权声明、个性签名、空行等
 */
#ifndef ROSBAG_RECORD_PAGE_H
#define ROSBAG_RECORD_PAGE_H

#include <QWidget>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "rosbag_utils_gui/rosbag_utils_dlg.h"

#include <rosbag/recorder.h>


namespace rosbag_utils_gui
{

class RosbagRecordPage : public QWidget
{
	Q_OBJECT

public:
	RosbagRecordPage(QWidget *parent = Q_NULLPTR);
	~RosbagRecordPage();
	void initUI();

    bool onRosbagRecordCallback(QString,QVector<QString>);
    bool onFinishRosbagRecordCallback();
    
protected Q_SLOTS:
    void onRosbagRecordSlot();
    
private:
	QPushButton *rosbag_record_btn_;
	QLineEdit   *content_;

    RosbagUtilsDlg* rosbag_record_dlg_;

    // rosbag record related
    rosbag::RecorderOptions* recorder_options_ptr_;
    rosbag::Recorder* rosbag_recorder_ptr_;
};

}

#endif//ROSBAG_RECORD_PAGE_H
